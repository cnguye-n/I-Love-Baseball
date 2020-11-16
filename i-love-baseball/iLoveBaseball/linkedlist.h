#ifndef LINKEDLIST_H
#define LINKEDLIST_H

//#include "listempty.h"
#include "souvenir.h"
#include <iostream>
#include <algorithm>
using namespace std;

/******************************
 ** LINKED LIST NODE STRUCT **
******************************/
template<typename E>
struct Node{
    E data;
    Node *next;
    Node( E data ) : data(data), next(0) {}
};

/******************************
 **    LINKEDLIST CLASS     **
******************************/

template<typename E>
class LinkedList
{
public:
    /******************************
     **  NESTED ITERATOR CLASS  **
    ******************************/
    class Iterator
    {
    private:
        /******************************
         **    CLASS ATTRIBUTES     **
        ******************************/
        Node<E> *current;              // IN - iterator, IntNode pointer

    public:
        /******************************
         **       CONSTRUCTORS     **
        ******************************/
        Iterator();                    // default constructor
        Iterator(Node<E> *ptr);        // overloaded copy constructor

        /**************************************
         ** MUTATORS (OVERLOADED OPERATORS) **
        **************************************/
        E operator*();
        Iterator operator++();

        /***************************************
         ** ACCESSORS (OVERLOADED OPERATORS) **
        ***************************************/
        bool operator==(const Iterator& right) const;
        bool operator!=(const Iterator& right) const;
};

public:

    /******************************
     ** CONSTRUCTOR & DESTRUCTOR **
    ******************************/

    LinkedList();
    LinkedList(const LinkedList& source);
    ~LinkedList();
    LinkedList & operator=(const LinkedList& source);

    /***************
     ** MUTATORS **
    ****************/

    void push_front(const E& value);
    void push_back(const E& value);
    void pop_front(); //throw(ListEmpty);
    void clear();
    void select_sort();
    void insert_sorted_team(const E& value);
    void insert_sorted_stadium(const E& value);
    void insert_sorted_date(const E& value);
    void remove(int index);
    void remove_duplicates();
    void insert(const E& value, int position);

    /***************
     ** ACCESSORS **
    ****************/

    void display() const;
    const E& front(); //const throw(ListEmpty);
    const E& back(); //const throw(ListEmpty);
    Iterator begin() const;
    Iterator end() const;
    int length() const;
    E sum() const;
    bool isEmpty() const;
    E& access(int index);

private:

    /******************************
     **    CLASS ATTRIBUTES     **
    ******************************/

    Node<E> *tail;
    Node<E> *head;

    /******************************
     ** PRIVATE HELPER FUNCTIONS **
    ******************************/
    int get_length(Iterator current) const;
    E get_sum(Iterator current) const;
};

/*****************************************************************
 *
 * LinkedList CLASS TEMPLATE
 * _______________________________________________________________
 * The program creates the LinkedList class template. It has functions
 * to handle a singly linked list. Works with data types such as int,
 * double, and string.
 ******************************************************************/

/******************************
 ** CONSTRUCTOR & DESTRUCTOR **
******************************/

/*****************************************************************
 *
 *  DEFAULT CONSTRUCTOR LinkedList: Class LinkedList
 *________________________________________________________________
 *  This is the default constructor for the LinkedList.
 *  It initializes an empty list, has head and tail point to nullptr.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *
 *  POST-CONDITIONS
 *     Initializes head and tail pointers to nullptr.
 *****************************************************************/

template <typename E>
LinkedList<E>::LinkedList(): tail(nullptr), head(nullptr){}

/*****************************************************************
 *
 *  OVERLOADED COPY CONSTRUCTOR LinkedList: Class LinkedList
 *________________________________________________________________
 *  This is the overloaded copy constructor for LinkedList class.
 *  It's called whenever a LinkedList object is passed by value.
 *  Creates a deep copy of LinkedList object 'source'
 *  Copies head and tail location into current object.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     source (LinkedList), object to be deep copied
 *
 *  POST-CONDITIONS
 *     An LinkedList object is deep copied from the one passed in
 *****************************************************************/

template <typename E>
LinkedList<E>::LinkedList(const LinkedList& source)
                                  // IN - object to be copied
{
    // PROCESSING - initialize 'copy' pointer to traverse 'list'
    Node<E> *copy;
    copy = source.head;

    // PROCESSING - no need to copy if other list is empty
    if (copy == nullptr)
    {
        return;
    }

    // PROCESSING - create a new first node, set head to new Node
    //              and tail to nullptr
    this->head = new Node<E>(copy->data);
    this->head->next = nullptr;
    this->tail = this->head;

    // PROCESSING - advance to next node
    copy = copy->next;

    // PROCESSING - keep copying nodes using push_back until end of list
    while (copy != nullptr)
    {
        push_back(copy->data);
        copy = copy->next;
    }
}

/*****************************************************************
 *
 *  DECONSTRUCTOR ~LinkedList: Class LinkedList
 *________________________________________________________________
 *  This is the deconstructor for the LinkedList class. It
 *  deallocates remaining dynamic memory (all Nodes)
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *
 *  POST-CONDITIONS
 *     Deallocates dynamic memory
 *****************************************************************/

template <typename E>
LinkedList<E>::~LinkedList()
{
    // PROCESSING - goes through all nodes, deleting them
    while (head != nullptr)
    {
        Node<E> *current;
        current = head;
        head = head->next;
        delete current;
    }
    // PROCESSING - head is at nullptr, also set tail to nullptr
    tail = nullptr;
}

/*****************************************************************
 *
 *  OVERLOADED ASSIGNMENT OPERATOR = : Class LinkedList
 *________________________________________________________________
 *  This function is called whenever two existing LinkedList
 *  objects are set equal to each other using =
 *  It deep copies right hand side object onto left hand side object
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     source (LinkedList), object to be deep copied
 *  POST-CONDITIONS
 *     Returns *this, LinkedList object copied from list
 *****************************************************************/

template <typename E>
LinkedList<E>& LinkedList<E>::operator=(const LinkedList& source)
                                           // IN - object to be copied
{
    // PROCESSING - initialize 'copy' pointer, which will be used
    //              to traverse the list
    Node<E> *copy;

    // PROCESSING - only start copying if current list is not equal
    //              to 'list'
    if (this != &source)
    {
        // PROCESSING - delete all current nodes
        while (this->head != nullptr)
        {
            Node<E> *current;
            current = this->head;
            this->head = this->head->next;
            delete current;
        }

        // PROCESSING - set copy to list head
        copy = source.head;

        // PROCESSING - no need to copy if other list is empty
        if (copy == nullptr)
        {
        }
        else{
            // PROCESSING - create a new first node
            this->head = new Node<E>(copy->data);
            this->tail = this->head;
            this->head->next = nullptr;

            // PROCESSING - advance node
            copy = copy->next;

            // PROCESSING - copy rest of nodes using push_back
            while (copy != nullptr)
            {
                push_back(copy->data);
                copy = copy->next;
            }
        }

    }
    // OUT - return this object
    return *this;
}

/*****************************************************************
 *
 *  METHOD push_front(): Class LinkedList
 *________________________________________________________________
 *  This function adds a new Node to the front of
 *   the LinkedList, with the data portion set to value.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (E), to be used as data part of node
 *  POST-CONDITIONS
 *     A new Node gets added to the front of the list
 *****************************************************************/

template <typename E>
void LinkedList<E>::push_front(const E& value) // IN - data to be added
{
    // PROCESSING - create new node
    Node<E>* newNode;
    newNode = new Node<E>(value);

    // PROCESSING - if head is empty, set head and tail to newnode
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
    // PROCESSING - otherwise, link head to newNode
    //              reposition head to newnode
    else {
        newNode->next = head;
        head = newNode;
    }


}

/*****************************************************************
 *
 *  METHOD push_back(): Class LinkedList
 *________________________________________________________________
 *  This function adds a new Node to the end of
 *   the LinkedList, with the data portion set to value.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (E), to be used as data part of node
 *  POST-CONDITIONS
 *     A new Node gets added to the back of the list
 *****************************************************************/

template <typename E>
void LinkedList<E>::push_back(const E& value) // IN - data to be added
{
    // PROCESSING - create new node
    Node<E>* newNode;
    newNode = new Node<E>(value);

    // PROCESSING - if head is null, set head and tail to newNode
    if (head == nullptr)
    {
        tail = newNode;
        head = newNode;
        newNode->next = nullptr;
    }
    // PROCESSING - otherwise, link current tail to newNode
    //              reposition tail to newNode
    else {
        tail->next = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
}

/*****************************************************************
 *
 *  METHOD pop_front(): Class LinkedList
 *________________________________________________________________
 *  This function removes the first node at the front,
*           only if the list isn't empty.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     The first node from the front gets removed from the list
 *****************************************************************/

template <typename E>
void LinkedList<E>::pop_front() //throw(ListEmpty)
{

    // PROCESSING - if list is empty, head and tail to nullptr
    //              if one Node in list, delete Node and set
    //              head and tail to nullptr
    //              if more than one Node, delete front node
    //              set head to next node
    Node<E>* current;
    current = head;

    //if (head == nullptr)
    //    throw ListEmpty();

    if (current != nullptr && current->next != nullptr)
    {
        head = head->next;
        delete current;
        current = nullptr;
    }
    else if (current != nullptr && current->next == nullptr)
    {
        delete current;
        head = tail = nullptr;
    }
    else {
        tail = nullptr;
    }

}

/*****************************************************************
 *
 *  METHOD clear(): Class LinkedList
 *________________________________________________________________
 *  This function makes the list empty by deallocating all the
 *  nodes in the list
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Deallocates all nodes in list
 *****************************************************************/

template <typename E>
void LinkedList<E>::clear()
{
    // PROCESSING - goes through all nodes, deleting them
    while (head != nullptr)
    {
        Node<E> *current;
        current = head;
        head = head->next;
        delete current;
    }
    // PROCESSING - head is at nullptr, also set tail to nullptr
    tail = nullptr;
}

/*****************************************************************
 *
 *  METHOD select_sort(): Class LinkedList
 *________________________________________________________________
 *  This function sorts the data values in the link
 *           list, in ascending order, by selection sort.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     The data values in the link list get sorted into ascending
 *     order by selection sort.
 *****************************************************************/

template <typename E>
void LinkedList<E>::select_sort()
{
    // PROCESSING - create current ptr to loop through nodes
    Node<E>* current;
    current = head;

    // PROCESSING - 2 loops, outer one loops through each element in list
    //              inner loop compares element to other elements in list
    //              and takes the smallest data element, storing the
    //              location in ptr c. Once exiting inner loop, the outer
    //              loop swaps the data values between current ptr and
    //              c ptr (which holds the smallest data value)
    //              so the smallest remaining data value gets swapped
    //              to its designated position which is closer to front
    //              of list, sorting the list in ascending value
    while(current != nullptr)
    {
        Node<E>* c;
        c = current;
        Node<E>* n;
        n = current->next;

        while (n != nullptr)
        {
            if (c->data > n->data)
            {
                c = n;
            }
            n = n->next;
        }

        E temp = current->data;
        current->data = c->data;
        c->data = temp;
        current = current->next;
    }
}

/*****************************************************************
 *
 *  METHOD insert_sorted_stadium(): Class LinkedList
 *________________________________________________________________
 *  This function assumes the list is sorted in ascending
*           order and inserts a node with data set to value
*           in the correct sorted position
*  SORTS BY STADIUM NAME
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (E), to be used as data part of node
 *  POST-CONDITIONS
 *     The list receives a new node inserted into the correct
 *     position in the sorted list.
 *****************************************************************/

template <typename E>
void LinkedList<E>::insert_sorted_stadium(const E& value)
                      // IN - to be used as data part of Node
{
    // PROCESSING - create current ptr to loop through list
    //               create new node with designated value
    Node<E>* current;
    current = head;

    Node<E>* newNode;
    newNode = new Node<E>(value);

    // PROCESSING - if empty list, create new node, set head and tail
    //              to newNode
    if (current == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
    // PROCESSING - if value is smaller than the one at head
    //              add node to front
    //              push_front creates another newNode so delete
    //              the one created earlier
    else if(head->data->get_stadium() >= value->get_stadium())
    {
        push_front(value);
        delete newNode;
    }
    // PROCESSING - if value is larger than the one at tail
    //              add node to back
    //              push_back creates another newNode so delete
    //              the one created earlier
    else if(tail->data->get_stadium() <= value->get_stadium())
    {
        push_back(value);
        delete newNode;
    }
    else
    {
        // PROCESSING - since list is sorted, we're looking at data values
        //              and where we can insert the new node so that the
        //              list stays sorted. previous node is =< value and
        //              next node is >= value keep looping till we find
        //              position
        while(current != nullptr)
        {// capitalize word
            if (current->data->get_stadium() <= value->get_stadium()
              && current->next->data->get_stadium() >= value->get_stadium())
            {
                break;
            }
            else{
                current = current->next;
            }
        }

        // PROCESSING - insert new node at the correct position
        //              after current
        newNode->next = current->next;
        current->next = newNode;
    }
}

/*****************************************************************
 *
 *  METHOD insert_sorted_team(): Class LinkedList
 *________________________________________________________________
 *  This function assumes the list is sorted in ascending
*           order and inserts a node with data set to value
*           in the correct sorted position
*  SORTS BY TEAM NAME
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (E), to be used as data part of node
 *  POST-CONDITIONS
 *     The list receives a new node inserted into the correct
 *     position in the sorted list.
 *****************************************************************/

template <typename E>
void LinkedList<E>::insert_sorted_team(const E& value)
                      // IN - to be used as data part of Node
{
    // PROCESSING - create current ptr to loop through list
    //               create new node with designated value
    Node<E>* current;
    current = head;

    Node<E>* newNode;
    newNode = new Node<E>(value);

    // PROCESSING - if empty list, create new node, set head and tail
    //              to newNode
    if (current == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
    // PROCESSING - if value is smaller than the one at head
    //              add node to front
    //              push_front creates another newNode so delete
    //              the one created earlier
    else if(head->data->get_team() >= value->get_team())
    {
        push_front(value);
        delete newNode;
    }
    // PROCESSING - if value is larger than the one at tail
    //              add node to back
    //              push_back creates another newNode so delete
    //              the one created earlier
    else if(tail->data->get_team() <= value->get_team())
    {
        push_back(value);
        delete newNode;
    }
    else
    {
        // PROCESSING - since list is sorted, we're looking at data values
        //              and where we can insert the new node so that the
        //              list stays sorted. previous node is =< value and
        //              next node is >= value keep looping till we find
        //              position
        while(current != nullptr)
        {
            if (current->data->get_team() <= value->get_team()
              && current->next->data->get_team() >= value->get_team())
            {
                break;
            }
            else{
                current = current->next;
            }
        }

        // PROCESSING - insert new node at the correct position
        //              after current
        newNode->next = current->next;
        current->next = newNode;
    }
}

/*****************************************************************
 *
 *  METHOD insert_sorted(): Class LinkedList
 *________________________________________________________________
 *  This function assumes the list is sorted in ascending
*           order and inserts a node with data set to value
*           in the correct sorted position
*  SORTS BY STADIUM OPEN DATE
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (E), to be used as data part of node
 *  POST-CONDITIONS
 *     The list receives a new node inserted into the correct
 *     position in the sorted list.
 *****************************************************************/

template <typename E>
void LinkedList<E>::insert_sorted_date(const E& value)
                      // IN - to be used as data part of Node
{
    // PROCESSING - create current ptr to loop through list
    //               create new node with designated value
    Node<E>* current;
    current = head;

    Node<E>* newNode;
    newNode = new Node<E>(value);

    // PROCESSING - if empty list, create new node, set head and tail
    //              to newNode
    if (current == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
    // PROCESSING - if value is smaller than the one at head
    //              add node to front
    //              push_front creates another newNode so delete
    //              the one created earlier
    else if(head->data->get_date() >= value->get_date())
    {
        push_front(value);
        delete newNode;
    }
    // PROCESSING - if value is larger than the one at tail
    //              add node to back
    //              push_back creates another newNode so delete
    //              the one created earlier
    else if(tail->data->get_date() <= value->get_date())
    {
        push_back(value);
        delete newNode;
    }
    else
    {
        // PROCESSING - since list is sorted, we're looking at data values
        //              and where we can insert the new node so that the
        //              list stays sorted. previous node is =< value and
        //              next node is >= value keep looping till we find
        //              position
        while(current != nullptr)
        {
            if (current->data->get_date() <= value->get_date()
              && current->next->data->get_date() >= value->get_date())
            {
                break;
            }
            else{
                current = current->next;
            }
        }

        // PROCESSING - insert new node at the correct position
        //              after current
        newNode->next = current->next;
        current->next = newNode;
    }
}

/*****************************************************************
 *
 *  METHOD remove_duplicates(): Class LinkedList
 *________________________________________________________________
 *  This function removes all nodes with values that are
 *  duplicates in the list. It removes the later duplicates.
 *  Does not assume list is sorted.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     The updated list does not contain any nodes with duplicate
 *     values
 *****************************************************************/

template <typename E>
void LinkedList<E>::remove_duplicates()
{
    // PROCESSING - create pointers
    Node<E>* current, *check, *trash;
    current = head;

    // PROCESSING - loop through list
    while(current != nullptr)
    {
        check = current;

        // PROCESSING - if data at current node and next are same
        //              delete duplicate
        //              keep checking until end of list
        //              for each remaining element in list
        while (check != nullptr && check->next != nullptr)
        {
            if (current->data == check->next->data)
            {
                trash = check->next;
                check->next = check->next->next;
                delete trash;
                trash = nullptr;
            }
            else{
                check = check->next;
            }
        }
        current = current->next;
    }
}

template <typename E>
void LinkedList<E>::remove(int index)
{
    // PROCESSING - create pointers
    Node<E>* current, *check, *trash;
    current = head;

    if (!index)
        pop_front();
    else if (index >= length())
    {
        return;
    }
    else {
        // PROCESSING - loop through list
        for (int i = 0; i < index - 1; i++)
        {
            current = current->next;
        }

        trash = current->next;
        current->next = current->next->next;
        delete trash;
        trash = nullptr;
    }
}

/*****************************************************************
 *
 *  METHOD display(): Class LinkedList
 *________________________________________________________________
 *  This function displays all data from the LinkedList.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Prints out data values from the IntList
 *****************************************************************/

template <typename E>
void LinkedList<E>::display() const
{
    // PROCESSING - create new current ptr going through all nodes
    Node<E> *current;
    current = head;

    // OUT - print out data for all nodes in list, looping through
    //       the nodes
    while (current != nullptr)
    {
        if (current->next == nullptr)
        {
            cout << current->data;
        }
        else
        {
            cout << current->data << " ";
        }
        current = current->next;
    }
}

/*****************************************************************
 *
 *  METHOD front(): Class LinkedList
 *________________________________________________________________
 *  This function returns the data in the head of the linked list.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the data (E) in the head of the linked list.
 *****************************************************************/

template <typename E>
const E& LinkedList<E>::front() //const throw(ListEmpty)
{
    //if (head == nullptr)
    //    throw ListEmpty();

    // OUT - return data at head of linked list
    return head->data;
}

/*****************************************************************
 *
 *  METHOD back(): Class LinkedList
 *________________________________________________________________
 *  This function returns the data in the tail of the linked list.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the data (E) in the tail of the linked list.
 *****************************************************************/
template <typename E>
const E& LinkedList<E>::back() //const throw(ListEmpty)
{
    //if (head == nullptr)
    //    throw ListEmpty();

    // OUT - return data at tail of linked list
    return tail->data;
}

/*****************************************************************
 *
 *  METHOD begin(): Class LinkedList
 *________________________________________________________________
 *  This function returns an iterator at the beginning of the
 *  linked list. Returns iterator pointing to head.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns an iterator pointing to head, the beginning of the
 *     linked list.
 *****************************************************************/

template <typename E>
typename LinkedList<E>::Iterator LinkedList<E>::begin() const
{
    // OUT - set iterator at beginning of linked list & return
    return Iterator(head);
}

/*****************************************************************
 *
 *  METHOD end(): Class LinkedList
 *________________________________________________________________
 *  This function returns an iterator one element past the last
 *  element of the linked list. Returns iterator pointing to to NULL.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns an iterator one element past the last element of the
 *     linked list, pointing to NULL.
 *****************************************************************/

template <typename E>
typename LinkedList<E>::Iterator LinkedList<E>::end() const
{
    // OUT - set iterator at end of linked list & return
    return Iterator(nullptr);
}

/*****************************************************************
 *
 *  METHOD length(): Class LinkedList
 *________________________________________________________________
 *  This function recursively determines the length of the linked list.
 *  Wrapper function for get_length
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the length of the linked list.
 *****************************************************************/

template <typename E>
int LinkedList<E>::length() const
{
    // PROCESSING - create iterator to go through list
    Iterator current(begin());

    // OUT - call get_length, which holds the recursive part
    return get_length(current);
}

/*****************************************************************
 *
 *  METHOD get_length(): Class IntList
 *________________________________________________________________
 *  This function recursively determines the length of the linked list.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the length of the linked list.
 *****************************************************************/

template <typename E>
int LinkedList<E>::get_length(Iterator current) const
                              // IN - iterator to go through linked lists
{
    // PROCESSING - if iterator at nullptr, return 0
    if (current == nullptr)
    {
        return 0;
    }
    // PROCESSING - else call the recursive function, add 1 to length
    return (1 + get_length(++current));
}

/*****************************************************************
 *
 *  METHOD sum(): Class LinkedList
 *________________________________________________________________
 *  This function recursively determines the sum of the linked list.
 *  Wrapper function, calls helper function get_sum().
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the sum of the data in the linked list.
 *****************************************************************/

template <typename E>
E LinkedList<E>::sum() const
{
    // PROCESSING - create iterator to go through list
    Iterator current(begin());

    // OUT - call get_sum, which holds the recursive part
    return get_sum(current);

}

/*****************************************************************
 *
 *  METHOD get_sum(): Class LinkedList
 *________________________________________________________________
 *  This function recursively determines the sum of the linked list.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the sum of the data in the linked list.
 *****************************************************************/

template <typename E>
E LinkedList<E>::get_sum(Iterator current) const
{
    // PROCESSING - if iterator at nullptr, return 0
    if (current == nullptr)
    {

        return 0;
    }
    // PROCESSING - else call the recursive function, add data value
    //              to the sum
    else
    {
        E item;
        item = *current;
        return (item + get_sum(++current));
    }
}

/*****************************************************************
 *
 *  METHOD isEmpty(): Class LinkedList
 *________________________________________________________________
 *  This function sees whether this list is empty
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns true if list is empty (head at nullptr), else false
 *****************************************************************/

template <typename E>
bool LinkedList<E>::isEmpty() const
{
    // PROCESSING & OUT - return true if list is empty
    //                    aka head at nullptr
    if (head == nullptr)
    {
        return true;
    }
    else {
        return false;
    }
}

/*****************************************************************
 *
 * Iterator CLASS (Nested in LinkedList private)
 * _______________________________________________________________
 * The Iterator nested class creates an iterator for the LinkedList
 * linked list class, essentially a helper class to LinkedList. It is
 * a pointer which has *, ==, ++, and != overloaded functions, used
 * to better traverse the linked list.
 ******************************************************************/

/******************************
 **       CONSTRUCTORS     **
******************************/

/*****************************************************************
 *
 *  DEFAULT CONSTRUCTOR IntListIterator: Class IntListIterator
 *________________________________________________________________
 *  This is the default constructor for the IntListIterator.
 *  It initializes the iterator to point to null.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *
 *  POST-CONDITIONS
 *     Initializes iterator pointer to NULL.
 *****************************************************************/

template <typename E>
LinkedList<E>::Iterator::Iterator(): current(nullptr)
{}

/*****************************************************************
 *
 *  OVERLOADED COPY CONSTRUCTOR Iterator: Class Iterator
 *________________________________________________________________
 *  This is the overloaded copy constructor for Iterator class.
 *  It's called whenever an Iterator object is passed by value.
 *  Creates a deep copy of IntListIterator pointer 'ptr'
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     ptr (Node<E>), node pointer to be copied
 *
 *  POST-CONDITIONS
 *     An Iterator object is deep copied from the one passed in
 *****************************************************************/

template <typename E>
LinkedList<E>::Iterator::Iterator(Node<E>* ptr)
{
    // PROCESSING - copy ptr
    this->current = ptr;
}

/*****************************************************************
 *
 *  OVERLOADED DEREFERENCE OPERATOR * : Class Iterator
 *________________________________________________________________
 *  This function is called whenever an Iterator object is
 *  dereferenced using the * operator, overloading *. It returns
 *  the info at the node
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns the info at the node
 *****************************************************************/

template <typename E>
E LinkedList<E>::Iterator::operator*()
{
    // OUT - return data
    return current->data;
}

/*****************************************************************
 *
 *  OVERLOADED PRE INCREMENT OPERATOR ++ : Class Iterator
 *________________________________________________________________
 *  This function is called whenever an Iterator object
 *  pre-incremented using the ++ operator. It returns an iterator
 *  pointing to the next node
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     None
 *  POST-CONDITIONS
 *     Returns an iterator pointing to the next node
 *****************************************************************/

template <typename E>
typename LinkedList<E>::Iterator LinkedList<E>::Iterator::operator++()
{
    // PROCESSING - if current iterator doesn't point to null,
    //              move pointer to next
    if (current != nullptr)
    {
        current = current->next;
    }
    // OUT - return ptr
    return *this;
}

/*****************************************************************
 *
 *  OVERLOADED EQUALITY OPERATOR == : Class Iterator
 *________________________________________________________________
 *  This function overloads the equality operator. Returns true if
 *  this iterator is equal to the one on the right, otherwise false.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     right (Iterator) - object to be compared
 *  POST-CONDITIONS
 *     Returns true if the Iterator objects are equal,
 *     otherwise false.
 *****************************************************************/

template <typename E>
bool LinkedList<E>::Iterator::operator==(const Iterator& right) const
{
    // OUT - return bool
    return this->current == right.current;
}

/*****************************************************************
 *
 *  OVERLOADED INEQUALITY OPERATOR != : Class Iterator
 *________________________________________________________________
 *  This function overloads the not equal to operator. Returns true if
 *  this iterator is not equal to the one on the right, otherwise false.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     right (Iterator) - object to be compared
 *  POST-CONDITIONS
 *     Returns true if the Iterator objects are not equal,
 *     otherwise false.
 *****************************************************************/

template <typename E>
bool LinkedList<E>::Iterator::operator!=(const Iterator& right) const
{
    // OUT - return bool
    return this->current != right.current;
}

/*****************************************************************
 *
 *  METHOD access() : Class LinkedList
 *________________________________________________________________
 *  This function returns the data at the specified index of the
 *  linked list.
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     index (int) - index to be accessed
 *  POST-CONDITIONS
 *     Returns the data value at the index specified
 *****************************************************************/

template <typename E>
E& LinkedList<E>::access(int index) // IN - index to access
{
    // PROCESSING - create ptr to loop thru
    Node<E>* current = head;

    // PROCESSING - loop thru, return data at index
    if (index <= length())
    {
        for (int i = 0; i < index; i++)
        {
            current = current->next;
        }
        return current->data;
    }
}

/*****************************************************************
 *
 *  METHOD insert() : Class LinkedList
 *________________________________________________________________
 *  This function inserts a new element to the linked list at
 *  position
 *________________________________________________________________
 *  PRE-CONDITIONS
 *     value (const E&) - value to be inserted
 *     index (int) - index to be inserted at
 *  POST-CONDITIONS
 *     Modifies list by inserting node at index
 *****************************************************************/

template <typename E>
void LinkedList<E>::insert(const E& value,       // IN - data value to add
                           int index)            // IN - index to insert
{
    // PROCESSING - create node ptrs
    Node<E>* current, *newNode;

    // PROCESSING - ptr to loop and new node
    current = head;
    newNode = new Node<E>(value);

    // PROCESSING - if empty list, create new node, set head and tail
    //              to newNode
    if (current == nullptr)
    {
        head = newNode;
        tail = newNode;
        newNode->next = nullptr;
    }
    else
    {
        // PROCESSING - if index is 0, push front
        if (index == 0)
        {
            push_front(value);
            delete newNode;
        }
        // PROCESSING - if index is in middle, loop thru until position
        //              insert node with value
        else if (index <= length())
        {
            for (int i = 1; i < index; i++)
            {
                current = current->next;
            }
            // PROCESSING - insert new node at the correct position
            //              after current
            newNode->next = current->next;
            current->next = newNode;
        }
        // PROCESSING - if index is 1 greater than length, push back
        else if (index + 1 == length())
        {
            push_back(value);
            delete newNode;
        }
    }
}

#endif // LINKEDLIST_H
