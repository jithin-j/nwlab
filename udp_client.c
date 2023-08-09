#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(int argc, char* argv[])
{
    struct sockaddr_in client, server;
    if(argc < 3)
    {
        printf("Error: IP address or port number not provided\n");
        exit(1);
    }
    int sock_desc = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_desc == -1)
    {
        printf("Error in socket creation\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[2]));

    char buff[100];
    printf("Enter the message to send\n");
    fgets(buff, 100, stdin);

    if(sendto(sock_desc, buff, 100, 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Error in sending\n");
        exit(1);
    }
    return 0;
}