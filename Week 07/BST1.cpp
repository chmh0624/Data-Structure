#include <iostream>
#include <cstdlib>
#include <queue>
#include <ctime>

using namespace std;

class Tree
{
public:
    Tree()
    {
        root = 0;
        int j, k;
        for (j = 0; j < 20; j++)
            for (k = 0; k < 4; k++)
                node[j][k] = -1;
    }
    int insert(int n)
    {
        int f = root, index = 0;
        while (node[index][0] != -1)
            index++;
        if (index >= 20) // overflow
            return -1;
        if (node[root][0] == -1) // empty tree
        {
            node[root][0] = 1;
            node[root][1] = n;
            return 1;
        }
        else
        {
            node[index][0] = 1;
            node[index][1] = n;
            while (1)
            {
                if (node[f][1] < n)
                {
                    if (node[f][3] == -1)
                    {
                        node[f][3] = index;
                        return 1;
                    }
                    else
                    {
                        f = node[f][3];
                    }
                }
                else
                {
                    if (node[f][2] == -1)
                    {
                        node[f][2] = index;
                        return 1;
                    }
                    else
                    {
                        f = node[f][2];
                    }
                }
            }
        }
    }
    void inorder(int idx)
    {
        if (this->node[idx][0] == -1)
            return;
        if (this->node[idx][2] != -1)
            this->inorder(node[idx][2]);
        std::cout << node[idx][1] << " ";
        if (this->node[idx][3] != -1)
            this->inorder(node[idx][3]);
    }
    void preorder(int idx)
    {
        if (this->node[idx][0] == -1)
            return;
        std::cout << node[idx][1] << " ";
        if (this->node[idx][2] != -1)
            this->inorder(node[idx][2]);
        if (this->node[idx][3] != -1)
            this->inorder(node[idx][3]);
    }
    void postorder(int idx)
    {
        if (this->node[idx][0] == -1)
            return;
        if (this->node[idx][2] != -1)
            this->inorder(node[idx][2]);
        if (this->node[idx][3] != -1)
            this->inorder(node[idx][3]);
        std::cout << node[idx][1] << " ";
    }
    void levelorder()
    {
        std::queue<int> temp;
        temp.push(0);
        while (temp.size())
        {
            int sz = temp.size();
            for (int i = 0; i < sz; i++)
            {
                std::cout << temp.front() << " ";
                if (this->node[temp.front()][2] != -1)
                    temp.push(this->node[temp.front()][2]);
                temp.pop();
                if (this->node[temp.front()][3] != -1)
                    temp.push(this->node[temp.front()][3]);
                temp.pop();
            }
        }
    }

private:
    int node[20][4];
    int root;
};

int main()
{
    Tree *tree = new Tree();
    int j, node;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
    {
        node = rand() % 10;
        tree->insert(node);
    }

    tree->inorder(0);
    printf("\n");
    tree->preorder(0);
    printf("\n");
    tree->postorder(0);
    printf("\n");
    tree->levelorder();
    printf("\n");
}

