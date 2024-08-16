#include <stdio.h>
#include <stdlib.h>

struct processes
{
    int ProcessNo;
    unsigned short int priority;
    float BurstTime;
    float ArrivalTime;
    float TAT;
    float WT;
    float CompletionTime;
} typedef processes;

void input(processes p[], int n)
{
    for (int i = 0; i < n; i++)
        p[i].ProcessNo = i + 1;

    printf("Enter the burst time: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &p[i].BurstTime);

    printf("\nEnter the Arrival time: ");
    for (int i = 0; i < n; i++)
        scanf("%f", &p[i].ArrivalTime);

    printf("\nEnter the priority: ");
    for (int i = 0; i < n; i++)
        scanf("%hd", &p[i].priority);
}

void SortByArrivalTime(processes p[], int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j + 1].ArrivalTime < p[j].ArrivalTime)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void SortByPriority(processes p[], int start, int n)
{
    processes temp;
    for (int i = start; i < n - 1; i++)
    {
        for (int j = start; j < n - i + start - 1; j++)
        {
            if (p[j + 1].priority < p[j].priority)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
            else if (p[j + 1].priority == p[j].priority && p[j + 1].BurstTime < p[j].BurstTime)
            {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void cal_TAT(processes p[], int n)
{
    float TotalTime = 0;
    if (p[0].ArrivalTime > 0)
        TotalTime = p[0].ArrivalTime;

    for (int i = 0; i < n; i++)
    {
        TotalTime += p[i].BurstTime;
        p[i].CompletionTime = TotalTime;
        p[i].TAT = p[i].CompletionTime - p[i].ArrivalTime;
        p[i].WT = p[i].TAT - p[i].BurstTime;

        if (i + 1 < n && p[i + 1].ArrivalTime <= TotalTime)
            SortByPriority(p, i + 1, n);
    }
}

void PrintTable(processes p[], int n)
{
    printf("\t%-10s", "Process");
    printf("%-20s", "Arrival Time");
    printf("%-20s", "Burst Time");
    printf("%-20s", "Priority");
    printf("%-10s", "TAT");
    printf("%-10s\n", "WT");
    for (int i = 0; i < n; i++)
    {
        printf("\t%-10d", p[i].ProcessNo);
        printf("%-20.2f", p[i].ArrivalTime);
        printf("%-20.2f", p[i].BurstTime);
        printf("%-20hd", p[i].priority);
        printf("%-10.2f", p[i].TAT);
        printf("%-10.2f\n", p[i].WT);
    }
}

void PrintGanttchart(processes p[], int n)
{
    printf("\nGantt Chart:\n");

    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime - 1; j++)
            printf(" ");
        printf("P%d", p[i].ProcessNo);
        for (int j = 0; j < (int)p[i].BurstTime - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    printf("%.0f", p[0].ArrivalTime);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("  ");
        if (p[i].CompletionTime > 9)
            printf("\b");
        printf("%.0f", p[i].CompletionTime);
    }
    printf("\n");
}

int main()
{
    processes *p;
    int n;
    float TAT_avg = 0, WT_avg = 0;
    printf("\n\nEnter the number of processes: ");
    scanf("%d", &n);

    p = (processes *)malloc(n * sizeof(processes));
    printf("\n");
    input(p, n);
    SortByArrivalTime(p, n);
    cal_TAT(p, n);

    printf("\n\n");
    PrintTable(p, n);

    for (int i = 0; i < n; i++)
    {
        TAT_avg += p[i].TAT;
        WT_avg += p[i].WT;
    }

    TAT_avg /= n;
    WT_avg /= n;

    printf("\n");
    printf("Average TAT: %.2f\n", TAT_avg);
    printf("Average WT: %.2f\n", WT_avg);

    printf("\n\n");
    PrintGanttchart(p, n);

    printf("\n\n");
    free(p);
    return 0;
}
