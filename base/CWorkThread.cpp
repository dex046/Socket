#include "CWorkThread.h"
CWorkThread::CWorkThread()
{
    this->m_Job = NULL;
    this->m_JobData = NULL;
    this->m_IsEnd = false;
    this->m_ThreadPool = NULL;
}

CWorkThread::~CWorkThread()
{
    if(NULL != m_Job)
        delete m_Job;
//    if(NULL != m_JobData)
//        delete m_JobData;
    if(NULL != m_ThreadPool)
        delete m_ThreadPool;//把整个线程池都删掉？
}

void CWorkThread::Run()
{
    SetThreadPool(this->m_ThreadPool);
    for(;;)
    {
        while(m_Job == NULL)
        {
            m_JobCond.Wait();
        }

        m_Job->Run(this->m_JobData);
        m_Job->SetWorkThread(NULL);
        m_Job = NULL;
        m_ThreadPool->_MoveToIdleList(this);
    }
}

void CWorkThread::SetJob(CJob *job, void *jobdata)
{

}

void CWorkThread::SetThreadPool(CThreadPool *threadpool)
{

}

void CWorkThread::Start()
{

}

