#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class BankersAlgorithm
{
    int n, m;
    vector<vector<int>> max, allocation, need;
    vector<int> available;
    int temp_avail = 0;
    string errorMessage = "";

    bool isSafe(vector<int> &work, vector<bool> &finish)
    {
        vector<int> safeSeq;

        cout << "Available Matrix: " << endl;
        for (int i = 0; i < m; i++)
            cout << work[i] << "   ";
        cout << "\t--" << endl;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool canAllocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        errorMessage = "resources required are greater than need";
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                        cout << work[j] << "   ";
                    }
                    cout << "\tP" << i << endl;
                    finish[i] = true;
                    safeSeq.push_back(i);
                    i = -1;
                }
            }
        }
        if (safeSeq.size() == n)
        {
            cout << "\nSafe sequence: ";
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
            {
                cin >> allocation[i][j];
                if (allocation[i][j] > max[i][j])
                {
                    cout << "\t\t...Allocated Resources Greater than Max Resources..." << endl;
                    exit(1);
                }
            }

        cout << "Enter the available resources:" << endl;
        for (int j = 0; j < m; j++)
        {
            cin >> available[j];
            temp_avail += available[j];
        }

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
        {
            cout << "The system is not in a safe state." << endl;
            cout << endl;
            cout << "Error: "
                 << errorMessage << endl;
        }
    }

    void requestResources()
    {
        int pid, tmp = 0;
        vector<int> request(m);
        errorMessage = "";
        int current_avail = 0;
        cout << "Enter the process No for the request(starts from 0): ";
        cin >> pid;

        for (int i = 0; i < m; i++)
            if (need[pid][i] == 0)
                tmp++;

        if (tmp == m)
        {
            cout << "Process " << pid << " has no resource requests." << endl;
            return;
        }

        cout << "Enter the resource request for process " << pid << ": ";
        for (int j = 0; j < m; j++)
        {
            cin >> request[j];
            current_avail += request[j];
        }
        bool valid = true;
        for (int j = 0; j < m; j++)
        {
            if (request[j] > need[pid][j])
            {
                errorMessage = "Requested resources is greater than Need resources";
                valid = false;
                break;
            }
            else if (request[j] > available[j])
            {
                errorMessage = "Request resources is greater than available resources";
                valid = false;
                break;
            }
            else if (current_avail > 0.8 * temp_avail)
            {
                errorMessage = "Request resources is greater than available resources";
                valid = false;
                break;
            }
        }
        if (!valid)
        {
            cout << endl;
            cout << "Error: " << errorMessage << endl
                 << endl;
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
        cout << "2. Check Safe Sequence" << endl;
        cout << "3. Request resources" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << endl;
            banker.displayState();
            break;
        case 2:
            cout << endl;
            banker.checkSafeState();
            break;
        case 3:
            cout << endl;
            banker.requestResources();
            break;
        case 4:
            cout << endl;
            cout << "Exiting program." << endl;
            return 0;
        default:
            cout << endl;
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}