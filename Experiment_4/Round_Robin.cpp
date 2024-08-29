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

void sort(vector<processes> &p, int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j + 1].arrivalTime < p[j].arrivalTime)
            {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
            else if (p[j + 1].arrivalTime == p[j].arrivalTime)
            {
                if (p[j + 1].burstTime < p[j].burstTime)
                {
                    temp = p[j + 1];
                    p[j + 1] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void Finalsort(vector<processes> &p, int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j + 1].id < p[j].id)
            {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }
}

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

void RR(vector<processes> &proc, int n, queue<Process> &ready_queue, queue<double> &time_stamp, float time_slice)
{
    int currentTime = 0;
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    queue<int> rq;
    vector<bool> isInQueue(n, false);

    while (completed != n)
    {
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isInQueue[i] && proc[i].remainingTime > 0)
            {
                rq.push(i);
                isInQueue[i] = true;
            }
        }

        if (rq.empty())
        {
            // If no process is ready, advance the current time
            currentTime++;
            continue;
        }

        int index = rq.front();
        rq.pop();

        // Process the selected process
        ready_queue.push(proc[index]);
        float executionTime = min(time_slice, proc[index].remainingTime);
        proc[index].remainingTime -= executionTime;
        currentTime += executionTime;
        time_stamp.push(currentTime);

        // If process has finished executing
        if (proc[index].remainingTime <= 0)
        {
            proc[index].completionTime = currentTime;
            proc[index].turnaroundTime = proc[index].completionTime - proc[index].arrivalTime;
            proc[index].waitingTime = proc[index].turnaroundTime - proc[index].burstTime;

            totalTAT += proc[index].turnaroundTime;
            totalWT += proc[index].waitingTime;

            completed++;
        }
        else
        {
            // If process has not finished, put it back in the queue after adding any new arrivals
            for (int i = 0; i < n; i++)
            {
                if (proc[i].arrivalTime <= currentTime && !isInQueue[i] && proc[i].remainingTime > 0)
                {
                    rq.push(i);
                    isInQueue[i] = true;
                }
            }
            rq.push(index); // Add the current process back to the end of the queue
        }
    }

    Finalsort(proc, n);
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

void compress_queue(queue<Process> &ready_queue, queue<double> &time_stamp)
{
    queue<Process> temp_ready_queue = ready_queue, temp1;
    queue<double> temp_time_stamp = time_stamp, temp2;
    Process p = temp_ready_queue.front();
    double ts = temp_time_stamp.front();
    temp2.push(ts);
    temp_ready_queue.pop();
    temp_time_stamp.pop();
    ts = temp_time_stamp.front();
    temp_time_stamp.pop();

    while (!temp_ready_queue.empty())
    {
        if (p.id == temp_ready_queue.front().id)
        {
            ts = temp_time_stamp.front();
            temp_ready_queue.pop();
            temp_time_stamp.pop();
        }

        else
        {
            temp1.push(p);
            temp2.push(ts);
            p = temp_ready_queue.front();
            ts = temp_time_stamp.front();
            temp_ready_queue.pop();
            temp_time_stamp.pop();
        }
    }
    temp1.push(p);
    temp2.push(ts);

    ready_queue = temp1;
    time_stamp = temp2;
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

    float time_slice;

    cout << "Enter time slice: ";
    cin >> time_slice;

    sort(proc, n);

    RR(proc, n, ready_queue, time_stamp, time_slice);

    cout << endl
         << endl;

    compress_queue(ready_queue, time_stamp);
    PrintGanttChart(ready_queue, time_stamp);

    cout << endl
         << endl;
    return 0;
}
