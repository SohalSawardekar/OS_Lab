#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class FIFO_PageReplacement
{
    int noOfFrames;
    queue<char> pages;
    vector<char> frameState;
    int pageFaults;
    string sequence;

public:
    FIFO_PageReplacement()
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

    void evaluate()
    {
        format();
        cout << "\nInitial state: ";
        printCurrentState();
        format();

        for (char page : sequence)
        {
            cout << "\nReferencing page: " << page << endl;

            if (!isPagePresent(page))
            {
                pageFaults++;

                if (pages.size() < noOfFrames)
                {
                    // Still have empty frames
                    pages.push(page);
                    frameState[pages.size() - 1] = page;
                }
                else
                {
                    // Need to replace oldest page
                    char oldestPage = pages.front();
                    pages.pop();
                    pages.push(page);

                    // Update frameState
                    for (int i = 0; i < frameState.size(); i++)
                    {
                        if (frameState[i] == oldestPage)
                        {
                            frameState[i] = page;
                            break;
                        }
                    }
                }
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
    FIFO_PageReplacement obj;

    cout << endl;
    obj.input();
    cout << endl;
    obj.evaluate();
    cout << endl;

    return 0;
}