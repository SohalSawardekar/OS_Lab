#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

class processes
{
    int processNo;
    float Arrival_time;
    float Burst_time;
    float WT;
    float TAT;
    float total_time;
    float remaining_time;

public:
    processes()
    {
        processNo = -1;
        Arrival_time = 0;
        Burst_time = 0;
        WT = 0;
        TAT = 0;
        total_time = 0;
        remaining_time = 0;
    }

    float ret_arrival() const { return Arrival_time; }

    float ret_burst() const { return Burst_time; }

    float get_TAT() const { return TAT; }

    void set_remaining_time(float rt) { remaining_time = rt; }

    float get_remaining_time() const { return remaining_time; }

    int get_processNo() const { return processNo; }

    void set_total_time(float t) { total_time = t; }

    void set_TAT(float tat) { TAT = tat; }

    void set_WT(float wt) { WT = wt; }

    void display_process() const
    {
        printf("\t%-10d", processNo);
        printf("%-20.2f", Arrival_time);
        printf("%-20.2f", Burst_time);
        printf("%-10.2f", TAT);
        printf("%-10.2f\n", WT);
    }

    friend void input(processes p[], int n);
    friend void sort(processes p[], int n);
};

queue<processes *> ready_q;
queue<processes *> temp_queue;

void sort(processes p[], int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // sorting according to AT
            if (p[j + 1].ret_arrival() < p[j].ret_arrival())
            {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }

            // If AT is same then sort according to BT
            else if (p[j + 1].ret_arrival() == p[j].ret_arrival())
            {
                if (p[j + 1].ret_burst() < p[j].ret_burst())
                {
                    temp = p[j + 1];
                    p[j + 1] = p[j];
                    p[j] = temp;
                }
            }
        }
    }
}

void sortByPno(processes p[], int n)
{
    processes temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // sorting according to AT
            if (p[j + 1].get_processNo() < p[j].get_processNo())
            {
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }
}

void input(processes p[], int n)
{
    cout << "Enter Burst Time: ";
    for (int i = 0; i < n; i++)
        cin >> p[i].Burst_time;

    cout << "Enter Arrival Time: ";
    for (int i = 0; i < n; i++)
        cin >> p[i].Arrival_time;

    for (int i = 0; i < n; i++)
    {
        p[i].processNo = i + 1;
        p[i].remaining_time = p[i].Burst_time;
    }
}

void round_robin_scheduling(processes p[], int n, float time_slice)
{
    float time = 0;
    unsigned int completed = 0;

    ready_q.push(&p[0]);

    while (completed < n)
    {
        if (!ready_q.empty())
        {
            processes *current_process = ready_q.front();
            ready_q.pop();

            if (current_process->get_remaining_time() <= time_slice)
            {
                time += current_process->get_remaining_time();
                current_process->set_remaining_time(0);
                current_process->set_total_time(time);
                current_process->set_TAT(time - current_process->ret_arrival());
                current_process->set_WT(current_process->get_TAT() - current_process->ret_burst());
                completed++;
            }
            else
            {
                time += time_slice;
                current_process->set_remaining_time(current_process->get_remaining_time() - time_slice);
                ready_q.push(current_process);
            }

            // Add new processes that have arrived during the last time_slice
            for (int j = 0; j < n; j++)
            {
                if (p[j].ret_arrival() <= time && p[j].get_remaining_time() > 0)
                {
                    bool in_queue = false;
                    temp_queue = ready_q;
                    while (!temp_queue.empty())
                    {
                        if (temp_queue.front() == &p[j])
                        {
                            in_queue = true;
                            break;
                        }
                        temp_queue.pop();
                    }
                    if (!in_queue)
                    {
                        ready_q.push(&p[j]);
                    }
                }
            }
        }
        else
        {
            time++;
            // Check if any process can be added to the queue at the current time
            for (int i = 0; i < n; i++)
            {
                if (p[i].ret_arrival() <= time && p[i].get_remaining_time() > 0)
                {
                    ready_q.push(&p[i]);
                }
            }
        }
    }
}

int main()
{
    processes *p;
    int n;
    float time_slice = 0;

    cout << "Enter the number of processes: ";
    cin >> n;

    p = new processes[n];

    input(p, n);
    sort(p, n);

    cout << "Enter time slice: ";
    cin >> time_slice;

    round_robin_scheduling(p, n, time_slice);

    sortByPno(p, n);

    cout << endl;
    printf("\t%-10s", "Process");
    printf("%-20s", "Arrival Time");
    printf("%-20s", "Burst Time");
    printf("%-10s", "TAT");
    printf("%-10s\n", "WT");
    for (int i = 0; i < n; i++)
    {
        p[i].display_process();
    }

    

    delete[] p;
    return 0;
}
