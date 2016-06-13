#ifndef MYJOB_H
#define MYJOB_H
#include "common.h"
using namespace std;
class CThread;
class CJob
{
private:
    int m_JobNo;
    string m_JobName;
    CThread* m_WorkThread;
public:
    CJob();
    virtual ~CJob();

    int GetJobNo(void)const;
    void SetJobNo(int jobno);
    string GetJobName(void)const;
    void SetJobName(string jobname);
    CThread* GetWorkThread(void) const;
    void SetWorkThread(CThread* workthread);
    virtual void Run(void* rundata) = 0;
};
#endif // MYJOB_H
