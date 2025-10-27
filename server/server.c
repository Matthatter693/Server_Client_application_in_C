#include "server.h"
#include "server_utils.h"



int main(int argc,char *argv[])
{

    struct sockaddr_in server;
    struct sockaddr_in clients[MAX_CONCTION];
    struct args_read fd[MAX_CONCTION];

    if(parse_arg(argc,argv,&server))
    {
        return 1;
    }


    int sfd,nsfd,ret,conct_count=0;
    pthread_t thread[MAX_CONCTION],thread_write;


    sfd=socket(AF_INET,SOCK_STREAM,0);

    if(sfd<0)
    {
        perror("socket fails");
        return 1;
    }
    perror("socket");

    struct_info(server);
    ret=bind(sfd,(struct sockaddr*)&server,sizeof(server));

    if(ret<0)
    {
        perror("bind fails");
        return 1;
    }
    perror("bind");

    ret=listen(sfd,MAX_CONCTION);

    if(ret<0)
    {
        perror("listen fails");
        return 1;
    }
    perror("listen");

    char s[100];
    int size=sizeof(clients[conct_count]);
    while(1)
    {
        printf("Waiting for client..\n");
        printf("No of connections:%d\n",conct_count);
        nsfd=accept(sfd,(struct sockaddr*)&clients[conct_count],&size);
        if(nsfd<0)
        {
            perror("accept fails");
            return 1;
        }
        perror("accept");

        if(conct_count==0)
        {
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
        printf("nsfd=%d saved=%d saved_no=%d\n",nsfd,fd[conct_count].sfd,*(fd[conct_count].conct_count));
        thread_create_read(&thread[conct_count],&fd[conct_count]);
        conct_count++;
        
    }

    close(sfd);

}
