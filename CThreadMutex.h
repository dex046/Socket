#ifndef MYTHREADMUTEX_H
#define MYTHREADMUTEX_H
#include <pthread.h>
#include "noncopyable.h"
class CThreadMutex : public noncopyable
{
private:
    pthread_mutex_t m_Mutex;
public:
    CThreadMutex();
    virtual ~CThreadMutex();
    pthread_mutex_t GetPthreadMutex();
    void Lock();
//    bool tryLook();
    void unlock();

};

class CThreadMutexGuard : public noncopyable
{
public:
    CThreadMutexGuard(CThreadMutex &m_Mutex);
    virtual ~CThreadMutexGuard();
private:
    CThreadMutex& m_Mutex;
};
#endif // MYTHREADMUTEX_H
