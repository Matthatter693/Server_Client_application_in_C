#include"client.h"
#include"client_utils.h"



int main(int argc,char*argv[])
{

    struct sockaddr_in client;

    //Parsing args
    if(parse_arg(argc,argv,&client))
    {
        return 1;
    }

    //fetching client info
    struct_info(client);

    //Variables
    int sfd,nsfd,ret;
    pthread_t thread;
    struct args fd;
    char s[100];



    /*Creating a socket
    * 1) If created sucess
    * 2) Else Exit
    */
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(sfd<0)
    {
        perror("socket fails");
        return 1;
    }
    perror("socket");


    /*
    *Connect call
    */
    nsfd=connect(sfd,(struct sockaddr*)&client,sizeof(client));
    if(nsfd<0)
    {
        perror("connect fails");
        return 1;
    }
    perror("connect");


    //Creating a thread for receiving msg from server
    fd.sfd=sfd;
    thread_create(&thread,&fd);

    //Client writes the data
    while(1)
    {
        printf("Enter a message:");
        scanf("%s",s);
        ret=write(sfd,s,strlen(s)+1);
        if(ret<0)
        {
            printf("write failed\n");
            close(sfd);
            break;
        }
        if(strcmp(s,"./exit")==0)
        {
            printf("exiting bye\n");
            close(sfd);
            break;
        }
    }
    return 0;
}
