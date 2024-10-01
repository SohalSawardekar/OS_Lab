#include <iostream>
#include <vector>

using namespace std;

class CircularQueue
{
    vector<char> buffer; // Dynamic buffer using a vector
    int IN, OUT;
    int bufferSize;

public:
    // Constructor to initialize the circular queue
    CircularQueue(int size) : IN(-1), OUT(-1), bufferSize(size)
    {
        buffer.resize(size);
    }

    // Produce item (insert into the buffer)
    void produce(char item)
    {
        if (isFull())
        {
            cout << "\nBuffer is FULL!\n";
            return;
        }

        if (IN == -1)
        { // If initially empty
            IN = 0;
        }

        OUT = (OUT + 1) % bufferSize; // Circular increment
        buffer[OUT] = item;
        cout << "\nProduce added to buffer: " << item << "\n";
        display();
    }

    // Consume item (remove from the buffer)
    char consume()
    {
        if (isEmpty())
        {
            cout << "\nBuffer is EMPTY!\n";
            return '\0'; // Return null character if empty
        }

        char item = buffer[IN];

        // If only one element left
        if (IN == OUT)
        {
            IN = OUT = -1; // Reset queue
        }
        else
        {
            IN = (IN + 1) % bufferSize; // Circular increment
        }

        return item;
    }

    // Check if the buffer is full
    bool isFull() const
    {
        return ((IN == 0 && OUT == bufferSize - 1) || (IN == OUT + 1));
    }

    // Check if the buffer is empty
    bool isEmpty() const
    {
        return (IN == -1);
    }

    // Display the buffer contents
    void display() const
    {
        if (isEmpty())
        {
            cout << "\nBuffer is EMPTY!\n";
            return;
        }

        cout << "\nBuffer contains: ";
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
        cout << "\n";
    }
};

int main()
{
    int bufferSize;
    cout << "Enter the buffer size: ";
    cin >> bufferSize;

    // Create a CircularQueue object with user-defined buffer size
    CircularQueue cq(bufferSize);

    int choice;
    char item;

    while (true)
    {
        cout << "\n****** MENU ******\n";
        cout << "1. Produce\n2. Consume\n3. Display\n4. Quit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Produce item
            cout << "Enter the item to produce: ";
            cin >> item;
            cq.produce(item);
            break;
        case 2: // Consume item
            item = cq.consume();
            if (item != '\0')
            {
                cout << "Consumed Item: " << item << "\n";
            }
            break;
        case 3: // Display buffer
            cq.display();
            break;
        case 4: // Quit program
            cout << "Exiting program...\n";
            exit(0);
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
