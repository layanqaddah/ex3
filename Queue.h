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
    Queue():m_frontNode(nullptr), m_backNode(nullptr), m_queueSize(0){}
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    ~Queue();

    /**--------- Interface ---------**/
    void printQueue();    //////////////////////////////////////////////////////////////////////////// to be removed
    void pushBack(const T& newNodeData);
    T& front();
    void popFront();
    int size() const;

    /**--------- Iterator ---------**/
    class Iterator;
    Iterator begin()
    {
        return Iterator(m_frontNode);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }
    /**--------- ConstIterator ---------**/
    class ConstIterator;
    ConstIterator begin() const
    {
        return ConstIterator(m_frontNode);
    }
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }
    /**--------- Exceptions ---------**/
    class EmptyQueue{};
    class InvalidOperation{};

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

        explicit Node(const T& nodeValue):m_nodeValue(nodeValue),m_nextNode(nullptr){}
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
    try {
        for (Queue<T>::ConstIterator it = queue.begin(); it != queue.end(); ++it) {
            if (it != queue.m_frontNode && it != queue.m_backNode) {
                Node *newNodePtr = new Node(*it);
                ptr->m_nextNode = newNodePtr;
                ptr = newNodePtr;
            }
        }
    }catch(const std::bad_alloc&)
    {
        while(m_frontNode!=nullptr)
        {
            Node* tmp=m_frontNode;
            m_frontNode=m_frontNode->m_nextNode;
            delete tmp;
        }
        delete m_backNode;
        throw;  ///////////////////////////////////////////////////////////////////// added this line to forward the exception to the next try/catch block
    }
    ptr->m_nextNode=m_backNode;
}


/**
 * Queue D'tor
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
    Node *newNodePtr = new Node(newNodeData);  /////////////////////////////////////////////Question: new throws std::bad_alloc automatically. since we have only one allocation inside the pushback function then we don't need to create a try/catch block since we don't have to release previously allocated nodes
    ///another question: since every block that uses the copy c'tor or the pushBack function makes use of dynamic allocations and could throw an std::bad_alloc, should we enclose such block with a try/cathc block ?
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
    if(m_queueSize<=0)
    {
        throw EmptyQueue();
    }
    return this->m_frontNode->m_nodeValue;
}

/**
 * @brief removes the front element of queue 
 *
 * @return ** void 
 */
template <class T>
void Queue<T>::popFront()
{
    if(m_queueSize<=0)
    {
        throw EmptyQueue();
    }
    Node *target=m_frontNode;
    m_frontNode=m_frontNode->m_nextNode;
    delete target;
    --m_queueSize;
}

/**
 * @brief size of the queue
 * 
 * @return **queue size
 */
template <class T>
int Queue<T>::size() const
{
    return this->m_queueSize;
}


template <class T>
void Queue<T>::printQueue()
{
    for(T& elem:*this)
    {
        std::cout<<elem<<std::endl;
    }
}


/**--------------------------------------------------- Iterator ---------------------------------------------------**/
template <class T>
class Queue<T>::Iterator
{
private:
    Node *m_currentNode;
public:
    explicit Iterator(Node* node):m_currentNode(node){};
    Iterator(const Iterator&)=default;
    ~Iterator()=default;
    Iterator& operator=(const Iterator&)=default;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator)const;
    T& operator*();

};

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    m_currentNode = m_currentNode->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    Queue<T>::Iterator tmp=*this;
    ++*this;
    return tmp;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)const
{
    return !(m_currentNode==iterator.m_currentNode);
}

template <class T>
T& Queue<T>::Iterator::operator*()
{
    return m_currentNode->m_nodeValue;
}


/**--------------------------------------------------- ConstIterator ---------------------------------------------------**/
template <class T>
class Queue<T>::ConstIterator
{
public:
    ConstIterator(const Node *node):m_currentNodePtr(node){};
    ConstIterator(const ConstIterator&)=default;
    ~ConstIterator()=default;
    ConstIterator& operator=(const ConstIterator&)=default;
    /**should we decalre the ++ operator as const ??????????????**/
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator!=(const ConstIterator& constIterator) const;
    const T& operator*() const;

private:
    const Node *m_currentNodePtr;
};


template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    m_currentNodePtr=m_currentNodePtr->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    Queue<T>::ConstIterator tmp=*this;
    ++*this;
    return tmp;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator)const
{
    return !(m_currentNodePtr==constIterator.m_currentNodePtr);
}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    return m_currentNodePtr->m_nodeValue;
}

//----------------------------------------trasform function-------------------------------------
template<class S,class Function>
void transform(Queue<S>& queue, Function function)
{
    for (typename Queue<S>::Iterator it = queue.begin(); it != queue.end(); ++it)
    {
        function(*it);
    }
}
//-----------------------------------------filter function--------------------------------------
template <class T, class Function>
Queue<T> filter(Queue<T>& queue, Function function)
{
    Queue<T> resQueue;
    for(T& element: queue)
    {
        if(function(element))
        {
            resQueue.pushBack(element);
        }
    }
    return resQueue;
}
#endif //ASSIGNMENT3_QUEUE_H
