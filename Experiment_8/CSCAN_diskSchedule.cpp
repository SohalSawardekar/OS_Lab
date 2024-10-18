#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class CSCAN_diskSchedule
{
    unsigned int trackSize;
    int noOfReqs;
    vector<int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;
    bool directionRight; // true for moving towards higher track numbers

public:
    CSCAN_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0), directionRight(true) {}

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

        // For C-SCAN, we typically move in one direction (right)
        directionRight = true;
    }

    void evaluate()
    {
        if (noOfReqs == 0)
        {
            cout << "\nTotal head Movement: 0\n";
            return;
        }

        // Create a vector including all positions that need to be visited
        vector<int> allTracks = requests;
        allTracks.push_back(currentPos);

        // Add disk endpoints
        allTracks.push_back(0);
        allTracks.push_back(trackSize - 1);

        // Sort all tracks
        sort(allTracks.begin(), allTracks.end());

        // Find the current position in the sorted list
        auto start = find(allTracks.begin(), allTracks.end(), currentPos);
        int startIndex = distance(allTracks.begin(), start);

        cout << "\nMovement sequence: " << currentPos;
        int currentTrack = currentPos;

        // Move towards higher track numbers
        for (int i = startIndex + 1; i < allTracks.size(); i++)
        {
            totalMovement += abs((allTracks[i]) - (currentTrack));
            currentTrack = allTracks[i];
            cout << " -> " << currentTrack;
        }

        // If we haven't processed all requests, jump to beginning and continue
        if (startIndex > 0)
        {
            // Add the movement from end to beginning
            cout << " -> 0"; // Show the jump to the beginning
            currentTrack = 0;

            // Process remaining requests from beginning
            for (int i = 0; i < startIndex; i++)
            {
                totalMovement += abs((allTracks[i]) - (currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main()
{
    CSCAN_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}