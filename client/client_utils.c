#include"client.h"
#include"client_utils.h"

void struct_info(struct sockaddr_in c_addr)
{
	printf("port no:%d\n",ntohs(c_addr.sin_port));
    printf("ip_address:%s\n",inet_ntoa(c_addr.sin_addr));
}

void* client_receive(void*args)
{
    int ret;
    char buf[100];
    struct args* argument=(struct args*)args;
    while(1)
    {
        printf("fd=%d\n",argument->sfd);
        ret=read(argument->sfd,buf,100);
        if(ret < 0)
        {
            printf("Failed read\n");
            pthread_exit(NULL);
        }
        printf("Message:%s\n",buf);
        if(strcmp(buf,"./exit")==0)
        {
            exit(0);
        }
        bzero(buf,100);
    }
}

int thread_create(pthread_t* thread,struct args* args)
{
    pthread_create(thread,NULL,client_receive,args);
    pthread_detach(*thread);
}

int parse_arg(int argc,char **argv,struct sockaddr_in* client)
{
    static struct option long_options[]=
    {
        {"ipaddr",required_argument,0,'i'},
        {"port",required_argument,0,'p'},
        {"help",no_argument,0,'h'},
        {0,0,0,0}
    };

    int opt;
    int portset=0,ipset=0;

    while(1)
    {

        client->sin_family=AF_INET;
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
                printf("in parse_ipaddr:%s\n",optarg);
                client->sin_addr.s_addr=inet_addr(optarg);
                break;
            case 'p':
                portset=1;
                printf("in_parse_port:%d\n",atoi(optarg));
                client->sin_port=htons(atoi(optarg));
                break;
            case 'h':
                printf("A simple client program in C\n");
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
        printf("Setting default port\n");
        client->sin_addr.s_addr=inet_addr("127.0.0.1");
    }
    if(ipset==0)
    {
        printf("Setting default ip\n");
        client->sin_port=htons(atoi("8080"));
    }
    return 0;
}
