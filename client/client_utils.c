#include"client.h"
#include"client_utils.h"

void struct_info(struct sockaddr_in c_addr)
{
	printf("port no:%d\n",ntohs(c_addr.sin_port));
    printf("ip_address:%s\n",inet_ntoa(c_addr.sin_addr));
}

void* client_receive(void*args)
{
    char buf[100];
    struct args* argument=(struct args*)args;
    while(1)
    {
        printf("fd=%d\n",argument->sfd);
        read(argument->sfd,buf,100);
        printf("Message:%s\n",buf);
        if(strcmp(buf,"./exit")==0)
        {
            exit(0);
        }
        bzero(buf,100);
        sleep(3);
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

    while(1)
    {

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
                printf("in parse_ipaddr:%s\n",optarg);
                client->sin_addr.s_addr=inet_addr(optarg);
                break;
            case 'p':
                printf("in_parse_port:%d\n",atoi(optarg));
                client->sin_port=htons(atoi(optarg));
                break;
            case 'h':
                printf("A simple client program in C\n");
                printf("*******************************************\n");
                printf("To write message:%s --write message (or) %s -w message\n",argv[0],argv[0]);
                printf("To read message:%s --read (or) %s -r\n",argv[0],argv[0]);
                printf("To help:%s --help (or) %s -h\n",argv[0],argv[0]);
                printf("*******************************************\n");
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
    return 0;
}
