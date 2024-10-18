#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class LRU_PageReplacement
{
    int noOfFrames;
    vector<char> frameState;
    vector<int> lastUsed;
    int pageFaults;
    string sequence;

public:
    LRU_PageReplacement()
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
        lastUsed.resize(noOfFrames, -1);
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

    void updateLastUsed(char page, int currentTime)
    {
        for (int i = 0; i < frameState.size(); i++)
        {
            if (frameState[i] == page)
            {
                lastUsed[i] = currentTime;
                break;
            }
        }
    }

    int findLRUPage()
    {
        int lruIndex = 0;
        int minTime = lastUsed[0];

        for (int i = 0; i < frameState.size(); i++)
        {
            if (frameState[i] == '-')
            {
                return i;
            }
        }

        for (int i = 1; i < lastUsed.size(); i++)
        {
            if (lastUsed[i] < minTime)
            {
                minTime = lastUsed[i];
                lruIndex = i;
            }
        }
        return lruIndex;
    }

    void evaluate()
    {
        format();
        cout << "\nInitial state: ";
        printCurrentState();
        format();

        for (int currentTime = 0; currentTime < sequence.length(); currentTime++)
        {
            char page = sequence[currentTime];
            cout << "\nReferencing page: " << page << endl;

            if (!isPagePresent(page))
            {
                pageFaults++;

                int replaceIndex = findLRUPage();
                frameState[replaceIndex] = page;
                lastUsed[replaceIndex] = currentTime;

                cout << "Page Fault occurred!" << endl;
            }
            else
            {
                updateLastUsed(page, currentTime);
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
    LRU_PageReplacement obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}