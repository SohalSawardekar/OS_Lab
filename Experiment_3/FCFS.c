#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

void PrintGanttchart(processes p[], int n)
{
    printf("\nGantt Chart:\n");

    // Print the top bar
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");

    // Print the process IDs
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

    // Print the bottom bar
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    // Print the time line
    printf("%.0f", p[0].ArrivalTime);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < (int)p[i].BurstTime; j++)
            printf("  ");
        if (p[i].total_time > 9)
            printf("\b"); // backspace: remove 1 space for two-digit numbers
        printf("%.0f", p[i].total_time);
    }
    printf("\n");
}

int main()
{
    processes *p;
    int n;
    float TAT_avg = 0, WT_avg = 0;
    printf("\n\nEnter the no of processes: ");
    scanf("%d", &n);

    p = (processes *)malloc(n * sizeof(processes));
    printf("\n");

    input(p, n);
    sort(p, n);
    cal_TAT(p, n);

    // calculate WT
    for (int i = 0; i < n; i++)
    {
        p[i].WT = p[i].TAT - p[i].BurstTime;
    }

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


/*

Output:

Enter the no of processes: 3


        Process: 1
Enter the burst time: 4
Enter the Arrival time: 1

        Process: 2
Enter the burst time: 5
Enter the Arrival time: 1

        Process: 3
Enter the burst time: 6
Enter the Arrival time: 3


        Process   Arrival Time        Burst Time          TAT       WT        
        1         1.00                4.00                4.00      0.00      
        2         1.00                5.00                9.00      4.00      
        3         3.00                6.00                13.00     7.00      

Average TAT: 8.67
Average WT: 3.67



Gantt Chart:
 -------- ---------- ------------ 
|   P1   |    P2    |     P3     |
 -------- ---------- ------------ 
1        5         10           16




*/