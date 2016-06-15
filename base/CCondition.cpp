#include "CCondition.h"
#include "common.h"
CCondition::CCondition(CThreadMutex& m_Mutex) : m_Mutex(m_Mutex)
{
    pthread_cond_init(&m_Cond, NULL);
}

CCondition::~CCondition()
{
    pthread_cond_destroy(&m_Cond);
}

void CCondition::Wait()
{
    std::cout << "thread" << getpid() << std::endl;
    sleep(1);
    CThreadMutexGuard temp(this->m_Mutex);
    pthread_cond_wait(&m_Cond, m_Mutex.GetPthreadMutex());
}

void CCondition::notify()
{
    pthread_cond_signal(&m_Cond);
}

void CCondition::notifyAll()
{
    pthread_cond_broadcast(&m_Cond);
}
