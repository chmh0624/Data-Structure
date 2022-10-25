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
        if (this->root != NULL)
            std::cout << this->root->data;
        if (this->root->left)
            queue.push(this->root->left);
        if (this->root->right)
            queue.push(this->root->right);
        TreeNode<T> *cur;
        while (queue.qsize)
        {
            int size = queue.qsize;
            for (int i = 0; i < size; i++)
            {
                cur = queue.pop();
                std::cout << "," << cur->data;
                if (cur->left)
                    queue.push(cur->left);
                if (cur->right)
                    queue.push(cur->right);
            }
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
