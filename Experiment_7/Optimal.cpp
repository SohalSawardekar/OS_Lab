#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class OPTIMAL_PageReplacement
{
    int noOfFrames;
    vector<char> frameState;
    int pageFaults;
    string sequence;

public:
    OPTIMAL_PageReplacement()
    {
        noOfFrames = 0;
        pageFaults = 0;
    }

    void input()
    {
        cout << "Enter no of frames: ";
        cin >> noOfFrames;

        cout << "Enter the sequence: ";
        cin >> sequence;

        frameState.resize(noOfFrames, '-');
    }

    void format()
    {
        cout << endl;
        for (int i = 0; i < 30; i++)
            cout << "-";
        cout << endl;
    }

    bool isPagePresent(char page)
    {
        for (char c : frameState)
        {
            if (c == page)
                return true;
        }
        return false;
    }

    void printCurrentState()
    {
        for (char c : frameState)
        {
            cout << c << " ";
        }
        cout << endl;
    }

    int findNextOccurrence(char page, int currentPos)
    {
        for (int i = currentPos + 1; i < sequence.length(); i++)
        {
            if (sequence[i] == page)
                return i;
        }
        return INT_MAX;
    }

    int findPageToReplace(int currentPos)
    {
        int farthest = -1;
        int replaceIndex = 0;

        for (int i = 0; i < frameState.size(); i++)
        {
            if (frameState[i] == '-')
                return i;

            int nextPos = findNextOccurrence(frameState[i], currentPos);
            if (nextPos > farthest)
            {
                farthest = nextPos;
                replaceIndex = i;
            }
        }
        return replaceIndex;
    }

    void evaluate()
    {
        format();
        cout << "\nInitial state: ";
        printCurrentState();
        format();

        for (int i = 0; i < sequence.length(); i++)
        {
            char page = sequence[i];
            cout << "\nReferencing page: " << page << endl;

            if (!isPagePresent(page))
            {
                pageFaults++;

                int replaceIndex = findPageToReplace(i);
                frameState[replaceIndex] = page;

                cout << "Page Fault occurred!" << endl;
            }
            else
            {
                cout << "Page already present" << endl;
            }

            cout << "Current frame state: ";
            printCurrentState();
            format();
        }

        cout << "\nTotal Page Faults: " << pageFaults << endl;
    }
};

int main()
{
    OPTIMAL_PageReplacement obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}