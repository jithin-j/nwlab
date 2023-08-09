#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int main()
{
    char buff[100];
    int k;
    int sock_desc;
    struct sockaddr_in client;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_desc == -1)
    {
        printf("Error in socket creation");
        exit(1);
    }

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = 3003;

    k = connect(sock_desc, (struct sockaddr*)&client, sizeof(client));
    if(k == -1)
    {
        printf("Error in connecting to server");
        exit(1);
    }

    printf("Enter the message to send\n");
    fgets(buff, 100, stdin);
    k = send(sock_desc, buff, 100, 0);
    if(k == -1)
    {
        printf("Error in sending");
        exit(1);
    }
    close(sock_desc);
    return 0;
}