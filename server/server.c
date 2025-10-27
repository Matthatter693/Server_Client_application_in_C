#include "server.h"
#include "server_utils.h"

int main(int argc,char *argv[])
{

    struct sockaddr_in server;
    struct server_argument server_args;

    if(parse_arg(argc,argv,&server_args))
    {
        return MAIN_FAIL;
    }

    struct_info(server_args.server);
    int sfd,nsfd,ret,conct_count=0,write_set=0;
    pthread_t thread[server_args.limit],thread_write;

    struct sockaddr_in clients[server_args.limit];
    struct args_read fd[server_args.limit];

    sfd=socket(AF_INET,SOCK_STREAM,0);

    if(sfd<0)
    {
        perror("socket fails");
        return ERR_SYS_SOCK;
    }

    ret=bind(sfd,(struct sockaddr*)&server_args.server,sizeof(server));

    if(ret<0)
    {
        perror("bind fails");
        return ERR_SYS_BIND;
    }

    ret=listen(sfd,server_args.limit);

    if(ret<0)
    {
        perror("listen fails");
        return ERR_SYS_LISTEN;
    }

    char s[100];
    int size=sizeof(clients[conct_count]);

    while(1)
    {
        printf("Waiting for client..\n");
        printf("No of connections:[ %d ]\n",conct_count);
        fflush(stdout);
        nsfd=accept(sfd,(struct sockaddr*)&clients[conct_count],&size);
        if(nsfd<0)
        {
            perror("accept fails");
            return ERR_SYS_ACCEPT;
        }

        if(conct_count<=server_args.limit)
        {
            printf("ACK sent\n");
            ret=3;
            write(nsfd,&ret,sizeof(ret));
        }
        else
        {
            printf("ACK refused\n");
            ret=0;
            write(nsfd,&ret,sizeof(ret));
            continue;
        }

        conct_count++;

        if(write_set==0)
        {
            write_set=1;
            struct args_write argument;
            argument.conct_count=&conct_count;
            argument.clients=clients;
            argument.fd=fd;

            thread_create_write(&thread_write,&argument);
            
        }
        struct_info(clients[conct_count]);

        //Creating thread for connections:
        fd[conct_count].sfd=nsfd;
        fd[conct_count].conct_count=&conct_count;
        fd[conct_count].clients=clients[conct_count];
        thread_create_read(&thread[conct_count],&fd[conct_count]);
        
    }

    close(sfd);

}
