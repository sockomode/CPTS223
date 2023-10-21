
#include <iostream>

template <typename T>
struct node {
    T data;
    node* next;

    node() { next = nullptr; }

    ~node() { delete next; }
};

template <class T>
class List {
public:
    List();
    ~List();

    bool isEmpty();
    void clearList();
    node<T>* getHead();
    void setHead(node<T>* head);
    int getLength();
    node<T>* getNodeAtPosition(int n);

    bool insertAtFront(T& data);
    bool removeNode(node<T>* match);

private:
    node<T>* pHead;
};

/*************************************************************
 * Function: List ()                                         *
 * Description: constructor                                  *
 *************************************************************/
template <class T>
List<T>::List()
{
    pHead = nullptr;
}

/*************************************************************
 * Function: ~List ()                                        *
 * Description: destructor                                   *
 *************************************************************/
template <class T>
List<T>::~List()
{
    delete pHead;
}

/*************************************************************
 * Function: isEmpty ()                                      *
 * Description: checks if the list is empty or not           *
 *************************************************************/
template <class T>
bool List<T>::isEmpty()
{
    return (pHead == nullptr);
}

/*************************************************************
 * Function: clearList ()                                    *
 * Description: deletes all nodes in list and resets pHead   *
 *		to NULL                                              *
 *************************************************************/
template <class T>
void List<T>::clearList()
{
    if (!isEmpty())
    {
        delete pHead;
        pHead = nullptr;
    }
}

/*************************************************************
 * Function: getHead ()                                      *
 * Description: getter function for head                     *
 *************************************************************/
template <class T>
node<T>* List<T>::getHead()
{
    return pHead;
}

/*************************************************************
 * Function: setHead ()                                      *
 * Description: setter function for head                     *
 *************************************************************/
template <class T>
void List<T>::setHead(node<T>* head)
{
    pHead = head;
}

/*************************************************************
 * Function: getLength ()                                    *
 * Description: getter function for length                   *
 *************************************************************/
template <class T>
int List<T>::getLength()
{
    int count = 0;
    node<T>* pCurrent = this->getHead();

    while (pCurrent != nullptr)
    {
        pCurrent = pCurrent->next;
        count++;
    }

    return count;
}

/*************************************************************
 * Function: getNodeAtPosition ()                            *
 * Description: returns pointer to the node at specified     *
 *        position n                                         *
 *************************************************************/
template <class T>
node<T>* List<T>::getNodeAtPosition(int n)
{
    if (n <= this->getLength() - 1)
    {
        node<T>* pCurrent = pHead;
        for (int i = 0; i < n; i++)
        {
            pCurrent = pCurrent->next;
        }

        return pCurrent;
    }
    else {
        return nullptr;
    }
}

/*************************************************************
 * Function: insertAtFront ()                                *
 * Description: inserts data at the front                    *
 *************************************************************/
template <class T>
bool List<T>::insertAtFront(T& data)
{
    node<T>* pNew = new node<T>;
    pNew->data = data;

    if (pNew != 0)
    {
        if (isEmpty())
        {
            pHead = pNew;
        }
        else
        {
            pNew->next = pHead;
            pHead = pNew;
        }

        return true;
    }

    return false;
}

/*************************************************************
 * Function: removeNode ()                                   *
 * Description: removes node                                 *
 *************************************************************/
template <class T>
bool List<T>::removeNode(node<T>* match)
{
    node<T>* pCurrent = this->getHead();

    if (pCurrent->data == match->data)
    {
        this->setHead(pCurrent->next);
        delete pCurrent;
        return true;
    }
    else {
        node<T>* pPrev = pCurrent;
        pCurrent = pCurrent->next;

        while (pCurrent != nullptr)
        {
            if (pCurrent->data == match->data)
            {
                pPrev->next = pCurrent->next;
                delete pCurrent;
                return true;
            }
            pPrev = pCurrent;
            pCurrent = pCurrent->next;
        }
    }

    return false;
}