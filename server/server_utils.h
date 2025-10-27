struct args_read
{
    int sfd;
    int *conct_count;
};

struct args_write
{
    int *conct_count;
    struct sockaddr_in* clients;
    struct args_read* fd;
};

void struct_info(struct sockaddr_in c_addr);
int thread_create_read(pthread_t* thread,struct args_read* args);
void* server_receive(void*args);
int parse_arg(int argc,char **argv,struct sockaddr_in* server);
void* server_send(void*args);
int thread_create_write(pthread_t* thread,struct args_write*args);