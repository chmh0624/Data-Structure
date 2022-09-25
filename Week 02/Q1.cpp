/**
 * A Node<T> class of Doublely Linked List class
 */
template<class T>
class Node {
  public:

  /**
   * Construct a new Node<T> object with no parameter
   */
  Node<T>() {
    this -> prev = NULL;
    this -> next = NULL;
  }

  /**
   * Construct a new Node<T> object with parameter
   * @param data: data to put in
   */
  Node<T>(T _data) {
    this -> prev = NULL;
    this -> next = NULL;
    this -> data = _data;
  }

  /**
   * Construct a new Node<T> object with parameters
   * @param data: data to put in
   * @param prev: pointer to the previous node<T>
   * @param next: pointer to the next node<T>
   */
  Node<T>(T _data, Node<T> *_prev, Node<T> *_next) {
    this -> prev = _prev;
    this -> next = _next;
    this -> data = _data;
  }
    
    Node<T> *prev;
    Node<T> *next;
    T data;
};

/**
 * A Doublely Linked List class
 */
template<class T>
class LinkedList {
  public:

  /**
   * Construct a new LinkedList object with no parameter
   */
  LinkedList() {
    this -> head = NULL;
    this -> tail = NULL;
  }

  /**
   * Add a node<T> to the tail of the linked list
   * @param data: data to put in
   */
  void addToTail(T _data) {
    if (this -> tail == NULL) {
        this -> tail = new Node<T>(_data);
        this -> head = this -> tail;
        return ;
    }
    this -> tail -> next = new Node<T>(_data);
    this -> tail -> next -> prev = this -> tail;
    this -> tail = this -> tail -> next;
  }

  /**
   * Add a node<T> to the head of the linked list
   * @param data: data to put in
   */
  void addToHead(T _data) {
    if (this -> head == NULL) {
        this -> head = new Node<T>(_data);
        this -> tail = this -> head;
        return ;
    }
    this -> head -> prev = new Node<T>(_data);
    this -> head -> prev -> next = this -> head;
    this -> head = this -> head -> prev;
  }

  /**
   * Delete a node<T> from the linked list with the given data from the head
   * If there are no data to be deleted, then do nothing
   * @param data: data to delete
   */
  void deleteData(T _data) {
    if (this -> head == NULL) return ;
    if (this -> head == this -> tail) {
        delete this -> head;
        this -> head = NULL;
        this -> tail = NULL;
        return ;
    }

    if (this -> head -> data == _data) {
        Node<T> *tmp = this -> head;
        this -> head = this -> head -> next;
        this -> head -> prev = NULL;
        delete tmp;
        return ;
    }
    
    Node<T> *cur = this -> head;
    while (cur) {
        if (cur -> data == _data) {
            if (cur == this -> tail) {
                Node<T> *temp = this -> tail;
                this -> tail = this -> tail -> prev;
                this -> tail -> next = NULL;
                delete temp;
            }
            else {
                cur -> prev -> next = cur -> next;
                cur -> next -> prev = cur -> prev;
                delete cur; 
            }
            return ;
        }
        cur = cur -> next;
    }
    return ;
  }

  /**
   * Delete valid n node<T>s from the linked list with the given data from the head
   * If there are no more data to be deleted, then just skip
   * @param data: data to delete
   * @param n: max number of node<T>s to delete
   */
  void deleteData(T _data, int n) {
    if (n == 0) return ;
    deleteData(_data);
    deleteData(_data, n-1);
  } 

  /**
   * Overload the operator << to print out all the data in the linked list from the head
   * There is a \n in the end of each print
   * 
   * Output example: 
   * If your linked list data is 5, 4, 3, 2, 1
   * then you should print out "(5, 4, 3, 2, 1)" with the content in quotes but without the quotes
   */
  friend std::ostream &operator<<(std::ostream &out, LinkedList * n) {
    Node<T> *cur = n -> head;
    out << "(";
    while (cur -> next) {
        out << cur -> data << ", ";
        cur = cur -> next;
    }
    out << cur -> data << ")\n";
  }

    Node<T> *head;
    Node<T> *tail;
};
