#ifndef MYTHREADMUTEX_H
#define MYTHREADMUTEX_H
#include <pthread.h>
#include "noncopyable.h"
class CThreadMutex : noncopyable
{
private:
    pthread_mutex_t m_Mutex;
public:
    friend class Condition;

    explicit CThreadMutex();
    ~CThreadMutex();
    pthread_mutex_t* GetPthreadMutex();
    void Lock();
//    bool tryLook();
    void unlock();

};

class CThreadMutexGuard : public noncopyable
{
public:
    explicit CThreadMutexGuard(CThreadMutex &m_Mutex);
    virtual ~CThreadMutexGuard();
private:
    CThreadMutex& m_Mutex;
};
#endif // MYTHREADMUTEX_H
