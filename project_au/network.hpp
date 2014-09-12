#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #include <winsock2.h>
  #pragma comment( lib, "ws2_32.lib" )
#else
  typedef int SOCKET;  

  #include <sys/types.h>
  #include <sys/socket.h>
  #include <sys/un.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <errno.h>
  #include <stdlib.h>

#endif

#include <cctype>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include <iostream>
#include <stdio.h>

#include "tools.hpp"



#define X 0
#define Y 1
#define Z 2

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
  #ifndef socklen_t
    typedef int socklen_t;
  #endif
#else
  #ifndef socklen_t
    typedef unsigned int socklen_t;
  #endif
#endif
  


using namespace std;

SOCKET createsocket(unsigned int socket_port);

int sendPos(SOCKET sockfd, SIMPLE_POSE aktpos);

int showNetworkError(const char* error_message);

SOCKET reconnectSocket(SOCKET sock);

int checkAppForOkNok(SOCKET sockfd);

