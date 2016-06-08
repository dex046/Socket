#ifndef MYTHREADMANAGER_H
#define MYTHREADMANAGER_H
#include "CThreadPool.h"
#include "CWorkThread.h"
#include "CJob.h"
class CThreadManager
{
private:
    CThreadPool* m_Pool;
    int m_iNumofthread;
public:
    void SetParallelNum(int num);
    CThreadManager();
    CThreadManager(int num);
    virtual ~CThreadManager();

    void Run(CJob *job, void* jobdata);
    void TerminateAll(void);
};

#endif // MYTHREADMANAGER_H
