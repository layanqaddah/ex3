
//
// Created by layan on 23/05/2022.
//

#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H

//typedef int S;
template <class T>
class Queue
{
public:
    Queue():m_frontNode(nullptr), m_backNode(nullptr), m_queueSize(0){};
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    ~Queue();

    void pushBack(const T& newNodeData);
    T& front();
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin()
    {
        return Iterator(m_frontNode);
    };
    Iterator end()
    {
        return Iterator(nullptr);
    };

private:
    class Node{
    public:
        T m_nodeValue;
        Node *m_nextNode;

        explicit Node(const T& nodeValue):m_nodeValue(nodeValue),m_nextNode(nullptr){};
        ~Node()=default;
        Node(const Node& nodeValue)=delete;
        Node& operator=(const Node& nodeValue)=delete;
    };

    Node *m_frontNode;
    Node *m_backNode;
    int m_queueSize;
};
template <class T>
Queue<T>::Queue(const Queue<T>& queue):m_frontNode(new Node(queue.m_frontNode->m_nodeValue)),
          m_backNode(new Node(queue.m_backNode->m_nodeValue)), m_queueSize(queue.m_queueSize)
{
    Node* ptr=m_frontNode;
    for(T& elem :queue)
    {
        if(elem!=queue.m_frontNode && elem!=queue.m_backNode)
        {
            Node *newNodePtr = new Node(*elem);
            ptr->m_nextNode = newNodePtr;
            ptr = newNodePtr;
        }
    }
    ptr->m_nextNode=m_backNode;
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
    m_backNode->m_nextNode=newNodePtr;
    m_backNode=newNodePtr;
    m_queueSize++;
}



//----------------------------------------------------------------------------------------------
template <class T>
class Queue<T>::Iterator
{
private:
    Node *current_node;
public:
    Iterator():current_node(nullptr){};
    ~Iterator()=default;
    Iterator(const Iterator&)=delete;
    Iterator operator=(const Iterator&)=delete;
    Iterator& operator++();
    Iterator& operator++(int);
    bool operator!=(const Iterator& iterator)const;
    T& operator*();

};

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++()
{
    current_node = current_node->m_nextNode;
    return *this;
}

template <class T>
typename Queue<T>::Iterator& Queue<T>::Iterator::operator++(int)
{
    Queue<T>::Iterator *tmp=this;
    ++*this;
    return tmp;
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

#endif //ASSIGNMENT3_QUEUE_H
