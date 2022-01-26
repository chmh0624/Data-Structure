/*
    Please finish function enqueue and dequeue

    Function enqueue will insert the data from the top of queue and return 1 on success, return -1 if not.

    Function dequeue will remove one data from the bottom of queue and return a pointer point the data, return NULL if there are on data.

    You can add member to the class if you need.
    
    You can get 80 point if you finish this two function.

    You can get 100 point if you queue is circularity.
*/

#include <iostream>
#include <cstring>

#define SIZE 100

using namespace std;

class Queue
{
public:
    Queue()
    {
        size = 0;
        front = 0;
    }
    int enqueue(int d)
    {
        if (size < 0) return -1;
        size %= SIZE;
        data[(front + size)%SIZE] = d;
        size ++;
        return 1;
    }
    int *dequeue()
    {
        if (size < 0) return NULL;
        int *returnPtr = &data[front%SIZE];
        front ++;
        return returnPtr;
    }
private:
      int data[SIZE];
      int size, front;
};

int main()
{
    int data, *temp;
    char command[50];
    Queue *queue = new Queue();
    while(1)
    {
        cin>>command;
        if(strcmp(command, "exit") == 0)
        {
            break;
        }
        else if(strcmp(command, "enqueue") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(queue->enqueue(data) == 1)
            {
                cout<<"Successfully enqueue data "<<data<<" into queue."<<endl;
            }
            else
            {
                cout<<"Failed to enqueue data into queue."<<endl;
            }
        }
        else if(strcmp(command, "dequeue") == 0) 
        {
            temp = queue->dequeue();
            if(temp == NULL)
            {
                cout<<"Failed to dequeue a data from queue.\n";
            }
            else
            {
                cout<<"Dequeue data "<<*temp<<" from queue."<<endl;
            }
        }
    }
}


