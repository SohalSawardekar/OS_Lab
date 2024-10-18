#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

class FCFS_diskSchedule
{
    unsigned int trackSize;
    int noOfReqs;
    queue<unsigned int> requestQueue;
    vector<unsigned int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;

public:
    FCFS_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0) {}

    void input()
    {
        cout << "Enter the track size: ";
        cin >> trackSize;

        cout << "Enter the no of requests: ";
        cin >> noOfReqs;

        requests.resize(noOfReqs);
        cout << "Enter the requests: ";
        for (int i = 0; i < noOfReqs; i++)
        {
            cin >> requests[i];
            if (requests[i] >= trackSize)
            {
                cout << "Error: Request position cannot exceed track size\n";
                exit(1);
            }
        }

        cout << "Enter the current position of R/W head: ";
        cin >> currentPos;
        if (currentPos >= trackSize)
        {
            cout << "Error: Initial position cannot exceed track size\n";
            exit(1);
        }
    }

    void evaluate()
    {
        if (noOfReqs == 0)
        {
            cout << "\nTotal head Movement: 0\n";
            return;
        }

        requestQueue.push(currentPos);
        for (unsigned int req : requests)
        {
            requestQueue.push(req);
        }

        int currentTrack = requestQueue.front();
        requestQueue.pop();

        cout << "\nMovement sequence: " << currentTrack;
        while (!requestQueue.empty())
        {
            int nextTrack = requestQueue.front();
            requestQueue.pop();
            totalMovement += abs(currentTrack - nextTrack);
            currentTrack = nextTrack;
            cout << " -> " << currentTrack;
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main()
{
    FCFS_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}