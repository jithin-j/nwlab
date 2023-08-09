#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct packet
{
    char data[1024];
}Packet;

typedef struct frame{
    int frame_kind;
    int seq_no;
    int ack;
    Packet packet;
}Frame;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage %s <port>\n", argv[0]);
        exit(0);
    }

    struct sockaddr_in serverAddr;
    int frame_id = 0;
    Frame frame_recv, frame_send;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sockfd < 0)
    {
        printf("Error in socket creation\n");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(atoi(argv[1]));

    int ack_recvd = 1;
    char buffer[1024];
    while(1)
    {
        if(ack_recvd == 1)
        {
            frame_send.frame_kind = 1;
            frame_send.seq_no = frame_id;
            frame_send.ack = 0;
            printf("Enter data to send: ");
            scanf("%s", frame_send.packet.data);
            sendto(sockfd, &frame_send, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
            printf("Frame sent\n");
        }
        int addr_size = sizeof(serverAddr);
        int frame_recvd_size = recvfrom(sockfd, &frame_recv, sizeof(Frame), 0, (struct sockaddr*)&serverAddr, &addr_size);
        if(frame_recvd_size > 0 && frame_recv.frame_kind == 0 && frame_recv.ack == frame_id+1)
        {
            printf("ACK received\n");
            ack_recvd = 1;
            frame_id = (frame_id+1);
        }
        else
        {
            printf("ACK not received\n");
            ack_recvd = 0;
        }
    }
    return 0;
}