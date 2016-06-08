#include "CCondition.h"
void CCondition::Wait()
{
    pthread_cond_wait(&this->m_Cond, &this->m_Mutex);
}
