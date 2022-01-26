/*
    Please finish two function push and pop

    Function push will push the data into stack and return 1 if success, return -1 if not.

    Function pop will pop the top data from stack and return a pointer point to the data, return NULL if there is no data.

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

class Stack
{
public:
    Stack()
    {
    }
    int push(int d)
    {
        Node *newNode = new Node;
        newNode -> data = d;
        if (size == 0)
        {
            head = newNode;
            size ++;
            return 1;
        }
        else
        {
            Node *cur = head;
            for (int i=0; i<size; cur = cur -> next, i++);
            cur -> next = newNode;
            return 1;
        }
        return -1;
    }

    int *pop()
    {
        if (size == 0) return NULL;
        Node *cur = head;
        int *tailData;
        for (int i=0; i<size - 1; cur = cur -> next, i++);
        tailData = &(cur -> next -> data);
        cur -> next = NULL;
        size --;
        return tailData;
    }
private:
    Node *head;
    int size = 0;
};

int main()
{
    int data, *temp;
    string command;
    Stack *stack = new Stack();
    while(1)
    {
        cin>>command;
        if(command.compare("exit") == 0)
        {
            break;
        }
        else if(command.compare("push") == 0)
        {
            cout<<"Please input a integer data:";
            cin>>data;
            if(stack->push(data) == 1)
            {
                cout<<"Successfully push data "<<data<<" into stack.\n";
            }
            else
            {
                cout<<"Failed to push data into stack.\n";
            }
        }
        else if(command.compare("pop") == 0)
        {
            temp = stack->pop();
            if(temp == NULL)
            {
                cout<<"Failed to pop a data from stack.\n";
            }
            else
            {
                cout<<"Pop data "<<*temp<<" from stack.\n";
            }
        }
    }
}
