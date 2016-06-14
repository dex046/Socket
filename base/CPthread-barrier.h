#ifndef PTHREADBARRIER_H
#define PTHREADBARRIER_H
#include "CThreadMutex.h"
#include "CCondition.h"

#define BARRIER_FLAG (1UL<<31)
class Barrier_t
{
private:
    int m_Count;
    int m_Total;
    CThreadMutex m_Mutex;
    CCondition m_Cond;
protected:
    Barrier_init(Barrier_t *b, int count);
    Barrier_destroy();
public:
    Barrier_t();
    ~Barrier_t();
};



#endif // PTHREADBARRIER_H
