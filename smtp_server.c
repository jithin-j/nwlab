#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in client, server;
    char str[50], msg[20];

    if (argc != 2)
    {
        printf("Input format not correct\n");
    }

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd == -1)
    {
        printf("Socket creation failed\n");
        exit(0);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(atoi(argv[1]));

    int k = bind(sock_fd, (struct sockaddr *)&server, sizeof(server));
    if (k == -1)
    {
        printf("Binding error\n");
        exit(0);
    }

    int len = sizeof(client);
    printf("Server waiting...\n");
    sleep(3);

    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
        exit(0);
    }
    else
    {
        printf("Got message from client: %s\n", str);
        printf("Sending greeting message to client...\n");
        strcpy(str, "220 127.0.0.1");
        sleep(10);
    }

    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        sleep(3);
        exit(0);
    }
    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
        exit(0);
    }
    else
    {
        if (strncmp(str, "HELO", 4))
        {
            printf("Expected HELO from Client\n");
        }
        else
        {
            printf("%s", str);
            printf("Sending response...\n");
            strcpy(str, "250 ok");
        }
    }
    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    sleep(3);

    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
    }
    else
    {
        if (strncmp(str, "MAIL FROM", 9))
        {
            printf("Expected MAIL FROM from Client\n");
        }
        else
        {
            printf("%s", str);
            printf("Sending response...\n");
            strcpy(str, "250 ok");
        }
    }

    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    sleep(3);
    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
    }
    else
    {
        if (strncmp(str, "RCPT TO", 7))
        {
            printf("Expected RCPT TO from Client\n");
        }
        else
        {
            printf("%s", str);
            printf("Sending response...\n");
            strcpy(str, "250 ok");
        }
    }

    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    sleep(3);

    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
    }
    else
    {
        if (strncmp(str, "DATA", 4))
        {
            printf("Expected DATA from Client\n");
        }
        else
        {
            printf("%s", str);
            printf("Sending response...\n");
            strcpy(str, "354 ok");
        }
    }

    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    sleep(3);

    if (recvfrom(sock_fd, msg, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
    }
    else
    {
        printf("mail body received..\n");
        printf("%s", msg);
    }

    if (recvfrom(sock_fd, str, 50, 0, (struct sockaddr *)&client, &len) < 0)
    {
        printf("Error in receiving\n");
    }
    else
    {
        if (strncmp(str, "QUIT", 4))
        {
            printf("Expected QUIT from Client\n");
        }
        else
        {
            printf("%s", str);
            printf("Sending response...\n");
            strcpy(str, "221 ok");
        }
    }

    if (sendto(sock_fd, str, sizeof(str), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    close(sock_fd);
    return 0;
}