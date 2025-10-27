#include"server.h"
#include"server_utils.h"

void struct_info(struct sockaddr_in c_addr)
{
	printf("PORT NUMBER = [ %d ] IP ADDRESS = [ %s ]\n",ntohs(c_addr.sin_port),inet_ntoa(c_addr.sin_addr));
}

void* server_receive(void*args)
{
    int ret;
    char buf[100];
    struct args_read* argument=(struct args_read*)args;
    while(1)
    {
        ret=read(argument->sfd,buf,sizeof(buf));
        printf("From [%s]:[%d]:%s\n",inet_ntoa(argument->clients.sin_addr),ntohs(argument->clients.sin_port),buf);
        if(strcmp(buf,"./exit")==0)
        {
            printf("Client disconnected\n");
            //struct_info(argument);
            *(argument->conct_count)=*(argument->conct_count)-1;
            printf("No of connections after exit:[ %d ]\n",*(argument->conct_count));
            fflush(stdout);
            pthread_exit(NULL);
        }
    }
}

void* server_send(void*args)
{
    int ret;
    char s[100];
    struct args_write* argm=(struct args_write*)args;
    while(1)
    {
        printf("Enter the client no & message:");
        scanf("%d %s",&ret,s);
        if(ret>*(argm->conct_count))
        {
            printf("invalid client id\n");
            continue;
        }
        write(argm->fd[ret].sfd,s,sizeof(s));
        if(strcmp(s,"./exit")==0)
        {
            printf("closing thread\n");
            pthread_exit(NULL);
        }
    }
}

int thread_create_read(pthread_t* thread,struct args_read* args)
{

    pthread_create(thread,NULL,server_receive,args);
    pthread_detach(*thread);
}

int thread_create_write(pthread_t* thread,struct args_write*args)
{
    pthread_create(thread,NULL,server_send,args);
    pthread_detach(*thread);
}

int parse_arg(int argc,char **argv,struct server_argument* server)
{
    static struct option long_options[]=
    {
        {"ipaddr",required_argument,0,'i'},
        {"port",required_argument,0,'p'},
        {"limit",required_argument,0,'l'},
        {"help",no_argument,0,'h'},
        {0,0,0,0}
    };

    int opt;
    int portset=0,ipset=0,limitset=0;

    while(1)
    {

        server->server.sin_family=AF_INET;
        int option_index=0;
        opt=getopt_long(argc,argv,"i:p:h",long_options,&option_index);
        if(opt==-1)
        {
            break;
        }

        switch(opt)
        {
            case 0:
                if(long_options[option_index].flag!=0)
                    break;
                break;
            case 'i':
                ipset=1;
                //printf("in parse_ipaddr:%s\n",optarg);
                server->server.sin_addr.s_addr=inet_addr(optarg);
                break;
            case 'p':
                portset=1;
                //printf("in_parse_port:%d\n",atoi(optarg));
                server->server.sin_port=htons(atoi(optarg));
                break;
            case 'l':
                limitset=1;
                server->limit=atoi(optarg);
                break;
            case 'h':
                printf("A simple server program in C\n");
                printf("*******************************************\n");
                printf("%s [start with default options]\n",argv[0]);
                printf("%s -i (or) --ipaddr {IP Addr}\n",argv[0]);
                printf("%s -p (or) --port {port}\n",argv[0]);
                printf("*******************************************\n");
                return 1;
                break;
            case '?':
                printf("write correct arguments :(\n");
                return 1;
                break;
            default:
                printf("does this work?\n");
                return 1;
        }
    }
    if(portset==0)
    {
        printf("Setting default port:[%s]\n",DEFAULT_IP);
        server->server.sin_addr.s_addr=inet_addr(DEFAULT_IP);
    }
    if(ipset==0)
    {
        printf("Setting default ip:[%d]\n",DEFAULT_PORT);
        server->server.sin_port=htons(DEFAULT_PORT);
    }
    if(limitset==0)
    {
        printf("Setting Default Limit:[%d]\n",MAX_CONCTION);
        server->limit=MAX_CONCTION;
    }
    return 0;
}
