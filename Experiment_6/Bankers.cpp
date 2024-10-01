#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class BankersAlgorithm
{
    int n, m;
    vector<vector<int>> max, allocation, need;
    vector<int> available;

    bool isSafe(vector<int> &work, vector<bool> &finish)
    {
        vector<int> safeSeq;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    safeSeq.push_back(i);
                    i = -1;
                }
            }
        }
        if (safeSeq.size() == n)
        {
            cout << "Safe sequence: ";
            for (int i : safeSeq)
                cout << "P" << i << " ";
            cout << endl;
            return true;
        }
        return false;
    }

public:
    void initializeSystem()
    {
        cout << "Enter the number of processes: ";
        cin >> n;
        cout << "Enter the number of resources: ";
        cin >> m;

        max.resize(n, vector<int>(m));
        allocation.resize(n, vector<int>(m));
        need.resize(n, vector<int>(m));
        available.resize(m);

        cout << "Enter the maximum resource matrix:" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> max[i][j];

        cout << "Enter the allocation matrix:" << endl;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                cin >> allocation[i][j];

        cout << "Enter the available resources:" << endl;
        for (int j = 0; j < m; j++)
            cin >> available[j];

        // Calculate need matrix
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                need[i][j] = max[i][j] - allocation[i][j];

        cout << endl;
        displayState();
        cout << endl;
        checkSafeState();
        cout << endl;
    }

    void displayState()
    {
        cout << "\nCurrent System State:" << endl;
        cout << "Process\t\tAllocation\tMax\tNeed\n";
        for (int i = 0; i < n; i++)
        {
            cout << "P" << i << "\t\t";
            for (int j = 0; j < m; j++)
                cout << allocation[i][j] << " ";
            cout << "\t\t";
            for (int j = 0; j < m; j++)
                cout << max[i][j] << " ";
            cout << "\t";
            for (int j = 0; j < m; j++)
                cout << need[i][j] << " ";
            cout << endl;
        }
        cout << "\nAvailable: ";
        for (int j = 0; j < m; j++)
            cout << available[j] << " ";
        cout << endl;
    }

    void checkSafeState()
    {
        vector<int> work = available;
        vector<bool> finish(n, false);
        if (isSafe(work, finish))
            cout << "The system is in a safe state." << endl;
        else
            cout << "The system is not in a safe state." << endl;
    }

    void requestResources()
    {
        int pid;
        vector<int> request(m);

        cout << "Enter the process No for the request(starts from 0): ";
        cin >> pid;
        cout << "Enter the resource request for process " << pid << ": ";
        for (int j = 0; j < m; j++)
            cin >> request[j];
        bool valid = true;
        for (int j = 0; j < m; j++)
        {
            if (request[j] > need[pid][j] || request[j] > available[j])
            {
                valid = false;
                break;
            }
        }
        if (!valid)
        {
            cout << "Invalid request. Process must wait." << endl;
            return;
        }
        for (int j = 0; j < m; j++)
        {
            available[j] -= request[j];
            allocation[pid][j] += request[j];
            need[pid][j] -= request[j];
        }

        cout << endl;
        displayState();
        cout << endl;

        vector<int> work = available;
        vector<bool> finish(n, false);
        if (isSafe(work, finish))
        {
            cout << "Resources allocated safely." << endl;
        }
        else
        {
            cout << "Resource allocation would lead to an unsafe state. Rolling back." << endl;
            for (int j = 0; j < m; j++)
            {
                available[j] += request[j];
                allocation[pid][j] -= request[j];
                need[pid][j] += request[j];
            }
        }
    }
};

int main()
{
    BankersAlgorithm banker;
    banker.initializeSystem();
    while (true)
    {
        cout << "\nBanker's Algorithm Menu:" << endl;
        cout << "1. Display current state" << endl;
        cout << "2. Check system safety" << endl;
        cout << "3. Request resources" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            banker.displayState();
            break;
        case 2:
            banker.checkSafeState();
            break;
        case 3:
            banker.requestResources();
            break;
        case 4:
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}