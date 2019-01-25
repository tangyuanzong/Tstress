#include "Thread.h"
#include<iostream>
#include<stdio.h>
#include<malloc.h>

class Thread_pool{

 public:
      void pool_create(Channel chan);
      void pool_start();
      void pool_end();

 private:
      Thread *pool;
      bool _start;
      Channel *_chan;
      int threads;
};
