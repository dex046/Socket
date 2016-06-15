#include "CPthread-barrier.h"
#include "common.h"
using namespace std;
void Barrier_t::Barrier_destroy()
{
    {
        CThreadMutexGuard guard(this->m_Mutex);
        while(this->m_Total > BARRIER_FLAG)
        {
            m_Cond.Wait();
        }
    }
}

void Barrier_t::Barrier_init(int count)
{
    this->m_Count = count;
    this->m_Total = BARRIER_FLAG;
}

int Barrier_t::Barrier_wait()
{
    //CThreadMutexGuard temp(this->m_Mutex);
//std::cout << "thread" << getpid() << std::endl;
    cout << "mul" << endl;
sleep(1);
    //CThreadMutexGuard temp(this->m_Mutex);
    cout << m_Count << endl;
//    while(4 > BARRIER_FLAG)//什么时候会出现大于的情况
//    {cout << "im in" << endl;
//        m_Cond.Wait();
//    }

cout << "thread" << endl;
sleep(1);

    {


        CThreadMutexGuard guard(this->m_Mutex);
        if(this->m_Total == BARRIER_FLAG)
        {
            this->m_Total = 0;
        }

        this->m_Total++;

        if(this->m_Total == this->m_Count)
        {
            this->m_Total += BARRIER_FLAG - 1;//为什么要加BARRIER_FLAG - 1
            this->m_Cond.notifyAll();

            return PTHREAD_BARRIER_SERIAL_THREAD;//-1  The constant PTHREAD_BARRIER_SERIAL_THREAD is defined in <pthread.h> and its value shall be distinct from any other value returned by pthread_barrier_wait().
        }
        else
        {
            while(this->m_Total < BARRIER_FLAG)
            {
                m_Cond.Wait();
            }

            this->m_Total--;

            if(this->m_Total == BARRIER_FLAG)
            {
                m_Cond.notifyAll();
            }

            return 0;
        }
    }
}

Barrier_t::Barrier_t(int count)
{
    Barrier_init(count);
}

Barrier_t::~Barrier_t()
{
    Barrier_destroy();
}
