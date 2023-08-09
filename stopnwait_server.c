#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct packet
{
    char data[1024];
}Packet;

typedef struct frame
{
    int frame_kind;
    int seq_no;
    int ack;
    Packet packet;
}Frame;

int main(int argc, char *argv[])
{
    int frame_id = 0;
    Frame frame_recv, frame_send;
    if(argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    struct sockaddr_in serverAddr, newAddr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("Error in socket creation\n");
        exit(1);
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(atoi(argv[1]));

    int k = bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(k < 0)
    {
        printf("Error in binding\n");
        exit(1);
    }
    socklen_t len = sizeof(newAddr);
    while(1)
    {
        int frame_size = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&newAddr, &len);
        if(frame_size > 0 && frame_recv.frame_kind == 1 && frame_recv.seq_no == frame_id)
        {
            printf("Frame received: %s\n", frame_recv.packet.data);
            frame_send.frame_kind = 0;
            frame_send.ack = frame_recv.seq_no+1;
            frame_send.seq_no = 0;
            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&newAddr, sizeof(newAddr));
            printf("ACK sent\n");
        }
        else
        {
            printf("Frame not received\n");
        }
        frame_id++;
    }
}