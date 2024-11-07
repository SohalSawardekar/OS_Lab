#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class LOOK_diskSchedule {
    unsigned int trackSize;
    int noOfReqs;
    vector<unsigned int> requests;
    unsigned int currentPos;
    unsigned int totalMovement;
    bool directionRight; 

public:
    LOOK_diskSchedule() : trackSize(0), noOfReqs(0), currentPos(0), totalMovement(0), directionRight(true) {}

    void input() {
        cout << "Enter the track size: ";
        cin >> trackSize;

        cout << "Enter the no of requests: ";
        cin >> noOfReqs;

        requests.resize(noOfReqs);
        cout << "Enter the requests: ";
        for (int i = 0; i < noOfReqs; i++) {
            cin >> requests[i];
            if (requests[i] >= trackSize) {
                cout << "Error: Request position cannot exceed track size\n";
                exit(1);
            }
        }

        cout << "Enter the current position of R/W head: ";
        cin >> currentPos;
        if (currentPos >= trackSize) {
            cout << "Error: Initial position cannot exceed track size\n";
            exit(1);
        }

        cout << "Enter direction (1 for right, 0 for left): ";
        cin >> directionRight;
    }

    void evaluate() {
        if (noOfReqs == 0) {
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

        if (directionRight) {
            // Move right first
            for (int i = startIndex + 1; i < allTracks.size(); i++) {
                totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
            
            // Then move left
            for (int i = startIndex - 1; i >= 0; i--) {
                totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
        } else {
            // Move left first
            for (int i = startIndex - 1; i >= 0; i--) {
                totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
            
            // Then move right
            for (int i = startIndex + 1; i < allTracks.size(); i++) {
                totalMovement += abs(static_cast<int>(allTracks[i]) - static_cast<int>(currentTrack));
                currentTrack = allTracks[i];
                cout << " -> " << currentTrack;
            }
        }

        cout << "\nTotal head Movement: " << totalMovement << endl;
    }
};

int main() {
    LOOK_diskSchedule obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}

