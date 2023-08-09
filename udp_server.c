#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in server, client;
    if(argc < 2)
    {
        printf("Error: Port number not provided\n");
        exit(1);
    }
    int sockdesc = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockdesc == -1)
    {
        printf("Error in socket creation\n");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    if(bind(sockdesc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Error in binding\n");
        exit(1);
    }
    char buff[100];
    printf("Server is waiting...\n");
    socklen_t len = sizeof(client);
    if(recvfrom(sockdesc, buff, 100, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
        exit(1);
    }
    printf("Message got from client is : %s\n", buff);
    return 0;
}