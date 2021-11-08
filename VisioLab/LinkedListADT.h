#pragma once
#include <SFML/Graphics.hpp>
#include <string>
template<class T>
class LinkedListADT {
    T* head, * tail;
    int length, limit;

public:
    LinkedListADT(int limit = 7) : head(NULL), tail(NULL), length(0) {
        this->limit = limit;
    }
    ~LinkedListADT() {
        clear();
    }
    void clear(void) {
        T* temp;
        while (head) {
            temp = head;
            head = head->getNext();
            delete temp;
        }
        reset();
    }
    int size(void) {
        return length;
    }
    void reset(void) {
        head = tail = NULL;
    }
    bool empty(void) {
        return (!head && !tail);
    }
    bool inLimit(void) {
        return length <= limit;
    }
    bool isFull(void) {
        return length >= limit;
    }
    T* top(void) {
        return head;
    }
    T* back(void) {
        return tail;
    }
    void pushFront(T* key) {
        if (!inLimit()) return;
        T* temp = key;
        if (head) head->setPrev(temp);
        else tail = temp;
        head = temp;
        length++;
    }
    bool popFront(void) {
        if (empty())
            return 0;

        T* temp = head;
        head = head->getNext();
        if (head) head->setPrev(NULL);
        else tail = NULL;

        delete temp;
        length--;
        return 1;
    }
    bool popBack(void)
    {
        if (head)
        {
            if (head->getNext())
            {
                T* temp2 = tail;
                tail = tail->getPrev();
                tail->setNext(NULL);
                delete temp2;
                length--;
                return 1;
            }
            else
                clear();
        }
    }
    void drawTo(sf::RenderWindow& window) {
        T* temp = head;
        while (temp) {
            temp->drawTo(window);
            temp = temp->getNext();
        }
    }
};