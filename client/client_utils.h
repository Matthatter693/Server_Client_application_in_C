

struct args
{
int sfd;
};


int parse_arg(int,char **,struct sockaddr_in*);
void struct_info(struct sockaddr_in c_addr);
int thread_create(pthread_t* thread,struct args* args);
void* client_receive(void*args);
