#include "Thread.h"

using namespace std;

volatile int timerexpired=0;

void alarm_hander(int signal){
     timerexpired=1;
}

void *f(void *arg){
     ((Thread *) arg)->run();
}

void Thread::init(){
     _start = false;
}

void Thread::start(Channel *chan,Channel *pchan){
        _start = true;
        if(pthread_create(&_tid, NULL, f, this) <0){
             _start = false;
             printf("create thread error");
        }
        _chan = chan;
        _pchan = pchan;
        _epoll.Epoll_create(_chan,_pchan);

} 

void Thread::run(){

     timeval tv;
     gettimeofday(&tv,NULL);
     _chan->s_time = tv.tv_sec * 1000 * 1000 + tv.tv_usec;

     while(1){

        if(!_start) continue;
        if(_epoll.Epoll_end())   break;

        while(_chan->S_conn > 0){
              Socket _socket;
              _socket.Build_Socket(_chan->host,_chan->port);
              int i = _socket.Get_Socket();
              if( i < 0 ){
                 printf("create socket error!\n");
                 continue;
              }
             _epoll.Epoll_add(i);
             _chan->S_conn--;
         }
        
       if(!_epoll.Epoll_end()) {
         _epoll.Epoll_wait();
       }
     }

     gettimeofday(&tv,NULL);
     _chan->e_time = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
}

void Thread::join(){
     pthread_join(_tid,NULL);
}

