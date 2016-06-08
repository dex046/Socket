#include "CJob.h"
CJob::CJob(void) : m_WorkThread(NULL), m_JobNo(0), m_JobName(NULL)
{

}

CJob::~CJob()
{

}
void CJob::SetJobNo(int jobno)
{
    this->m_JobNo = jobno;
}

int CJob::GetJobNo(void) const
{
    return this->m_JobNo;
}

void CJob::SetJobName(string jobname)
{
    this->m_JobName = jobname;
    /*
    if(NULL != m_JobName)
    {
        free(m_JobName);
        m_JobName = NULL;
    }

    if(NULL != jobname)
    {
        m_JobName = (char*)malloc(strlen(jobname) + 1);
        strcpy(m_JobName, jobname);
    }
    */

}

string CJob::GetJobName() const
{
    return m_JobName;
}

void CJob::SetWorkThread(CThread *workthread)
{
    this->m_WorkThread = workthread;
}

CThread* CJob::GetWorkThread(void) const
{
    return this->m_WorkThread;
}


