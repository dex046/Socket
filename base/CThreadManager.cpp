#include "CThreadManager.h"
CThreadManager::CThreadManager()
{
    m_iNumofthread = 10;
    m_Pool = new CThreadPool(m_iNumofthread);
}

CThreadManager::CThreadManager(int num)
{
    m_iNumofthread = num;
    m_Pool = new CThreadPool(m_iNumofthread);
}

CThreadManager::~CThreadManager()
{
    if(NULL != m_Pool)
    {
        delete m_Pool;
    }
}

void CThreadManager::SetParallelNum(int num)
{
    m_iNumofthread = num;
}

void CThreadManager::Run(CJob *job, void *jobdata)
{
    m_Pool->Run(job, jobdata);
}

void CThreadManager::TerminateAll(void)
{
    m_Pool->TerminateAll();
}
