#pragma once

#include <iostream>

using namespace std;

template <typename T>
struct Node {
	Node* next;
	T key;
    int count = 1;
    void inc()
    {
        ++count;
    }
    friend bool operator <(const Node<T>& l, const Node<T>& r)
    {
        return (l.count == r.count ? l.key < r.key : l.count > r.count);
    }
    friend ostream& operator <<(ostream& fout, const Node<T>& word)
    {
        return fout << word.key << " " << word.count;
    }
};