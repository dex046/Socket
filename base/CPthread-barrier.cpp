#include "CPthread-barrier.h"
void Barrier_t::Barrier_destroy()
{
}

void Barrier_t::Barrier_init(Barrier_t *b, int count)
{
    b->m_Count = count;
    b->total = BARRIER_FLAG;
}

void Barrier_t::Barrier_wait()
{
    //CThreadMutexGuard temp(this->m_Mutex);

    while(this->m_Count > BARRIER_FLAG)//什么时候会出现大于的情况
    {
        m_Cond.Wait();
    }

    if(this->m_Total == BARRIER_FLAG)
    {
        this->m_Total = 0;
    }

    this->m_Total++;

    if(this->m_Total == this->m_Count)
    {
        this->m_Total += BARRIER_FLAG - 1;//为什么要加BARRIER_FLAG - 1
        this->m_Cond.notifyAll();
    }
}
