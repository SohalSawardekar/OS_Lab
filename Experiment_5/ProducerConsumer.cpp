#include <iostream>
#include <vector>

using namespace std;

class CircularQueue
{
    vector<string> buffer;
    int IN, OUT;
    int bufferSize;

public:
    CircularQueue(int size) : IN(-1), OUT(-1), bufferSize(size)
    {
        buffer.resize(size);
    }

    void produce(string item)
    {
        if (isFull())
        {
            cout << "\nBuffer is FULL!\n";
            return;
        }

        if (IN == -1)
        {
            IN = 0;
        }

        OUT = (OUT + 1) % bufferSize;
        buffer[OUT] = item;
        cout << "\nProduce added to buffer: " << item << "\n";
        display();
    }

    string consume()
    {
        if (isEmpty())
        {
            cout << "\nBuffer is EMPTY!\n";
            return '\0';
        }

        string item = buffer[IN];

        if (IN == OUT)
        {
            IN = OUT = -1;
        }
        else
        {
            IN = (IN + 1) % bufferSize;
        }

        return item;
    }

    bool isFull() const
    {
        return ((IN == 0 && OUT == bufferSize - 1) || (IN == OUT + 1));
    }

    bool isEmpty() const
    {
        return (IN == -1);
    }

    void display() const
    {
        if (isEmpty())
        {
            cout << "\nBuffer is EMPTY!\n";
            return;
        }

        cout << endl;
        for (int i = 0; i < 30; i++)
            cout << "-";

        cout << endl
             << "\nBuffer contains: ";
        int i = IN;
        if (IN <= OUT)
        {
            while (i <= OUT)
            {
                cout << buffer[i] << " ";
                i++;
            }
        }
        else
        {
            while (i < bufferSize)
            {
                cout << buffer[i] << " ";
                i++;
            }
            i = 0;
            while (i <= OUT)
            {
                cout << buffer[i] << " ";
                i++;
            }
        }
        cout << "\n\n";
        for (int i = 0; i < 30; i++)
            cout << "-";
        cout << endl;
        cout << "IN = " << IN << endl;
        cout << "OUT = " << OUT << endl;
    }
};

int main()
{
    int bufferSize;
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    CircularQueue cq(bufferSize);

    int choice;
    string item;

    while (true)
    {
        cout << "\n****** MENU ******\n";
        cout << "1. Produce\n2. Consume\n3. Display\n4. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter the item to produce: ";
            cin >> item;
            cq.produce(item);
            break;
        case 2:
            item = cq.consume();
            cout << endl;
            for (int i = 0; i < 30; i++)
                cout << "-";
            cout << endl;
            cout << "Consumed Item: " << item << "\n\n";
            for (int i = 0; i < 30; i++)
                cout << "-";
            cout << endl;
            break;
        case 3:
            cq.display();
            break;
        case 4:
            cout << "Exiting program...\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
