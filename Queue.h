//
// Created by layan & omar on 23/05/2022.
//

#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H

#include<iostream>

template <class T>
class Queue
{

public:
    Queue():m_frontNode(nullptr), m_backNode(nullptr), m_queueSize(0){}
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    ~Queue();
    
    void pushBack(const T& newNodeData);
    T& front() const;
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin()
    {
        return Iterator(m_frontNode);
    }
    Iterator end()
    {
        return Iterator(nullptr);
    }

    class ConstIterator;
    ConstIterator begin() const
    {
        return ConstIterator(m_frontNode);
    }
    ConstIterator end() const
    {
        return ConstIterator(nullptr);
    }

    class EmptyQueue{};

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
        throw;
    }
    ptr->m_nextNode=m_backNode;
}


 template<class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& queue)
{
    if(&queue == this)
    {
        return *this;
    }
    Node* tempFront=new Node(queue.m_frontNode->m_nodeValue);
    Node* temp=tempFront;
    try
    {
        Queue<T>::ConstIterator it = queue.begin();
        ++it;
        for (; it != queue.end(); ++it)
        {
            temp->m_nextNode = new Node(*it);
            temp=temp->m_nextNode;
        }
    }
    catch(const std::bad_alloc&)
    {
        while(tempFront!= nullptr)
        {
            Node* tmp = tempFront;
            tempFront = tempFront->m_nextNode;
            delete tmp;
        }
        throw;
    }
    while(m_frontNode!= nullptr)
    {
        Node* tmp = m_frontNode;
        m_frontNode = m_frontNode->m_nextNode;
        delete tmp;
    }
    m_backNode = temp;
    m_frontNode=tempFront;
    m_queueSize = queue.m_queueSize;
    return *this;
}




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


template <class T>
T& Queue<T>::front() const
{
    if(m_queueSize<=0)
    {
        throw EmptyQueue();
    }
    return this->m_frontNode->m_nodeValue;
}


template <class T>
void Queue<T>::popFront()
{
    if(m_queueSize<=0)
    {
        throw EmptyQueue();
    }
    if(m_frontNode==m_backNode)
    {
        delete m_frontNode;
        m_frontNode = nullptr;
        m_backNode = nullptr;
    }
    else
    {
        Node *target=m_frontNode;
        m_frontNode=m_frontNode->m_nextNode;
        delete target;
    }
    --m_queueSize;
}


template <class T>
int Queue<T>::size() const
{
    return this->m_queueSize;
}



template <class T>
class Queue<T>::Iterator
{
public:
    explicit Iterator(Node* node):m_currentNodePtr(node){};
    Iterator(const Iterator&)=default;
    ~Iterator()=default;
    Iterator& operator=(const Iterator&)=default;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator!=(const Iterator& iterator)const;
    T& operator*() const;

    class InvalidOperation{};

private:
    Node *m_currentNodePtr;
};

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    if(m_currentNodePtr == nullptr)
    {
        throw InvalidOperation();
    }
    m_currentNodePtr = m_currentNodePtr->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::Iterator::operator++(int)
{
    if(m_currentNodePtr == nullptr)
    {
        throw InvalidOperation();
    }
    Queue<T>::Iterator tmp=*this;
    ++*this;
    return tmp;
}

template <class T>
bool Queue<T>::Iterator::operator!=(const Iterator& iterator)const
{
    return !(m_currentNodePtr==iterator.m_currentNodePtr);
}

template <class T>
T& Queue<T>::Iterator::operator*() const
{
    if(m_currentNodePtr == nullptr)
    {
        throw InvalidOperation();
    }
    return m_currentNodePtr->m_nodeValue;
}




template <class T>
class Queue<T>::ConstIterator
{
public:
    ConstIterator(const Node *node):m_currentNodePtrConst(node){};
    ConstIterator(const ConstIterator&)=default;
    ~ConstIterator()=default;
    ConstIterator& operator=(const ConstIterator&)=default;
    ConstIterator& operator++();
    ConstIterator operator++(int);
    bool operator!=(const ConstIterator& constIterator) const;
    const T& operator*() const;

    class InvalidOperation{};

private:
    const Node *m_currentNodePtrConst;
};


template <class T>
typename Queue<T>::ConstIterator& Queue<T>::ConstIterator::operator++()
{
    if(m_currentNodePtrConst== nullptr)
    {
        throw InvalidOperation();
    }
    m_currentNodePtrConst=m_currentNodePtrConst->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::ConstIterator Queue<T>::ConstIterator::operator++(int)
{
    if(m_currentNodePtrConst== nullptr)
    {
        throw InvalidOperation();
    }
    Queue<T>::ConstIterator tmp=*this;
    ++*this;
    return tmp;
}

template <class T>
bool Queue<T>::ConstIterator::operator!=(const ConstIterator& constIterator)const
{
    return !(m_currentNodePtrConst==constIterator.m_currentNodePtrConst);
}

template <class T>
const T& Queue<T>::ConstIterator::operator*() const
{
    if(m_currentNodePtrConst== nullptr)
    {
        throw InvalidOperation();
    }
    return m_currentNodePtrConst->m_nodeValue;
}


template<class S,class Function>
void transform(Queue<S>& queue, Function function)
{
    for (typename Queue<S>::Iterator it = queue.begin(); it != queue.end(); ++it)
    {
        function(*it);
    }
}


template <class T, class Function>
Queue<T> filter(const Queue<T>& queue, Function function)
{
    Queue<T> resQueue;
    for(const T& element: queue)
    {
        if(function(element))
        {
            resQueue.pushBack(element);
        }
    }
    return resQueue;
}
#endif //ASSIGNMENT3_QUEUE_H
