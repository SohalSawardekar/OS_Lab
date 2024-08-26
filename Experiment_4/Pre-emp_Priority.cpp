#include <iostream>
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
    int priority;
} processes;

void input(vector<processes> &p, int n)
{
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
    }

    cout << "Enter burst time: ";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].burstTime;
    }

    cout << "Enter arrival time: ";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].arrivalTime;
    }

    cout << "Enter priority: ";
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].priority;
    }

    for (int i = 0; i < n; i++)
    {
        p[i].remainingTime = p[i].burstTime;
    }
}

void PrintTable(vector<processes> &p, int n)
{
    printf("\t%-10s", "Process");
    printf("%-20s", "Arrival Time");
    printf("%-20s", "Burst Time");
    printf("%-20s", "Priority");
    printf("%-10s", "TAT");
    printf("%-10s\n", "WT");
    for (int i = 0; i < n; i++)
    {
        printf("\t%-10d", p[i].id);
        printf("%-20.2f", p[i].arrivalTime);
        printf("%-20.2f", p[i].burstTime);
        printf("%-20d", p[i].priority);
        printf("%-10.2f", p[i].turnaroundTime);
        printf("%-10.2f\n", p[i].waitingTime);
    }
}

void priorityScheduling(vector<processes> &proc, int n, queue<Process> &ready_queue, queue<double> &time_stamp)
{
    vector<bool> isCompleted(n, false); // To track if a process is completed
    int currentTime = 0;
    int completed = 0;
    float totalTAT = 0, totalWT = 0;

    while (completed != n)
    {
        int index = -1;
        int highestPriority = INT_MAX;

        // Select the process with the highest priority at the current time
        for (int i = 0; i < n; i++)
        {
            if (proc[i].arrivalTime <= currentTime && !isCompleted[i])
            {
                if (proc[i].priority < highestPriority ||
                    (proc[i].priority == highestPriority && proc[i].remainingTime < proc[index].remainingTime))
                {
                    highestPriority = proc[i].priority;
                    index = i;
                }
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
    cout << (int)time_stamp.front();
    temp_time.pop();
    while (!temp_time.empty())
    {
        double time = temp_time.front();
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

    priorityScheduling(proc, n, ready_queue, time_stamp);

    cout << endl
         << endl;

    compress_queue(ready_queue, time_stamp);

    PrintGanttChart(ready_queue, time_stamp);

    cout << endl
         << endl;
    return 0;
}
