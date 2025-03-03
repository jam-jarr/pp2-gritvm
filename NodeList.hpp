//
// Created by admin on 2/1/25.
// Name: Huy Bui U82390903
// Name: Jamie Giarratana U81686143
// Description Header for the Doubly Linked List
#ifndef INTDLIST_H
#define INTDLIST_H
#include <iostream>
#include <string>
#include "DNode.hpp"
#include "NodeList.hpp"
using namespace std;

template <typename T>
class NodeList;

template<typename T>
class DNode{
public:
    DNode<T>();
private:
    DNode(const T &value);

    T val;
    DNode* prev;
    DNode* next;
    friend class Iterator;
    friend class NodeList<T>;
};
template<typename T>
DNode<T>::DNode(){
    val = nullptr;
    prev = nullptr;
    next = nullptr;
}
template<typename T>
DNode<T>::DNode(const T& value){
    val = value;
    prev = nullptr;
    next = nullptr;
}

template <typename T>
class NodeList {
public:
    class Iterator {
    public:
        Iterator();
        T& operator*();
        bool operator==(const Iterator& p) const;
        bool operator!=(const Iterator& p) const;
        Iterator& operator++();
        Iterator& operator--();
    private:
        DNode<T>* v;
        explicit Iterator(DNode<T>* u);
        friend class NodeList<T>;
    };
    NodeList();
    ~NodeList();
    NodeList<T>::Iterator begin() const;
    NodeList<T>::Iterator end() const;
    void clear();
    void push_front(T v);
    void push_back(T v);
    string remove_front();
    string remove_back();
    void printAll() const;
private:
    bool isEmpty() const;
    DNode<T>* head;
    DNode<T>* tail;
};

template<typename T>
NodeList<T>::Iterator::Iterator() {
    v = nullptr;
}

template<typename T>
NodeList<T>::Iterator::Iterator(DNode<T> *u) {
    v = u;
}
template<typename T>
T& NodeList<T>::Iterator::operator*(){
    return v->val;
}
template<typename T>
bool NodeList<T>::Iterator::operator==(const Iterator& p) const{
    return v == p.v;
}
template<typename T>
bool NodeList<T>::Iterator::operator!=(const Iterator& p) const{
    return v != p.v;
}
template<typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator++(){
    if (v && v->next) { // Check if v is valid and has a next node
        v = v->next;
    }
    v = v->next;
    return *this;
}
template<typename T>
typename NodeList<T>::Iterator& NodeList<T>::Iterator::operator--(){
    if (v && v->prev) { // Check if v is valid and has a previous node
        v = v->prev;
    }
    v = v->prev;
    return *this;
}

template <typename T>
NodeList<T>::NodeList()
{
    head = new DNode<T>;
    tail = new DNode<T>;
    head->next = tail;
    tail->prev = head;
    // Number of Nodes in the list
}
template <typename T>
NodeList<T>::~NodeList()
{
    while (!isEmpty())
    {
        remove_front();
    }
    delete head;
    delete tail;
}
template<typename T>
typename NodeList<T>::Iterator NodeList<T>::begin() const {
    return Iterator(head->next);
}
template<typename T>
typename NodeList<T>::Iterator  NodeList<T>::end() const {
    return Iterator(tail->prev);
}
template<typename T>
void NodeList<T>::clear(){
    while (!isEmpty()) {
        remove_front();
    }
}
/// Check if Linked List is empty
/// \return true if empty, false if not
template<typename T>
bool NodeList<T>::isEmpty() const
{
    return head->next == tail;
}
/// Add value to head of the Linked List
/// \param v value to be added
template<typename T>
void NodeList<T>::push_front(T v)
{
    DNode<T> *node = new DNode<T>(v);
    DNode<T> *temp = head->next;
    head->next = node;
    node->next = temp;
    temp->prev = node;
    node->prev = head;
}
/// Add value to tail of the Linked List
/// \param v value to be added
template<typename T>
void NodeList<T>::push_back(T v)
{
    DNode<T> *node = new DNode<T>(v);
    DNode<T> *temp = tail->prev;
    tail->prev = node;
    node->prev = temp;
    temp->next = node;
    node->next = tail;
}

/// Remove value from head of the Linked List
/// \param v value to be removed
template<typename T>
string NodeList<T>::remove_front()
{
    if (isEmpty())
    {
        throw length_error("Linked List is empty");
    }
    DNode<T> *temp = head->next;
    string tempVal = temp->val;
    head->next = temp->next;
    temp->next->prev = head;
    delete temp;
    return tempVal;
}
/// Remove value from tail of the Linked List
/// \param v value to be removed
template<typename T>
string NodeList<T>::remove_back()
{
    if (isEmpty())
    {
        throw length_error("Linked List is empty");
    }
    DNode<T> *temp = tail->prev;
    string tempVal = temp->val;
    tail->prev = temp->prev;
    temp->prev->next = tail;
    delete temp;
    return tempVal;
}
/// Print all values in the Linked List
template<typename T>
void NodeList<T>::printAll() const
{
    for (DNode<T> *curr = head->next; curr != tail; curr = curr->next)
    {
        cout << curr->val << " ";
    }
    cout << endl;
}

#endif //COP4530_INTDLIST_H
