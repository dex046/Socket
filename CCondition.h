#ifndef MYCONDITION_H
#define MYCONDITION_H
#include "common.h"
class CCondition
{
private:
    pthread_cond_t m_Cond;
    pthread_mutex_t m_Mutex;
public:
    CCondition();
    ~CCondition();
    void Wait();
};

#endif // MYCONDITION_H
