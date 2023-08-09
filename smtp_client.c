#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("input format incorrect!\n");
    }
    struct sockaddr_in server, client;
    char msg[50] = "hi";
    int t = 0;
    char fromaddr[50], toaddr[50];

    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr  = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));

    client.sin_family = AF_INET;
    client.sin_addr.s_addr = INADDR_ANY;
    client.sin_port = htons(atoi(argv[1]));

    printf("Sending hi to server...\n");
    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending\n");
        exit(0);
    }
    
    socklen_t len = sizeof(server);
    if(recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, &len) < 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "220", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Greeting message is %s\n", msg);
            strcpy(msg, "HELO 127.0.0.1");
            printf("Sending HELO to server...\n");
        }
    }
    if (sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("Error in sending\n");
        exit(0);
    }
    

    if(recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, &len) < 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "250", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Server response is %s\n", msg);
            printf("Enter FROM address\n");
            scanf("%s", fromaddr);
            strcpy(msg, "MAIL FROM");
            strcat(msg, fromaddr);
        }
    }

    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending from address\n");
        exit(0);
    }
    
    if(recvfrom(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, &len)< 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "250", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Server response is %s\n", msg);
            printf("Enter TO address\n");
            scanf("%s", toaddr);
            strcpy(msg, "RCPT TO");
            strcat(msg, toaddr);
        }
    }

    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending to address\n");
        exit(0);
    }

    if(recvfrom(sock_fd, msg, sizeof(msg),0, (struct sockaddr*)&server, &len) < 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "250", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Server response is %s\n", msg);
            strcpy(msg, "DATA");
        }
    }

    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending DATA\n");
        exit(0);
    }

    if(recvfrom(sock_fd, msg, sizeof(msg),0, (struct sockaddr*)&server, &len) < 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "354", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Server response is %s\n", msg);
            printf("Enter the message to send\n");
            while(1)
            {
                char c = getchar();
                if(c == '$')
                {
                    msg[t] = '\0';
                    break;
                }
                if(c == '\0')
                {
                    continue;
                }
                msg[t++] = c;
            }
        }
    }

    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending message\n");
        exit(0);
    }

    sleep(3);
    printf("Sending QUIT to server\n");
    strcpy(msg, "QUIT");

    if(sendto(sock_fd, msg, sizeof(msg), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        printf("error in sending QUIT\n");
        exit(0);
    }

    if(recvfrom(sock_fd, msg, sizeof(msg), 0,(struct sockaddr*)&server, &len) < 0)
    {
        printf("error in receiving\n");
        exit(0);
    }
    else{
        if(strncmp(msg, "221", 3))
        {
            printf("Error in connection..\n");
        }
        else{
            printf("Server response is %s\n", msg);
            printf("Server has sent GOODBYE...\n");
            printf("Closing connection...\n");
            close(sock_fd);
        }
    }
    return 0;
}