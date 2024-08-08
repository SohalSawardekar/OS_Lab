#include <stdio.h>
#include <stdlib.h>

#define max 1000

struct processes
{
    int ProcessNo;
    float BurstTime;
    float ArrivalTime;
    float TAT;
    float WT;
    float total_time;
} typedef processes;

void input(processes p[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("\n\tProcess: %d\n", i + 1);
        p[i].ProcessNo = i + 1;
        printf("Enter the burst time: ");
        scanf("%f", &p[i].BurstTime);
        printf("Enter the Arrival time: ");
        scanf("%f", &p[i].ArrivalTime);
    }
}

void sort(processes p[], int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j + 1].ArrivalTime < p[j].ArrivalTime)
            {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }
}

void cal_TAT(processes p[], int n)
{
    float TotalTime = 0;
    for (int i = 0; i < n; i++)
    {
        if (p[i].ArrivalTime > TotalTime)
        {
            TotalTime = p[i].ArrivalTime; // CPU is idle until this process arrives
        }
        p[i].TAT = p[i].BurstTime + TotalTime - p[i].ArrivalTime;
        TotalTime += p[i].BurstTime;
        p[i].total_time = TotalTime;
    }
}

void PrintTable(processes p[], int n)
{
    printf("\t%-10s", "Process");
    printf("%-20s", "Arrival Time");
    printf("%-20s", "Burst Time");
    printf("%-10s", "TAT");
    printf("%-10s\n", "WT");
    for (int i = 0; i < n; i++)
    {
        printf("\t%-10d", p[i].ProcessNo);
        printf("%-20.2f", p[i].ArrivalTime);
        printf("%-20.2f", p[i].BurstTime);
        printf("%-10.2f", p[i].TAT);
        printf("%-10.2f\n", p[i].WT);
    }
}

void SRTF(processes p[], int n)
{
    processes ProcessorStack[max];
    float RemainTimeStack[max] = -1;
    int top = -1;

    top = 0;
    ProcessorStack[top] = p[top];
    RemainTimeStack[top] = p[top].BurstTime;
    
}

int main()
{
    int n;
    processes *p;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    p = (processes *)malloc(n * sizeof(processes));

    input(p, n);
    sort(p, n);

    printf("\n\n");
    free(p);
    return 0;
}
