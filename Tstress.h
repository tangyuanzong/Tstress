#include "Thread_pool.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/param.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <rpc/types.h>
#include <getopt.h>
#include <netdb.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <iostream>
#include <sys/epoll.h>
#include <fcntl.h>
#include <sys/time.h>
#include <time.h>
#include <stdarg.h>
#include <pthread.h>


class Tstress
{
      public:
         void Stress_init();
         void Stress_usage();
         void Stress_http(const char *url);
         void Stress_opt(int argc, char *argv[]);
         void Stress_start();

      private:
         Channel tchan;
         int success;
         int  stresstime;
         char *proxyhost;
};

