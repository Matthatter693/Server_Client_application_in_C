#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<argp.h>

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

//MACROS

#define ARG_COUNT 3
#define MAX_CONCTION 2
#define DEFAULT_PORT 8080
#define DEFAULT_IP "0.0.0.0"
