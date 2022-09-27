struct Node
{
    int data;
    struct Node *prev, *next;
};
/*
    function initLinkList will initialize the head of a linked list.
    parameter head represent the head of a linked list.
*/
void initLinkList(struct Node **head)
{
    *head = NULL;
}
/*
    function addToHead will insert a node which hold data into linked list from head of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToHead(struct Node **head, int data)
{
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode -> data = data;
    newNode -> next = *head;
    newNode -> prev = NULL;
    if ((*head) != NULL)
        (*head) -> prev = newNode;
    *head = newNode;
}
/*
    function addToHead will insert a node which hold data into linked list from tail of the linked list.
    parameter head represent the head of a linked list.
    parameter data represent the data to insert.
*/
void addToTail(struct Node **head, int data)
{
    if ((*head) == NULL) {
        *head = (struct Node *) malloc(sizeof(struct Node));
        (*head) -> data = data;
        (*head) -> next = NULL;
        (*head) -> prev = NULL;
    }
    else {
        struct Node *cur = *head;
        while (cur -> next) cur = cur -> next;
        cur -> next = (struct Node *) malloc(sizeof(struct Node));
        cur -> next -> data = data;
        cur -> next -> prev = cur;
      	cur -> next -> next = NULL;
    }
}
/*
    function deleteData will search from head to find the first node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
*/
void deleteData(struct Node **head, int data)
{
    if ((*head) == NULL) return ;
    if ((*head) -> next == NULL) {
        if ((*head) -> data == data) {
            free(*head);
            *head = NULL;
        }
        return ;
    }
    struct Node *cur = *head;
    while (cur) {
        if (cur -> data == data) {
            if (cur == *head) {
                struct Node *temp = *head;
                (*head) = (*head) -> next;
                (*head) -> prev = NULL;
                free(temp);
                return ;
            }
            else if (cur -> next == NULL) {
                struct Node *temp = cur;
                cur -> prev -> next = NULL;
                free(temp);
                return ;
            }
            else {
                cur -> prev -> next = cur -> next;
                cur -> next -> prev = cur -> prev;
                free(cur);
                return ;
            }
        } 
        else {
            cur = cur -> next;
        }
    }
}
/*
    function deleteData will search from head to find the first n node which hold the data and remove it.
    parameter head represent the head of a linked list.
    parameter data represent the data to be search.
    parameter n represent the max number of node to be removed.
*/
void deleteDatas(struct Node **head, int data, int n)
{
    if (n == 0) return ;
    deleteData(head, data);
    deleteDatas(head, data, n-1);
}
/*
    function display will print out all the data in the linked list from the head
    there is a \n in the end of each print
    output example:
    if your linked list data is 5, 4, 3, 2, 1
    then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
    parameter head represent the head of a linked list.
*/
void display(struct Node *head)
{
    if (head == NULL) {
        printf("()\n");
    }
    else {
        printf("(%d", head -> data);
        struct Node *temp = head -> next;
        while (temp) {
            printf(", %d", temp -> data);
            temp = temp -> next;
        }
        printf(")\n");
    }

}

void enqueue(struct Node **queue, int data)
{
    addToTail(queue, data);
}
/*
    function dequeue will remove a data from queue
    parameter queue represent the queue
    this function should return the data that be removed
*/
int dequeue(struct Node **queue)
{
    if (*queue) {
        int f = front(*queue);
        deleteData(queue, front(*queue));
        return f;
    }
    return 0;
}
/*
    function front will give the next remove data in the given queue
    parameter queue represent the queue
    this function should return the next remove data
*/
int front(struct Node *queue)
{
    if (queue)
        return queue -> data;
}
/*
    function isEmpty will determine if the given queue is empty or not
    parameter queue represent the queue
    this function should return 1 if the given queue is empty, 0 if not
*/
int isEmpty(struct Node *queue)
{
    return queue == NULL;
}
