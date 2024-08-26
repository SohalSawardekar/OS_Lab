#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <climits>
#include <cfloat>
#include <iomanip>

using namespace std;

typedef struct Process
{
    int id;
    float arrivalTime;
    float burstTime;
    float remainingTime;
    float completionTime;
    float turnaroundTime;
    float waitingTime;
} processes;

void input(vector<processes> &p, int n) // Pass vector by reference
{
    for (int i = 0; i < n; i++)
        p[i].id = i + 1;

    cout << "Enter burst time: ";
    for (int i = 0; i < n; i++)
        scanf("%f", &p[i].burstTime);

    cout << "Enter arrival time: ";
    for (int i = 0; i < n; i++)
        scanf("%f", &p[i].arrivalTime);

    // Initialize remaining time
    for (int i = 0; i < n; i++)
        p[i].remainingTime = p[i].burstTime;
}

void PrintTable(vector<processes> &p, int n)
{
    printf("\t%-10s", "Process");
    printf("%-20s", "Arrival Time");
    printf("%-20s", "Burst Time");
    printf("%-10s", "TAT");
    printf("%-10s\n", "WT");
    for (int i = 0; i < n; i++)
    {
        printf("\t%-10d", p[i].id);
        printf("%-20.2f", p[i].arrivalTime);
        printf("%-20.2f", p[i].burstTime);
        printf("%-10.2f", p[i].turnaroundTime);
        printf("%-10.2f\n", p[i].waitingTime);
    }
}

void SRTN(vector<processes> &proc, int n, queue<Process> &ready_queue, queue<double> &time_stamp)
{
    vector<bool> isCompleted(n, false); // To track if a process is completed
    int currentTime = 0;
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed != n)
    {
        float minRemainingTime = FLT_MAX;
        int index = -1;

        // Select the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i] && proc[i].remainingTime < minRemainingTime)
            {
                minRemainingTime = proc[i].remainingTime;
                index = i;
            }
        }

        if (index == -1)
        {
            // No process is ready, so just advance the current time
            currentTime++;
        }
        else
        {
            // Process the selected process
            ready_queue.push(proc[index]);
            proc[index].remainingTime -= 1;
            currentTime++;
            time_stamp.push(currentTime);
            if (proc[index].remainingTime <= 0)
            {
                // Process completed
                proc[index].completionTime = currentTime;
                proc[index].turnaroundTime = proc[index].completionTime - proc[index].arrivalTime;
                proc[index].waitingTime = proc[index].turnaroundTime - proc[index].burstTime;

                totalTAT += proc[index].turnaroundTime;
                totalWT += proc[index].waitingTime;

                isCompleted[index] = true;
                completed++;
            }
        }
    }

    cout << endl;
    PrintTable(proc, n);
    cout << endl;

    // Calculate and display average TAT and average WT
    cout << "\nAverage Turnaround Time: " << totalTAT / n << endl;
    cout << "Average Waiting Time: " << totalWT / n << endl;
}

void PrintGanttChart(queue<Process> ready_queue, queue<double> time_stamp)
{
    // Print process IDs in order of execution
    cout << "Gantt Chart:" << endl;
    cout << " ";

    queue<Process> temp_queue = ready_queue; // Temporary queue to avoid popping from the original
    while (!temp_queue.empty())
    {
        cout << "-----";
        temp_queue.pop();
    }
    cout << endl
         << "|";

    temp_queue = ready_queue; // Reset temp_queue for process ID printing
    while (!temp_queue.empty())
    {
        Process p = temp_queue.front();
        cout << " P" << p.id << " |";
        temp_queue.pop();
    }

    cout << endl
         << " ";

    temp_queue = ready_queue; // Temporary queue for time stamps
    while (!temp_queue.empty())
    {
        cout << "-----";
        temp_queue.pop();
    }
    cout << endl;

    // Print timestamps
    queue<double> temp_time = time_stamp; // Reset temp_time for timestamp printing
    double time = temp_time.front();
    temp_time.pop();
    cout << (int)time;
    while (!temp_time.empty())
    {
        time = temp_time.front();
        temp_time.pop();
        cout << setw(5) << (int)time;
    }
    cout << endl;
}

int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> proc(n);
    queue<Process> ready_queue;
    queue<double> time_stamp;

    input(proc, n);

    float temp_arrival = FLT_MAX; // stores the starting arrival time
    for (int i = 0; i < n; i++)
    {
        if (proc[i].arrivalTime < temp_arrival)
            temp_arrival = proc[i].arrivalTime;
    }

    time_stamp.push(temp_arrival);

    SRTN(proc, n, ready_queue, time_stamp);

    cout << endl
         << endl;

    PrintGanttChart(ready_queue, time_stamp);

    cout << endl
         << endl;
    return 0;
}
