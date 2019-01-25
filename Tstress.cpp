#include "Tstress.h"

void Tstress::Stress_init(){
     success = 0;
     stresstime = 30;
     proxyhost = NULL;
     tchan.port = 80;
     tchan.succ_conn = 0;
}

void Tstress::Stress_usage(){

      printf("T_Stress [option].....\n"
            "  -T                The number of Threads.\n"
            "  -S                Total connections.\n"
            "  -C                The number of Concurrent connections.\n"
      );

}

void Tstress::Stress_http(const char *url){

     strcpy(tchan.req,"GET");
     strcat(tchan.req," ");

     if(NULL==strstr(url,"://")){
	  printf("%s: is not a valid URL.\n",url);
	  return;
     }

     if(strlen(url)>1500){
         printf("URL is too long.\n");
	 return;
     }

     if(strncasecmp(url,"http://",7)!=0){
        printf("Only HTTP protocol is supported \n");
        return ;
     }

     int i = strstr(url,"://")  - url + 3;
     int j = strstr(url + i , "/") - url;

     if(strstr(url + i, "/") == NULL){
        printf("Hostname need ends with '/'\n");
        return;
     }
    
    
    strcat(tchan.req,strstr(url + i , "/"));
    strcat(tchan.req," HTTP/1.0\r\n");

    strcat(tchan.req,"User-Agent: Tstress 1.0\r\n");

    strcat(tchan.req,"Host: ");
    strncpy(tchan.host,url + i , j - i);
    strcat(tchan.req,tchan.host);

    strcat(tchan.req,"\r\n");
    strcat(tchan.req,"\r\n"); 
   // strcat(request,"Connection: close\r\n");

}

void Tstress::Stress_opt(int argc, char *argv[]){

     int opt = 0;         
     int options_index = 0;
     static const struct option long_options[]={{NULL,0,NULL,0}};

     while((opt = getopt_long(argc,argv,"T:S:C:",long_options,&options_index))!=EOF){
             
          switch(opt){
               case 'T': tchan.Threads = atoi(optarg); break;
               case 'S': tchan.S_conn = atoi(optarg); break;
               case 'C': tchan.C_conn = atoi(optarg); break;
          }
     }
}

void Tstress::Stress_start(){

     Socket _sock;
     _sock.Build_Socket(tchan.host,tchan.port);
     int s = _sock.Get_Socket();
     if(s < 0  ) {
        printf("connect error\n");
        return;
     }
     close(s);

     printf("\nTstress Starting! Author: tyz , Date: 2019/1/22 \n"); 
     printf("Threads: %d\n",tchan.Threads);
     printf("Sum connections: %d\n",tchan.S_conn);
     printf("Concurrent connections: %d\n\n",tchan.C_conn);
     printf("%s",tchan.req);

     Thread_pool tpool;
     tpool.pool_create(tchan);
     tpool.pool_start();
     tpool.pool_end();

}
