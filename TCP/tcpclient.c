#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_message[2000],client_message[2000];

    memset(server_message,'\0',sizeof(server_message));//clear buffer
    memset(client_message,'\0',sizeof(client_message));

    socket_desc=socket(AF_INET,SOCK_STREAM,0);

    if(socket_desc<0)
    {
        printf("Error ehilr creating socket\n");
        return 0;
    }
    printf("Socket created\n");

    //set port and ip
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Unnable to connect\n");
        return 0;
    }
    printf("connected\n");

    printf("Enter message: ");
    scanf("%s",client_message);

    //send
    if(send(socket_desc,client_message,strlen(client_message),0)<0)
    {
        printf("Unable to send\n");
        return 0;
    }

    //recieve client mess
    if(recv(socket_desc,server_message,sizeof(server_message),0)<0)
    {
        printf("Couldn't recieve\n");
        return 0;
    }
    printf("Msg from server:%s\n",server_message);

    //closing socket

    close(socket_desc);

    return 0;
}
