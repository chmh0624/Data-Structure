/*
    Please finish function enqueue and dequeue

    Function enqueue will insert the data from the top of queue and return 1 on success, return -1 if not.

    Function dequeue will remove one data from the bottom of queue and return a pointer point the data, return NULL if there are on data.

    You can add member to the class if you need.
*/

#include <iostream>
#include <string>

using namespace std;

class Node
{
public:
	int data;
	Node *next;
};

class Queue
{
public:
	Queue()
	{
	}
	int enqueue(int data)
	{
        if (size == 0)
        {
            Node *newNode = new Node;
            newNode -> data = data;
            top = newNode;
            bot = newNode;
            size ++;
            return 1;
        }
        else
        {
            Node *newNode = new Node;
            newNode -> data = data;
            top -> next = newNode;
            top = newNode;
            size ++;
            return 1;
        }
        return -1;
	}
	int *dequeue()
	{
        if (size == 0) return NULL;
        int *returnData = &(bot -> data);
        bot = bot -> next;
        return returnData;
	}
private:
	Node *top, *bot;
    int size = 0;
};

int main()
{
	int data, *temp;
	string command;
	Queue *queue = new Queue();
	while(1)
	{
		cin>>command;
		if(command.compare("exit") == 0)
		{
			break;
		}
		else if(command.compare("enqueue") == 0)
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
		else if(command.compare("dequeue") == 0)
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
