#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
    int socket_desc,client_sock,client_size;
    struct sockaddr_in server_addr,client_addr;
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

    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Not binded\n");
        return 0;
    }
    printf("Binding done\n");

    //listen for client
    if(listen(socket_desc,1)<0)
    {
        printf("error\n");
        return 0;
    }
    printf("Listening...\n");

    //accepting
    client_size=sizeof(client_addr);
    client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);

    if(client_sock<0)
    {
        printf("Cant accept\n");
        return 0;
    }
    printf("client connected at ip:%s and port:%i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

    //recieve client mess
    if(recv(client_sock,client_message,sizeof(client_message),0)<0)
    {
        printf("Couldn't recieve\n");
        return 0;
    }
    printf("Msg from client:%s\n",client_message);

    //reply to client
    strcpy(server_message,"This is server message.");

    if(send(client_sock,server_message,strlen(server_message),0)<0)
    {
        printf("cant send\n");
        return 0;
    }

    //closing socket

    close(client_sock);
    close(socket_desc);

    return 0;
}
