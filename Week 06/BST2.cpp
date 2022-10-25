#include <iostream>
#include <sstream>
#include <limits.h>
#include <string>

template <class T>
class TreeNode
{
public:
    TreeNode()
    {
        this->left = NULL;
        this->right = NULL;
    }
    TreeNode(T data)
    {
        this->data = data;
        this->right = NULL;
        this->left = NULL;
    }

    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
};

template <class T>
class Queue
{
public:
    T *data;
    int front, tail, mxsize, qsize;
    Queue()
    {
        this->data = new T[500];
        this->front = 0;
        this->tail = 0;
        this->mxsize = 500;
        this->qsize = 0;
    }
    void push(T data)
    {
        this->data[this->tail] = data;
        this->tail = this->tail + 1;
        this->qsize++;
    }
    T pop()
    {
        this->front++;
        this->qsize--;
        return this->data[this->front - 1];
    }
};

/**
 * A binarySearchTree abstract class for BinarySearchTree class
 */
template <class T>
class binarySearchTree
{
public:
    binarySearchTree()
    {
        this->root = NULL;
    }
    virtual void preorder() = 0;

    virtual void inorder() = 0;

    virtual void postorder() = 0;

    virtual void levelorder() = 0;

    virtual bool insert(T data) = 0;

    virtual void setRoot(T data) = 0;

    virtual bool serach(T target) = 0;

protected:
    TreeNode<T> *root;
};

template <class T>
class BinarySearchTree : public binarySearchTree<T>
{
public:
    BinarySearchTree()
    {
        this->root = NULL;
    }
    void preorder()
    {
        bool comma = false;
        preorder_hp(this->root, &comma);
        std::cout << std::endl;
    }
    void preorder_hp(TreeNode<T> *rroot, bool *comma)
    {
        if (rroot == NULL)
            return;
        if (*comma == true)
            std::cout << ",";
        else
            *comma = true;
        std::cout << rroot->data;
        preorder_hp(rroot->left, comma);
        preorder_hp(rroot->right, comma);
    }

    void inorder()
    {
        bool comma = false;
        inorder_hp(this->root, &comma);
        std::cout << std::endl;
    }
    void inorder_hp(TreeNode<T> *rroot, bool *comma)
    {
        if (rroot == NULL)
            return;
        inorder_hp(rroot->left, comma);
        if (*comma == true)
            std::cout << ",";
        else
            *comma = true;
        std::cout << rroot->data;
        inorder_hp(rroot->right, comma);
    }

    void postorder()
    {
        bool comma = false;
        postorder_hp(this->root, &comma);
        std::cout << std::endl;
    }
    void postorder_hp(TreeNode<T> *rroot, bool *comma)
    {
        if (rroot == NULL)
            return;
        postorder_hp(rroot->left, comma);
        postorder_hp(rroot->right, comma);
        if (*comma == true)
            std::cout << ",";
        else
            *comma = true;
        std::cout << rroot->data;
    }

    void levelorder()
    {
        Queue<TreeNode<T> *> queue;
        if (this->root == NULL)
            return;
        int print[500];
        int idx = 0;
        if (this->root != NULL)
            std::cout << this->root->data;
        queue.push(this->root->left);
        queue.push(this->root->right);
        TreeNode<T> *cur;
        int isNULL = this->root->right != NULL || this->root->left != NULL;
        while (queue.qsize && isNULL)
        {
            for (int i = 0; i < idx; i++)
            {
                std::cout << ",";
                if (print[i] != INT_MIN)
                    std::cout << print[i];
                else
                    std::cout << "NULL";
            }
            isNULL = 0;
            idx = 0;
            int size = queue.qsize;
            for (int i = 0; i < size; i++)
            {
                cur = queue.pop();
                if (cur)
                {
                    print[idx++] = cur->data;
                    queue.push(cur->left);
                    queue.push(cur->right);
                    isNULL += (cur->left != NULL || cur->right != NULL);
                }
                else
                {
                    print[idx++] = INT_MIN;
                }
            }
        }
        for (int i = idx - 1; i >= 0; i--)
        {
            if (print[i] == INT_MIN)
            {
                idx--;
            }
            else
            {
                break;
            }
        }
        for (int i = 0; i < idx; i++)
        {
            std::cout << ",";
            if (print[i] != INT_MIN)
                std::cout << print[i];
            else
                std::cout << "NULL";
        }
        std::cout << std::endl;
    }

    bool insert(T data)
    {
        if (this->root == NULL)
        {
            this->root = new TreeNode<T>(data);
            return true;
        }
        TreeNode<T> *cur = this->root;
        while (true)
        {
            if (cur->data == data)
                return false;
            if (cur->data > data)
            {
                if (cur->left == NULL)
                {
                    cur->left = new TreeNode<T>(data);
                    return true;
                }
                else
                    cur = cur->left;
            }
            else
            {
                if (cur->right == NULL)
                {
                    cur->right = new TreeNode<T>(data);
                    return true;
                }
                else
                    cur = cur->right;
            }
        }
    }

    void setRoot(T data)
    {
        if (this->root == NULL)
        {
            this->root = new TreeNode<T>(data);
        }
        else
        {
            this->root->data = data;
        }
    }

    bool serach(T target)
    {
        TreeNode<T> *cur = this->root;
        while (cur)
        {
            if (target == cur->data)
                return true;
            if (target > cur->data)
                cur = cur->right;
            else
                cur = cur->left;
        }
        return false;
    }
};

int main()
{
    std::string input;
    while (std::getline(std::cin, input))
    {
        BinarySearchTree<int> *bst = new BinarySearchTree<int>;

        for (int i = 0; i < input.length(); i++)
            if (input[i] == ',')
                input[i] = ' ';
        std::stringstream ss(input);
        std::string element;
        while (ss >> element)
        {
            if (element != "NULL")
            {
                int data = stoi(element);
                bst->insert(data);
            }
        }
        bst->levelorder();
        input = "";
    }
}
