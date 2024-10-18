#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class SCAN_diskSchedule
{
    unsigned int trackSize;
    int noOfReqs;
    vector<int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;
    bool directionRight; // true for moving towards higher track numbers

public:
    SCAN_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0), directionRight(true) {}

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
        vector<int> allTracks = requests;
        allTracks.push_back(currentPos);

        // Add the disk end points if moving in that direction
        if (directionRight)
        {
            allTracks.push_back(trackSize - 1); // End of disk
        }
        else
        {
            allTracks.push_back(0); // Start of disk
        }

        // Sort all tracks
        sort(allTracks.begin(), allTracks.end());

        // Find the current position in the sorted list
        auto start = find(allTracks.begin(), allTracks.end(), currentPos);
        int startIndex = distance(allTracks.begin(), start);

        cout << "\nMovement sequence: " << currentPos;
        int currentTrack = currentPos;

        if (directionRight)
        {
            // Move right first
            for (int i = startIndex + 1; i < allTracks.size(); i++)
            {
                totalMovement += abs((allTracks[i]) - (currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }

            // Then move left
            for (int i = allTracks.size() - 2; i >= 0; i--)
            {
                if (allTracks[i] < currentPos)
                { // Only process tracks we haven't visited
                    totalMovement += abs((allTracks[i]) - (currentTrack));
                    currentTrack = allTracks[i];
                    cout << " -> " << currentTrack;
                }
            }
        }
        else
        {
            // Move left first
            for (int i = startIndex - 1; i >= 0; i--)
            {
                totalMovement += abs((allTracks[i]) - (currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }

            // Then move right
            for (int i = 1; i < allTracks.size(); i++)
            {
                if (allTracks[i] > currentPos)
                { // Only process tracks we haven't visited
                    totalMovement += abs((allTracks[i]) - (currentTrack));
                    currentTrack = allTracks[i];
                    cout << " -> " << currentTrack;
                }
            }
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main()
{
    SCAN_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}