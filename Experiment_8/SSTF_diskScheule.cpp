#include <iostream>
#include <vector>
#include <cmath>
#include <limits.h>

using namespace std;

class SSTF_diskSchedule
{
    unsigned int trackSize;
    int noOfReqs;
    vector<unsigned int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;

public:
    SSTF_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0) {}

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

    int findClosest(vector<unsigned int> &reqs, vector<bool> &served, int current)
    {
        int minDist = INT_MAX;
        int closestIndex = -1;

        for (int i = 0; i < reqs.size(); i++)
        {
            if (!served[i])
            {
                int distance = abs(static_cast<int>(current) - static_cast<int>(reqs[i]));
                if (distance < minDist)
                {
                    minDist = distance;
                    closestIndex = i;
                }
            }
        }
        return closestIndex;
    }

    void evaluate()
    {
        if (noOfReqs == 0)
        {
            cout << "\nTotal head Movement: 0\n";
            return;
        }

        vector<bool> served(noOfReqs, false);
        int currentTrack = currentPos;
        int remainingReqs = noOfReqs;

        cout << "\nMovement sequence: " << currentTrack;

        while (remainingReqs > 0)
        {
            int nextIndex = findClosest(requests, served, currentTrack);
            if (nextIndex == -1)
                break;

            int nextTrack = requests[nextIndex];
            totalMovement += abs(currentTrack - nextTrack);
            currentTrack = nextTrack;

            served[nextIndex] = true;
            remainingReqs--;

            cout << " -> " << currentTrack;
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main()
{
    SSTF_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}