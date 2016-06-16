#ifndef MYWORKTHREAD_H
#define MYWORKTHREAD_H
#include "CCondition.h"
#include "CThread.h"
#include "CThreadMutex.h"
#include "CThreadPool.h"
class CThreadPool;
class CWorkThread : public CThread
{
private:
    CThreadPool* m_ThreadPool;
    CJob* m_Job;
    void* m_JobData;

    CThreadMutex& m_Mutex;//m_Mutex和m_WorkMutex的区别
    bool m_IsEnd;//

public:
    CCondition& m_JobCond;//为什么属性是public
    CThreadMutex& m_WorkMutex;

    explicit CWorkThread(CThreadMutex &m_Mutex, CCondition &m_JobCond, CThreadMutex &m_WorkMutex);
    virtual ~CWorkThread();
    void Run();
    void Start();
    void SetJob(CJob* job, void* jobdata);
    CJob* GetJob(){return this->m_Job;}
    void SetThreadPool(CThreadPool* threadpool);
    CThreadPool* GetThreadPool(){return this->m_ThreadPool;}
};
#endif // MYWORKTHREAD_H
