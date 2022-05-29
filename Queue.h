//
// Created by layan on 23/05/2022.
//

#ifndef ASSIGNMENT3_QUEUE_H
#define ASSIGNMENT3_QUEUE_H

template <class T>
class Node{
public:
    T m_nodeValue;
    Node m_nextNode;

    explicit Node(const T& nodeValue):m_nodeValue(nodeValue),m_nextNode(nullptr){};
    ~Node()=default;
    Node(const Node& nodeValue)=delete;
    Node& operator=(const Node& nodeValue)=delete;
};

//typedef int S;
template <class S>
class Queue{
public:
    Queue():m_frontNode(nullptr), m_backNode(nullptr), m_queueSize(0){};
    Queue(const Queue& queue);
    Queue& operator=(const Queue& queue);
    ~Queue();

    void pushBack(const S& newNodeData);
    S& front();
    void popFront();
    int size() const;

    class Iterator;
    Iterator begin();
    Iterator end();

private:
    Node<S> *m_frontNode;
    Node<S> *m_backNode;
    int m_queueSize;
};

template <class S>
Queue<S>::Queue(const Queue<S>& queue):m_frontNode(new Node<S>(queue->m_frontNode)),
                                       m_backNode(new Node<S>(queue.m_backNode)), m_queueSize(queue.m_queueSize)
{
}

template <class S>
class Queue<S>::Iterator
{
private:
    Node<S> *current_node;
public:
    explicit Iterator():
};


#endif //ASSIGNMENT3_QUEUE_H
