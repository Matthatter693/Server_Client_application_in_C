/*
---------ENUMS FOR STATUS-----------
*/

/*--Main status--*/
enum main_status
{
    MAIN_SUCESS=0, //if success
    MAIN_FAIL,     //if failed
};


/*--Sys call statuses--*/
enum sys_call_fail
{
    SYS_SUCCESS=0,  //general success
    ERR_SYS_SOCK,   //socket() error
    ERR_SYS_BIND,   //bind() error
    ERR_SYS_ACCEPT, //accept() error
    ERR_SYS_LISTEN, //listen() error
    ERR_SYS_CONNECT, //connect() error
};

/*---STRUCTURES---*/

struct server_argument
{
    int limit;
    struct sockaddr_in server;
};


struct args_read
{
    int sfd;
    struct sockaddr_in clients;
    int *conct_count;
};

struct args_write
{
    int *conct_count;
    struct sockaddr_in* clients;
    struct args_read* fd;
};


/*----FUNCTION DECLARATIONS----*/
void struct_info(struct sockaddr_in c_addr);
int thread_create_read(pthread_t* thread,struct args_read* args);
void* server_receive(void*args);
int parse_arg(int argc,char **argv,struct server_argument* server);
void* server_send(void*args);
int thread_create_write(pthread_t* thread,struct args_write*args);
