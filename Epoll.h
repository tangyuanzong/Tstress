#include <sys/epoll.h>
#include <vector>
#include <stdio.h>
#include <poll.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <pthread.h>

#define MAX_EVENTS 500
#define timeout 3000
#define REQUEST_SIZE 2048
#define MAXHOSTLEN 150
#define MAXTHREADNUM 200

struct Channel
{
       char host[MAXHOSTLEN];
       int  port;
       char req[REQUEST_SIZE];
       int  S_conn;
       int  C_conn;
       int  succ_conn;
       int  Threads;
       pthread_mutex_t mutex;
       long long s_time;
       long long e_time;
};

class Epoll
{
   public:
        void Epoll_create(Channel *chan,Channel *pchan);
        void Epoll_add(int fd);
        void Epoll_mod(int fd);
        void Epoll_del(int fd);
        void Epoll_wait();
        void Epoll_job(int i);
        bool Epoll_end() {return end;}
        void Epoll_hander(int ret);

   private:
        int epoll_fd;
        char *epoll_req;
        bool end;
        Channel *T_chan;
        Channel *Tp_chan;
        struct epoll_event events[MAX_EVENTS];
};
