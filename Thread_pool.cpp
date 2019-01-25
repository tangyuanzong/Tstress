#include "Thread_pool.h"

using namespace std;

void Thread_pool::pool_create(Channel chan){
        threads = chan.Threads;
        _chan = (Channel *) malloc(sizeof(Channel) * threads + 1);

        int x = chan.C_conn / threads;
        int y = chan.C_conn % threads;

        _chan[threads] = chan;

        if(pthread_mutex_init(&(_chan[threads].mutex),NULL)!=0){
           printf("mutex init error\n");
           return;
        }

        for(int i= 0 ; i < threads ; i++){
           _chan[i] = chan;
           _chan[i].S_conn = x;

           if(y>0){
              _chan[i].S_conn++;
              y--;
           }
        }

        pool = (Thread *) malloc(sizeof(Thread) * threads);
}

void Thread_pool::pool_start(){

        for(int x = 0;x < threads;x++){
            pool[x].start(&_chan[x],&_chan[threads]);
        }
}

void Thread_pool::pool_end(){

        for(int i=0;i < threads;i++){
             pool[i].join();
        }
        
        float per = 0;

        for(int x=0 ; x< threads;x++){
          float s = (float ) ((_chan[x].e_time - _chan[x].s_time) / 1000000);
          per += (_chan[x].succ_conn / s);
        }

        pthread_mutex_destroy(&(_chan[threads].mutex));

        printf("\nPerformance : %.2f H / S \n",per / threads);
        free(_chan);
        free(pool);
}
