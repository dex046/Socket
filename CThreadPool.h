#ifndef THREADPOOL_H
#define THREADPOOL_H
#include "common.h"
#include "CWorkThread.h"
#include "CThreadMutex.h"
#include "CCondition.h"
using namespace std;

class CThreadPool
{
    friend class CWorkThread;

private:
    unsigned int m_MaxNum;//the max thread num that can create at the same time
    unsigned int m_AvailLow;//the min num of idle thread that should kept
    unsigned int m_AvailHigh;//the max num of idle thread that kept at the same time
    unsigned int m_AvailNum;//the normal thread num of idle num
    unsigned int m_InitNum;//normal thread num

protected:
    CWorkThread* _GetIdleThread();

    void _AppendToIdleList(CWorkThread* jobthread);
    void _MoveToBusyList(CWorkThread* idlethread);
    void _MoveToIdleList(CWorkThread* busythread);

    void _DeleteIdleThread(int num);
    void _CreateIdleThread(int num);

public:
    CThreadMutex m_BusyMutex;
    CThreadMutex m_IdleMutex;
    CThreadMutex m_JobMutex;
    CThreadMutex m_varMutex;//

    CCondition m_BusyCond;
    CCondition m_IdleCond;
    CCondition m_IdleJobCond;
    CCondition m_MaxNumCond;

    vector<CWorkThread*> m_ThreadList;
    vector<CWorkThread*> m_BusyList;
    vector<CWorkThread*> m_IdleList;

    CThreadPool();
    CThreadPool(int initnum);
    virtual ~CThreadPool();

    void SetMaxNum(int maxnum){m_MaxNum = maxnum;}
    int GetMaxNum(void){return m_MaxNum;}

    void SetAvailLowNum(int minnum){m_AvailLow = minnum;}
    int GetAvailLowNum(){return m_AvailLow;}

    void SetAvailHighNum(int maxnum){m_AvailHigh = maxnum;}
    int GetAvailHighNum(){return m_AvailHigh;}

    int GetActualAvailNum(void){return m_AvailNum;}
    int GetAllNum(void){return m_ThreadList.size();}
    int GetBusyNum(void){return m_BusyList.size();}
    void SetInitNum(int initnum){m_InitNum = initnum;}
    int GetInitNum(){return m_InitNum;}

    void TerminateAll(void);
    void Run(CJob* job, void* jobdata);
};





#endif // THREADPOOL_H
