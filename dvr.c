#include<stdio.h>

struct router
{
    unsigned cost[20];
    unsigned from[20];
}routingTable[10];

void main()
{
    int routers = 0;
    int costmatrix[20][20];
    printf("Enter the number of routers: ");
    scanf("%d", &routers);
    printf("Enter the cost matrix : \n");
    for(int i = 0; i < routers; i++)
    {
        for(int j = 0; j < routers; j++)
        {   
            scanf("%d", &costmatrix[i][j]);
            costmatrix[i][i] = 0;
            routingTable[i].cost[j] = costmatrix[i][j];
            routingTable[i].from[j] = j;
        }
    }
    int otherRoutesExists;
    do
    {
        otherRoutesExists = 0;
        for(int i = 0; i < routers; i++)
        {
            for(int j = 0; j < routers; j++)
            {
                for(int k = 0; k < routers; k++)
                {
                    if(routingTable[i].cost[j] > costmatrix[i][k] + routingTable[k].cost[j])
                    {
                        routingTable[i].cost[j] = costmatrix[i][k] + routingTable[k].cost[j];
                        routingTable[i].from[j] = k;
                        otherRoutesExists = 1;
                    }
                }
            }
        }
    } while (otherRoutesExists != 0);
    for(int i = 0; i < routers; i++)
    {
        printf("For router %d\n", i+1);
        for(int j = 0; j < routers; j++)
        {
            printf("Node %d via %d Distance %d\n", j+1, routingTable[i].from[j]+1, routingTable[i].cost[j]);
        }
    }
    printf("\n\n");
}