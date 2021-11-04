#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "NodeCenter.h"
using namespace std;

template <class T>
class heap {
    bool heap_type; // 1 -> max; 0 -> min;

public:
    heap(int type = 0) {
        heap_type = type;
    }

    template<class S>
    bool parent_check(S parent, S child) {
        if (heap_type) return parent.getFrequency() < child.getFrequency();
        else return parent.getFrequency() > child.getFrequency();
    }

    void up_heapify(vector<T>& a, int i) {
        while (i > 1 && parent_check<T>(a[i >> 1], a[i])) {
            swap(a[i >> 1], a[i]);
            i >>= 1;
        }
    }

    void down_heapify(vector<T>& a, int i, int n) {
        int l = i << 1, r = l + 1, p = i;

        if ((l <= n) && parent_check(a[p], a[l])) p = l;
        if ((r <= n) && parent_check(a[p], a[r])) p = r;

        if (p != i) {
            swap(a[i], a[p]);
            down_heapify(a, p, n);
        }
    }

    void build_heap(vector<T>& a) {
        int n = a.size() - 1;
        for (int i = n << 1; i >= 1; i--)
            down_heapify(a, i, n);
    }

    void heap_sort(vector<int>& a) {
        for (int i = a.size() - 1; i > 1; i--) {
            swap(a[1], a[i]);
            down_heapify(a, 1, i - 1);
        }
    }
};

template <class T>
class prio_queue {
    int pq_type; // 1 -> max; 0 -> min;
    vector<T> h;
    heap<T> hp;
    int totalNodes;

public:
    prio_queue(int type = 0) : pq_type(type) { }

    void setHeap(vector<T>& list) {
        hp.build_heap(list);
        h = list;

        totalNodes = size();
        fixAllPositions();
    }

    const vector<T>& getHeap(void) {
        return h;
    }

    int size(void)
    {
        return h.size() - 1;
    }

    bool empty(void)
    {
        return size() == 0;
    }

    T top(void) // heap max or min
    {
        return h[1];
    }

    void push(T val) // heap insertion
    {
        h.emplace_back(val);
        hp.up_heapify(h, size());
        fixAllPositions();
    }

    void pop(void) // heap extract max or min
    {
        h[1] = h.back();
        h.pop_back();
        hp.down_heapify(h, 1, size());
    }

    void fixAllPositions(void) {
        float coef = 0;

        for (int i = 1; i < h.size(); i++) {
            h[i].fixNodePosition(coef, totalNodes);
            coef += h[i].getNodeList().size();
        }
    }

    void drawTo(sf::RenderWindow& window) {
        for (int i = 1; i < h.size(); i++) {
            h[i].drawTo(window);
        }
    }
};