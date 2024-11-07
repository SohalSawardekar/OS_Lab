#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class CLOOK_diskSchedule
{
    unsigned int trackSize;
    int noOfReqs;
    vector<unsigned int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;
    bool directionRight; // true for moving towards higher track numbers

public:
    CLOOK_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0), directionRight(true) {}

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

        cout << "Enter direction (1 for right, 0 for left): ";
        cin >> directionRight;
    }

    void evaluate()
    {
        if (noOfReqs == 0)
        {
            cout << "\nTotal head Movement: 0\n";
            return;
        }

        // Create a vector including all positions that need to be visited
        vector<unsigned int> allTracks = requests;
        allTracks.push_back(currentPos);

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
            totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
            currentTrack = allTracks[i];
            cout << " -> " << currentTrack;
        }

        // If we haven't processed all requests, jump to the beginning and continue
        if (startIndex > 0)
        {
            // Add the movement from the last request to the first request
            totalMovement += abs(static_cast<int>(allTracks[0]) - static_cast<int>(currentTrack));
            currentTrack = allTracks[0];
            cout << " -> " << currentTrack;

            // Process remaining requests from the beginning
            for (int i = 0; i < startIndex; i++)
            {
                totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main()
{
    CLOOK_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}