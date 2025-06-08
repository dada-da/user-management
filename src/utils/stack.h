//
// Created by Da on 7/6/25.
//

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <stdexcept>

template<typename T>
class Node {
public:
    T data;
    Node *next;

    explicit Node(T newData) {
        this->data = newData;
        this->next = nullptr;
    }
};

template<typename T>
class Stack {
    Node<T> *head;

public:
    Stack() {
        this->head = nullptr;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return this->head == nullptr;
    }

    void push(T newData) {
        auto *newNode = new Node<T>(newData);

        if (!newNode) {
            throw std::runtime_error("Stack overflow");
        }

        newNode->next = head;
        head = newNode;
    }

    void pop() {
        if (this->isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        Node<T> *temp = head;
        head = head->next;
        delete temp;
    }

    Node<T> *peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }

        return head;
    }

    Node<T> *getTop() const {
        return head;
    }
};


#endif //STACK_H
