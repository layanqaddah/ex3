//
// Created by layan & omar on 23/05/2022.
//

#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H

#include<iostream> ////////////////////////////////////////////////////////////// remember to remove if not needed inside Queue.h anymore!

template <class T>
class Queue
{

public:
    Queue():m_frontNode(nullptr), m_backNode(nullptr), m_queueSize(0){};
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    ~Queue();

    /**--------- Interface ---------**/
    void printQueue();
    void pushBack(const T& newNodeData);
    T& front();
    void popFront();
    int size() const;

    /**--------- Iterator ---------**/
    class Iterator;
    Iterator begin()
    {
        return Iterator(m_frontNode);
    };
    Iterator end()
    {
        return Iterator(nullptr);
    };
    /**--------- ConstIterator ---------**/
    class ConstIterator;
    ConstIterator begin() const
    {
        return ConstIterator(m_frontNode);
    };
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

private:
    class Node;
    Node *m_frontNode;
    Node *m_backNode;
    int m_queueSize;

    class Node
    {
    public:
        T m_nodeValue;
        Node *m_nextNode;

        explicit Node(const T& nodeValue):m_nodeValue(nodeValue),m_nextNode(nullptr){};
        Node(const Node& nodeValue)=delete;
        Node& operator=(const Node& nodeValue)=delete;
        ~Node()=default;
    };
    
};



/**
 * Queue Copy C'tor
 * */
template <class T>
Queue<T>::Queue(const Queue<T>& queue):m_frontNode(new Node(queue.m_frontNode->m_nodeValue)),
                     m_backNode(new Node(queue.m_backNode->m_nodeValue)), m_queueSize(queue.m_queueSize)
{
    Node* ptr=m_frontNode;
    for(Queue<T>::ConstIterator it=queue.begin(); it!=queue.end(); ++it)
    {
        if(it!=queue.m_frontNode && it!=queue.m_backNode)
        {
            Node *newNodePtr = new Node(*it);
            ptr->m_nextNode = newNodePtr;
            ptr = newNodePtr;
        }
    }
    ptr->m_nextNode=m_backNode;
}


/**
 * Queue Copy C'tor
 * */
template <class T>
Queue<T>::~Queue()
{
    Node* tmp=m_frontNode;
    while (m_frontNode!=m_backNode)
    {
        m_frontNode=m_frontNode->m_nextNode;
        delete tmp;
        tmp=m_frontNode;
    }
    if(m_backNode!= nullptr)
    {
        delete m_backNode;
    }

    m_frontNode= nullptr;
    m_backNode= nullptr;
    m_queueSize=0;
}

/**
 * @brief adds a new element to the end of the queue
 * 
 * @param element to add to queue  
 * 
 * @return ** void
 */
template <class T>
void Queue<T>::pushBack(const T& newNodeData)
{
    Node *newNodePtr = new Node(newNodeData);
    if(m_backNode==nullptr)
    {
        m_backNode=m_frontNode=newNodePtr;
    }
    else
    {
        m_backNode->m_nextNode=newNodePtr;
        m_backNode=newNodePtr;
    }
    m_queueSize++;
}

/**
 * @brief returns the front element of queue
 * 
 * @return ** queue front 
 */
template <class T>
T& Queue<T>::front()
{
    return this->m_frontNode->m_nodeValue;
};

/**
 * @brief removes the front element of queue 
 *
 * @return ** void 
 */
template <class T>
void Queue<T>::popFront()
{
    Node *target=m_frontNode;
    m_frontNode=m_frontNode->m_nextNode;
    delete target;
    --m_queueSize;
};

/**
 * @brief size of the queue
 * 
 * @return **queue size
 */
template <class T>
int Queue<T>::size() const
{
    return this->m_queueSize;
};


template <class T>
void Queue<T>::printQueue()
{
    for(T& elem:*this)
    {
        std::cout<<elem<<std::endl;
    }
}


/**--------------------------------------------------- Iterator ---------------------------------------------------**/
/************change the names of the member variables to m_name format**/
template <class T>
class Queue<T>::Iterator
{
private:
    Node *current_node;
public:
    explicit Iterator(Node* node):current_node(node){};
    Iterator(const Iterator&)=default;
    ~Iterator()=default;
    Iterator& operator=(const Iterator&)=default;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator)const;
    T& operator*();

};


/*** WHAT TO DO IF ANY OF THESE OPERATORS ARE USED
 * ON THE ITERATOR RETURNED BY EMD ?  OR DOES THE CONVENTION PROHIBIT SUCH USE ?***/
template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    current_node = current_node->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Queue<T>::Iterator *tmp=this;
    ++*this;
    return *tmp;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)const
{
    return !(current_node==iterator.current_node);
}

template <class T>
T& Queue<T>::Iterator::operator*()
{
    return current_node->m_nodeValue;
}


/**--------------------------------------------------- ConstIterator ---------------------------------------------------**/
/*
 * i had to remove the explicit keyword from the c'tor for the converstion between Node to ConstIterator in the for loop inside the queue copy c'tor
 */
template <class T>
class Queue<T>::ConstIterator
{
public:
    ConstIterator(const Node *node):m_currentNode(node){};
    ConstIterator(const ConstIterator&)=default;
    ~ConstIterator()=default;
    ConstIterator& operator=(const ConstIterator&)=default;
    /**should we decalre the ++ operator as const ??????????????**/
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator!=(const ConstIterator& constIterator) const;
    const T& operator*()const;

private:
    const Node *m_currentNode;
};


template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    m_currentNode=m_currentNode->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    Queue<T>::ConstIterator *tmp=this;
    ++*this;
    return *tmp;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator)const
{
    return !(m_currentNode==constIterator.m_currentNode);
}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return m_currentNode->m_nodeValue;
}



#endif //ASSIGNMENT3_QUEUE_H
