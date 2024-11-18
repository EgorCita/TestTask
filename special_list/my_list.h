#pragma once

#include<fstream>
#include<iostream>
#include "node.h"

using namespace std;

template<typename T>
class MyList
{
    Node<T> * fict_;
public:
	MyList()
	{
		fict_ = static_cast<Node<T> *>(malloc(sizeof(Node<T>)));
		fict_->next = fict_;
	}

	void push_front(T value, int type = 0)
	{
		if (fict_->next == fict_)
		{
			fict_->next = new Node<T>{ fict_, value, 1};
		}
        else if (type && fict_->next->key == value)
        {
            fict_->next->inc();
        }
		else
		{
            Node<T>* temp = new Node<T>{ fict_->next, value, 1};
			fict_->next = temp;
		}
	}
	
	void print()
	{
        Node<T>* head = fict_->next;
		while (head != fict_)
		{
			cout << *head << "\n";
			head = head->next;
		}
		cout << "\n";
	}

    Node<T>* first()
    {
        return fict_->next;
    }

    Node<T>* end()
    {
        return fict_;
    }

    void sort()
    {
        fict_->next = merge_sort(fict_->next, fict_);
    }
    
    void write_file(string filename)
    {
        ofstream fout(filename);

        if (!fout.is_open()) {
            throw runtime_error("Ошибка: невозможно открыть файл " + filename);
        }

        Node<T>* head = fict_->next;
        while (head != fict_)
        {
            fout << *head << "\n";
            head = head->next;
        }
    }

    ~MyList()
    {
        while (fict_->next != fict_)
        {
            Node<T>* temp = fict_->next;
            fict_->next = fict_->next->next;
            delete temp;
        }
        free(fict_);
    }
};

template <typename T>
void split(Node<T>* head, Node<T>** a, Node<T>** b, Node<T>* end) {
    if (head == end || head->next == end) {
        *a = head;
        *b = end;
        return;
    }

    Node<T>* slow = head;
    Node<T>* fast = head->next;

    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *a = head;
    *b = slow->next;
    slow->next = end;
}

template <typename T>
Node<T>* merge(Node<T>* a, Node<T>* b, Node<T>* end) {
    if (a == end)
        return b;
    if (b == end)
        return a;

    Node<T>* result;
    if (*a < *b)
    {
        result = a;
        a = a->next;
    }
    else
    {
        result = b;
        b = b->next;
    }
    Node<T>* temp = result;

    /*if (*a < *b) {
        result = a;
        result->next = merge(a->next, b, end);
    }
    else {
        result = b;
        result->next = merge(a, b->next, end);
    }*/

    while (a != end && b != end)
    {
        if (*a < *b) {
            temp->next = a;
            temp = temp->next;
            a = a->next;
        }
        else {
            temp->next = b;
            temp = temp->next;
            b = b->next;
        }
    }

    while (a != end)
    {
        temp->next = a;
        temp = temp->next;
        a = a->next;
    }

    while (b != end)
    {
        temp->next = b;
        temp = temp->next;
        b = b->next;
    }

    return result;
}

template <typename T>
Node<T>* merge_sort(Node<T>* head, Node<T>* end) {
    if (head == end || head->next == end)
        return head;

    Node<T>* a;
    Node<T>* b;

    split(head, &a, &b, end);

    a = merge_sort(a, end);
    b = merge_sort(b, end);

    return merge(a, b, end);
}