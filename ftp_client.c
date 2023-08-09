#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
    struct sockaddr_in server;
    int sock_desc, k;
    char recvb[100];
    FILE *fp;

    sock_desc = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_desc == -1)
    {
        printf("Error in socket creation");
        exit(1);
    }
    else{
        printf("Socket is created\n");
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(3003);

    k = connect(sock_desc, (struct sockaddr*)&server, sizeof(server));
    if(k == -1)
    {
        printf("Error in connecting to server");
        exit(1);
    }
    else{
        printf("Connected\n");
    }

    printf("Enter the existing filename: ");
    char filename[100];
    scanf("%s", filename);
    printf("Enter the new filename: ");
    char newfilename[100];
    scanf("%s", newfilename);
    fp = fopen(newfilename, "w");   

    k = send(sock_desc, filename, sizeof(filename), 0);
    if(k == -1)
    {
        printf("Error in sending");
        exit(1);
    }
    else{
        printf("Filename sent\n");
    }
    while(1)
    {
        bzero(recvb, 100);
        k = recv(sock_desc, recvb, 100, 0);
        recvb[k] = '\0';
        if(strcmp(recvb, "error") == 0)
        {
            printf("File not found\n");
            exit(1);
        }
        else if(strcmp(recvb, "completed") == 0)
        {
            printf("File transfer completed\n");
            fclose(fp);
            close(sock_desc);
            break;
        }
        else
        {
            fputs(recvb, stdout);
            printf("\n");
        }
        fprintf(fp, "%s", recvb);
    } 
    return 0;
}