#ifndef MYCONDITION_H
#define MYCONDITION_H
#include "common.h"
#include "CThreadMutex.h"
class CCondition
{
private:
    pthread_cond_t m_Cond;
    CThreadMutex &m_Mutex;
public:
    explicit CCondition(CThreadMutex& m_Mutex);
    ~CCondition();
    void Wait();
    void notify();
    void notifyAll();
};

#endif // MYCONDITION_H
