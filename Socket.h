#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

class Socket
{
     public:
       void Build_Socket(const char *host, int Port);
       int Get_Socket() {return sock;}
       void Close_Socket();
   
     private:
       int sock;
};
