#include<stdio.h>
void main()
{
    printf("Enter bucket size: \n");
    int bucket_size;
    scanf("%d", &bucket_size);
    printf("Enter output rate: \n");
    int output_rate;
    scanf("%d", &output_rate);
    printf("Enter number of packets: \n");
    int n;
    scanf("%d", &n);
    int bucket = 0;
    while(n != 0)
    {
        printf("Enter the incoming packet size: \n");
        int incoming_packet_size;
        scanf("%d", &incoming_packet_size);
        if(incoming_packet_size < bucket_size - bucket)
        {
            bucket += incoming_packet_size;
            printf("Bucket status: %d out of %d\n", bucket, bucket_size);
        }
        else
        {
            printf("Packet size greater than bucket space. Packet discarded\n");
        }
        bucket -= output_rate;
        if(bucket < 0)
        {
            bucket = 0;
        }
        printf("After outgoing, bucket status: %d out of %d\n", bucket, bucket_size);
        n--;
    }
}