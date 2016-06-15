#include <iostream>
#include "CPthread-barrier.h"
using namespace std;

#define N 5
//#define COUNT 100
void *do_barrier_bench(void *barrier)
{
    int i;
    Barrier_t *barrier_temp = (Barrier_t*)barrier;
    barrier_temp->Barrier_wait();
//    for(i = 0; i < COUNT; ++i)
//    {
//        barrier.Barrier_wait();
//    }

    return NULL;
}

int main()
{
    //cout << "abc" << endl;
    Barrier_t barrier(N-1);// = new Barrier_t(COUNT);

    pthread_t th[N-1];
    clock_t start, end;
    int i;

    for(int i = 0; i < N - 1; ++i)
    {
        if(pthread_create(&th[i], NULL, do_barrier_bench, (void*)&barrier))
        {
            cout << "pthread failed" << endl;
        }
    }
//cout << "abc" << endl;
    start = clock();

    do_barrier_bench(NULL);

    end = clock();
cout << "abc" << endl;
    for (i = 0; i < N - 1; i++) {
        if (pthread_join(th[i], NULL)) {
            fprintf(stderr, "pthread_join failed");
            exit(EXIT_FAILURE);
        }
    }

    cout << "bench OK" << endl;
    printf("time elasped %lds.\n", (end - start) / CLOCKS_PER_SEC);
    return 0;
}

