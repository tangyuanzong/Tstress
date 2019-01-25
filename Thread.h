#include "Epoll.h"
#include "Socket.h"
#include <stdio.h>
#include <time.h>
#include <iostream>

typedef void (*callback)(void *arg);

class Thread{

      public:
           void init();
           void start(Channel *chan,Channel *pchan);
           void run();
           void join();
           
      private:
           pthread_t _tid;
           Epoll _epoll;
           bool _start;
           Channel *_chan;
           Channel *_pchan;
};
