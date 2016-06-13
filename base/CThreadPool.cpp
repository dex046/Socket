#include "CThreadPool.h"
CThreadPool::CThreadPool()
{
    m_MaxNum = 50;
    m_AvailLow = 5;
    m_AvailNum = m_InitNum = 10;
    m_AvailHigh = 20;

    m_BusyList.clear();
    m_IdleList.clear();
    for(int i = 0; i < m_InitNum; ++i)
    {
        CWorkThread* thr = new CWorkThread;
        thr->SetThreadPool(this);
        _AppendToIdleList(thr);
        thr->Start();///////
    }
}

CThreadPool::CThreadPool(int initnum)
{
    assert(initnum>0 && initnum<=30);
    m_MaxNum = 30;
    m_AvailLow = initnum - 10 > 0 ? initnum - 10 : 3;
    m_InitNum = m_AvailNum = initnum;
    m_AvailHigh = initnum + 10;

    m_BusyList.clear();
    m_IdleList.clear();
    for(int i = 0; i < m_InitNum; ++i)
    {
        CWorkThread* thr = new CWorkThread;
        thr->SetThreadPool(this);
        _AppendToIdleList(thr);
        thr->Start();//begin the thread,the thread wait for job
    }
}

CThreadPool::~CThreadPool()
{
    TerminateAll();
}

void CThreadPool::TerminateAll()
{
    for(int i = 0; i < m_ThreadList.size(); ++i)
    {
        CWorkThread* thr = m_ThreadList[i];
        thr->Join();
    }
}

CWorkThread* CThreadPool::_GetIdleThread()
{
    while(m_IdleList.size() == 0)
        m_IdleCond.Wait();

    {
        CThreadMutexGuard guard_mutex(m_IdleMutex);
        if(m_IdleList.size() > 0)
        {
            CWorkThread* thr = (CWorkThread*)m_IdleList.front();
            cout << "Get Idle thread " << thr->GetThreadID() << endl;
            return thr;
        }
    }

    return NULL;
}

void CThreadPool::_AppendToIdleList(CWorkThread* jobthread)
{
    CThreadMutexGuard guard_mutex(m_IdleMutex);
    m_IdleList.push_back(jobthread);
    m_ThreadList.push_back(jobthread);
}

void CThreadPool::_MoveToBusyList(CWorkThread *idlethread)
{
    {
        CThreadMutexGuard guard_mutex(m_BusyMutex);
        m_BusyList.push_back(idlethread);
        m_AvailNum--;
    }

    {
        CThreadMutexGuard guard_mutex(m_IdleMutex);
        vector<CWorkThread*>::iterator pos;
        pos = find(m_IdleList.begin(), m_IdleList.end(), idlethread);
        if(pos != m_IdleList.end())
        {
            m_IdleList.erase(pos);
        }
    }
}

void CThreadPool::_MoveToIdleList(CWorkThread *busythread)
{
    {
        CThreadMutexGuard guard_mutex(m_IdleMutex);
        m_IdleList.push_back(busythread);
        m_AvailNum++;
    }

    {
        CThreadMutexGuard guard_mutex(m_BusyMutex);
        vector<CWorkThread*>::iterator pos;
        pos = find(m_BusyList.begin(), m_BusyList.end(), busythread);
        if(pos != m_BusyList.end())
        {
            m_BusyList.erase(pos);
        }
    }

    m_IdleCond.notify();
    m_MaxNumCond.notify();//
}

//create num idle thread and put them into idlelist
void CThreadPool::_CreateIdleThread(int num)
{
    for(int i = 0; i < num; ++i)
    {
        CWorkThread* thr = new CWorkThread;
        thr->SetThreadPool(this);
        _AppendToIdleList(thr);
        {
            CThreadMutexGuard guard_mutex(m_varMutex);//这里使用RAII是不是效率不高?
            m_AvailNum++;
        }
        thr->Start();//start
    }
}

void CThreadPool::_DeleteIdleThread(int num)
{
    {
        CThreadMutexGuard guard_mutex(m_IdleMutex);
        for(int i = 0; i < num; ++i)
        {
            CWorkThread* thr;
            if(m_IdleList.size() > 0)
            {
                thr = (CWorkThread*)m_IdleList.front();
                cout << "Get Idle thread " << thr->GetThreadID() << endl;
            }

            vector<CWorkThread*>::iterator pos;
            pos = find(m_IdleList.begin(), m_IdleList.end(), thr);
            if(pos != m_IdleList.end())
            {
                m_IdleList.erase(pos);
            }
            m_AvailNum--;
            cout << "The idle thread available num: " << m_AvailNum << endl;
            cout << "The idlelist num: " << m_IdleList.size() << endl;
        }
    }

}

void CThreadPool::Run(CJob *job, void *jobdata)
{
    assert(job != NULL);

    if(GetBusyNum() == m_MaxNum)
        m_MaxNumCond.Wait();

    if(m_IdleList.size() < m_AvailLow)
    {
        //默认情况下，创建后的线程数目应该为m_InitNum，
        if(GetAllNum() + m_InitNum - m_IdleList.size() < m_MaxNum)
        {
            _CreateIdleThread(m_InitNum - m_IdleList.size());
        }
        else
        {
            _CreateIdleThread(m_MaxNum - GetAllNum());
        }

        CWorkThread* idlethr = _GetIdleThread();
        if(idlethr != NULL)
        {
            CThreadMutexGuard guard_mutex(idlethr->m_WorkMutex);
            _MoveToBusyList(idlethr);
            idlethr->SetThreadPool(this);
            job->SetWorkThread(idlethr);
            cout << "job is set to thread " << idlethr->GetThreadID() << endl;
            idlethr->SetJob(job, jobdata);
        }
    }
}

