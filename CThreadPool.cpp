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
    m_AvailHigh = Initnum + 10;

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
        CThreadMutexGuard guard_mutex = new CThreadMutexGuard(m_IdleMutex);
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
    CThreadMutexGuard guard_mutex = new CThreadMutexGuard(m_IdleMutex);
    m_IdleList.push_back(jobthread);
    m_ThreadList.push_back(jobthread);
}

void CThreadPool::_MoveToBusyList(CWorkThread *idlethread)
{
    {
        CThreadMutexGuard guard_mutex = new CThreadMutexGuard(m_BusyMutex);
        m_BusyList.push_back(idlethread);
        m_AvailNum--;
    }

    {
        CThreadMutexGuard guardmutex = new CThreadMutexGuard(m_IdleMutex);
        vector<CWorkThread*>::iterator pos;
        pos = find(m_IdleList.begin(), m_IdleList.end(), idlethread);
        if(pos != m_BusyList.end())
        {
            m_BusyList.erase(pos);
        }
    }

    m_IdleCond.notify();


}
