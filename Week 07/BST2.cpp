#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Tree
{
public:
    Tree()
    {
        int j;
        for (j = 0; j < 2000; j++)
            root[j] = -1;
    }
    int insert(int node)
    {
        int index = 0;
        while (index < 2000 && root[index] != -1)
        {
            if (root[index] < node)
                index = index * 2 + 2;
            else
                index = index * 2 + 1;
        }
        root[index] = node;
    }
    void inorder(int idx)
    {
        if (this->root[idx * 2 + 1] != -1)
            this->inorder(idx * 2 + 1);
        std::cout << this->root[idx] << " ";
        if (this->root[idx * 2 + 2] != -1)
            this->inorder(idx * 2 + 2);
    }
    void preorder(int idx)
    {
        std::cout << this->root[idx] << " ";
        if (this->root[idx * 2 + 1] != -1)
            this->inorder(idx * 2 + 1);
        if (this->root[idx * 2 + 2] != -1)
            this->inorder(idx * 2 + 2);
    }
    void postorder(int idx)
    {
        if (this->root[idx * 2 + 1] != -1)
            this->inorder(idx * 2 + 1);
        if (this->root[idx * 2 + 2] != -1)
            this->inorder(idx * 2 + 2);
        std::cout << this->root[idx] << " ";
    }
    void levelorder()
    {
        for (int i : this->root)
        {
            if (i != -1)
                std::cout << i << " ";
        }
    }

private:
    int root[2000];
};

int main()
{
    Tree *tree = new Tree();
    int j, node;
    srand(time(NULL));
    for (j = 0; j < 10; j++)
    {
        node = rand() % 100;
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
