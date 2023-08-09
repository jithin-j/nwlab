#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    FILE *fp;
    struct sockaddr_in server, client;
    char rcv[100], fileread[100];
    int sock_desc, temp_sock_desc;
    int k,n;
    int len;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_desc == -1)
    {
        printf("Error in socket creation\n");
        exit(1);
    }
    else{
        printf("Socket is created\n");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
    {
        printf("Error in binding\n");
        exit(1);
    }
    else{
        printf("Binded\n");
    }

    k = listen(sock_desc, 5);
    if (k == -1)
    {
        printf("Error in listening\n");
        exit(1);
    }
    len = sizeof(client);
    temp_sock_desc = accept(sock_desc, (struct sockaddr *)&client, &len);
    if (temp_sock_desc == -1)
    {
        printf("Error in temporary socket creation\n");
        exit(1);
    }
    else{
        printf("Connection accepted\n");
    }

    n = recv(temp_sock_desc, rcv, 100, 0);
    rcv[n] = '\0';
    fp = fopen(rcv, "r");
    printf("Filename received: %s", rcv);
    if (fp == NULL)
    {
        send(temp_sock_desc, "error", 5, 0);
        printf("File not found\n");
        close(temp_sock_desc);
    }
    else
    {
        while (fgets(fileread, sizeof(fileread), fp) != NULL)
        {
            if (send(temp_sock_desc, fileread, sizeof(fileread), 0) < 0)
            {
                printf("Can't send file contents\n");
            }
            sleep(1);
        }
        if (feof(fp))
        {
            send(temp_sock_desc, "completed", 100, 0);
        }
    }
}