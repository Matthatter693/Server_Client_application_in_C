#include "server.h"
#include "server_utils.h"


int main(int argc,char *argv[])
{

    if(argc!=3)
    {
        printf("wrong usage\n");
        return 0;
    }

    int sfd,nsfd,ret;
    struct sockaddr_in server,client;

    printf("argv[2]=%s argv[3]=%s\n",argv[1],argv[2]);

    sfd=socket(AF_INET,SOCK_STREAM,0);

    if(sfd<0)
    {
        perror("socket fails");
        return 1;
    }
    perror("socket");

    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[1]));
    server.sin_addr.s_addr = inet_addr(argv[2]);


    ret=bind(sfd,(struct sockaddr*)&server,sizeof(server));

    if(ret<0)
    {
        perror("bind fails");
        return 1;
    }
    perror("bind");

    ret=listen(sfd,2);

    if(ret<0)
    {
        perror("listen fails");
        return 1;
    }
    perror("listen");

    int size=sizeof(client);
    while(1)
    {
        if((nsfd=accept(sfd,(struct sockaddr*)&client,&size)<0))
        {
            perror("accept fails");
            return 1;
        }
        perror("accept");
    }


}
