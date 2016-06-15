#ifndef PTHREADBARRIER_H
#define PTHREADBARRIER_H
#include "CThreadMutex.h"
#include "CCondition.h"

#define BARRIER_FLAG (1UL<<31)
class Barrier_t
{
private:
    volatile int m_Count;
    int m_Total;
    CThreadMutex m_Mutex;
    CCondition m_Cond;

protected:
    void Barrier_init(int count);
    void Barrier_destroy();
public:
    Barrier_t(){}
    Barrier_t(int count);
    ~Barrier_t();
    int Barrier_wait();
};



#endif // PTHREADBARRIER_H
