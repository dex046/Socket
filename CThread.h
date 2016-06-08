#ifndef MYTHREAD_H
#define MYTHREAD_H
#include "common.h"
#include "CJob.h"
using namespace std;
enum ThreadState{IDLE, BUSY};
class CThread
{
private:
    int m_Errcode;
    //Semaphore m_ThreadSemaphore;
    unsigned long m_ThreadID;
    string m_ThreadName;

    bool m_Detach;
    bool m_CreateSuspended;
    ThreadState m_ThreadState;

protected:
    void _SetErrcode(int errcode);
    static void* _ThreadFunction(void*);
public:
    //Mythread();
    CThread(bool m_Detach = false, bool m_CreateSuspended = false);
    virtual ~CThread();
    virtual void run(void) = 0;
    void SetThreadState(ThreadState state){m_ThreadState = state;}

    bool Terminate(void);
    bool Start(void);
    void Exit(void);
    bool Wakeup(void);

    ThreadState GetThreadState(void){return m_ThreadState;}
    int GetLastError(void){return m_Errcode;}
    void SetThreadName(std::string name){this->m_ThreadName = name;}
    std::string GetThreadName(){return this->m_ThreadName;}
    int GetThreadID(){return m_ThreadID;}

    bool SetPriority(int priority);
    int GetPriority(void);
    int GetConcurrency(void);
    void SetConcurrency(int num);
    bool Detach(void);
    bool Join(void);
    bool Yield(void);
    int Self(void);
};

#endif // MYTHREAD_H

