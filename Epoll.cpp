#include "Epoll.h"

using namespace std;

void Epoll::Epoll_create(Channel *chan,Channel *pchan){
     epoll_fd = epoll_create(MAX_EVENTS);
     T_chan = chan;
     Tp_chan = pchan;
     end = false;
}


void Epoll::Epoll_add(int fd){
     struct epoll_event event;
     event.data.fd = fd;
     event.events = EPOLLOUT|EPOLLET;

     if(epoll_ctl(epoll_fd,EPOLL_CTL_ADD,fd,&event)<0){
          printf("add error\n");
          return ;
     }
}

void Epoll::Epoll_mod(int fd){
     struct epoll_event event;
     event.data.fd = fd;
     event.events = EPOLLIN|EPOLLET;

     if(epoll_ctl(epoll_fd, EPOLL_CTL_MOD, fd, &event) < 0){
        printf("mod error\n");
        return ;
     }
}

void Epoll::Epoll_del(int fd){
     struct epoll_event event;
     event.data.fd = fd;

     if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, &event) < 0){
        printf("del error\n");
        return ;
     }
}

void Epoll::Epoll_job(int i){

     if(i == 0 ) return;

     pthread_mutex_lock(&(Tp_chan->mutex));

          if(Tp_chan->S_conn <= 0){
             end = true;
             pthread_mutex_unlock(&(Tp_chan->mutex));
             return;
          }

         // printf("%d %d \n",Tp_chan->S_conn,i);

          T_chan->succ_conn+=i;
          i = Tp_chan->S_conn >= i?i:Tp_chan->S_conn;
          T_chan->S_conn = i;
          Tp_chan->S_conn -= i;
        
     pthread_mutex_unlock(&(Tp_chan->mutex));
}

void Epoll::Epoll_hander(int ret){

        int succ = 0;

        for(int i = 0;i < ret ; i++){
            int fd = events[i].data.fd;

            if(events[i].events&EPOLLIN){
                char buf[5000];
                int ret;
                if((ret = read(fd,buf,5000))>=0){
                   succ++;
                   Epoll_del(fd);
                   close(fd);
                }

            }
 
            else if(events[i].events&EPOLLOUT){
                   int rlen = strlen(T_chan->req);
                   if(rlen!=write(fd,T_chan->req,rlen)){
                      printf("write error!\n");
                   }    
                   Epoll_mod(fd);
            }
        }

        Epoll_job(succ);
}

void Epoll::Epoll_wait(){

         while(1){
                   int ret = epoll_wait(epoll_fd, events, MAX_EVENTS, timeout);

                   if(ret < 0 ){
                       printf("epoll error\n");
                       break;
                   }

                   else if(ret == 0){
                        break;
                   }

                   else 
                     Epoll_hander(ret);
         }
}

