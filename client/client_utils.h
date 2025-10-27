
struct args
{
int sfd;
};

enum ack_status
{
    ACK_SUCESS = 0,
    ACK_FAILURE
};

int parse_arg(int,char **,struct sockaddr_in*);
void struct_info(struct sockaddr_in c_addr);
int thread_create(pthread_t* thread,struct args* args);
void* client_receive(void*args);
enum ack_status server_ack(int sfd);
