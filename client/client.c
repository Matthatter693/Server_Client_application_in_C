#include"client.h"
#include"client_utils.h"


int main(int argc,char*argv[])
{

    struct sockaddr_in client,server;

    //Parsing args
    if(parse_arg(argc,argv,&client))
    {
        return 1;
    }

    struct_info(client);
    int sfd,nsfd,ret;
    pthread_t thread;
    struct args fd;

    sfd=socket(AF_INET,SOCK_STREAM,0);

    if(sfd<0)
    {
        perror("socket fails");
        return 1;
    }
    perror("socket");

    nsfd=connect(sfd,(struct sockaddr*)&client,sizeof(client));
    if(nsfd<0)
    {
        perror("connect fails");
        return 1;
    }
    perror("connect");

    fd.sfd=sfd;
    printf("stored=%d\n",fd.sfd);
    thread_create(&thread,&fd);

    while(1)
    {
        char s[20];
        printf("Enter a message:");
        scanf("%s",s);
        write(sfd,s,strlen(s)+1);
    }
}
