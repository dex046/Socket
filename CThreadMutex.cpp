#include "CThreadMutex.h"
CThreadMutex::CThreadMutex()
{
    pthread_mutex_init(&m_Mutex, NULL);
}

CThreadMutex::~CThreadMutex()
{
    pthread_mutex_destroy(&m_Mutex);
}

pthread_mutex_t CThreadMutex::GetPthreadMutex()
{
    return this->m_Mutex;
}

void CThreadMutex::Lock()
{
    pthread_mutex_lock(&m_Mutex);
}

void CThreadMutex::unlock()
{
    pthread_mutex_unlock(&m_Mutex);
}

CThreadMutexGuard::CThreadMutexGuard(CThreadMutex& m_Mutex) : m_Mutex(m_Mutex)
{
    m_Mutex.Lock();
}

CThreadMutexGuard::~CThreadMutexGuard()
{
    m_Mutex.unlock();
}

//CThreadMutex::Lock()
//{

//}

//CThreadMutex::unlock()
//{

//}

//CThreadMutex::tryLook()
//{

//}
