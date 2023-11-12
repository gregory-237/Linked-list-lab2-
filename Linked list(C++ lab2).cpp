﻿// Linked list(C++ lab2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stack>
#include <iostream>
#include<algorithm>
using namespace std;

template<typename T>
class LinkedList
{
public:
    class Node
    {
    public:
        T _data;
        Node* _next;
        Node* _prev;
        Node(T data = T(), Node* next = nullptr, Node* prev = nullptr)
        {
            this->_data = data;
            this->_next = next;
            this->_prev = prev;
        }
    };
    Node* head;
    int _size;
    
    void swap(LinkedList<T>& other)
    {
        std::swap(head, other.head);
        std::swap(_size, other._size);
    }
public:

    LinkedList()
    {
        head = nullptr;
        _size = 0;
    }

    LinkedList(const LinkedList<T>& other)
    {
        this->head = nullptr;
        this->_size = 0;
        Node* tmp = other.head;
        while (tmp != nullptr)
        {
            this->push_tail(tmp->_data);
            tmp = tmp->_next;
        }
    }

    ~LinkedList()
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* nodeToDelete = current;
            current = current->_next;
            delete nodeToDelete;
        }
    }

    LinkedList<T>& operator=(LinkedList<T> other)
    {
        if (this == &other)
        {
            return *this;
        }
        swap(other);
        return *this;
    }

    void push_tail(T data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
        }
        else
        {
            Node* current = head;
            while (current->_next != nullptr)
            {
                current = current->_next;
            }
            current->_next = new Node(data, nullptr, current);
        }
        _size++;
    }

    void push_tail(LinkedList<T>& other)
    {
        Node* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            this->push_tail(otherCurrent->_data);
            otherCurrent = otherCurrent->_next;
        }
    }

    void push_head(T data)
    {
        head = new Node(data, head);
        if (head->_next != nullptr) {
            head->_next->_prev = head;
        }
        _size++;
    }

    void push_head(LinkedList<T>& other)
    {
        Node* tmp = other.head;
        LinkedList<T> list;

        while (tmp != nullptr)
        {
            list.push_head(tmp->_data);
            tmp = tmp->_next;
        }
        Node* kk = list.head;
        while (kk != nullptr)
        {
            this->push_head(kk->_data);
            kk = kk->_next;
        }
    }

    void pop_head()
    {
        if (head == nullptr)
        {
            throw out_of_range("Cannot pop front from an empty list");
        }
        Node* nodeToDelete = head;
        head = head->_next;
        if (head != nullptr)
        {
            head->_prev = nullptr;
        }
        delete nodeToDelete;
        _size--;
    }

    void pop_tail()
    {
        if (head == nullptr)
        {
            throw out_of_range("Cannot pop back from an empty list");
        }
        Node* current = head;
        while (current->_next != nullptr)
        {
            current = current->_next;
        }
        if (current->_prev != nullptr)
        {
            current->_prev->_next = nullptr;
        }
        else
        {
            head = nullptr;
        }
        delete current;
        _size--;
    }

    void delete_node(T data)
    {
        Node* current = head;
        while (current != nullptr)
        {
            Node* nextNode = current->_next;
            if (current->_data == data) {
                if (current->_prev != nullptr) {
                    current->_prev->_next = current->_next;
                }
                else {
                    head = current->_next;
                }
                if (current->_next != nullptr) {
                    current->_next->_prev = current->_prev;
                }
                delete current;
                _size--;
            }
            current = nextNode;
        }
    }

    void remove(int index)
    {
        if (index < 0 || index >= _size)
        {
            throw out_of_range("wrong index to remove");
        }
        Node* current = head;
        for (int i = 0; i < index; i++)
        {
            current = current->_next;
        }
        if (current->_prev != nullptr)
        {
            current->_prev->_next = current->_next;
        }
        else {
            head = current->_next;
        }
        if (current->_next != nullptr)
        {
            current->_next->_prev = current->_prev;
        }
        delete current;
        _size--;
    }

    T operator[](int index) const
    {
        int count = 0;
        Node* tmp = head;
        while (tmp != nullptr)
        {
            if (count == index)
            {
                return tmp->_data;
            }
            count++;
            tmp = tmp->_next;
        }
        throw out_of_range("wrong index of list");
    }

    T& operator[](int index) 
    {
        int count = 0;
        Node* tmp = head;
        while (tmp != nullptr)
        {
            if (count == index)
            {
                return tmp->_data;
            }
            count++;
            tmp = tmp->_next;
        }
        throw out_of_range("wrong index of list");
    }

    friend ostream& operator<<(ostream& os, const LinkedList<T> list)
    {
        for (Node* current = list.head; current != nullptr; current = current->_next)
        {
            os << current->_data << " ";
        }
        return os;
    }

    int get_size() const
    {
        return _size;
    }

    int& get_size()
    {
        return _size;
    }


};

template <typename T>
LinkedList<T> add(LinkedList<T> a, LinkedList<T> b) {
    LinkedList<int>* result = new LinkedList<int>;
    int carry = 0;
    int i = a.get_size() - 1;
    int j = b.get_size() - 1;
    while (i >= 0 || j >= 0 || carry)
    {
        int digit1 = i >= 0 ? a[i] : 0;
        int digit2 = j >= 0 ? b[j] : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result->push_head(sum % 10);
        if (i >= 0) --i;
        if (j >= 0) --j;

        
    }
    return *result;
}

template <typename T>
long long multiply(LinkedList<T> a, LinkedList<T>b) {
    LinkedList<int>* result = new LinkedList<int>;
    long long N = 1000000007;
    long long num1 = 0, num2 = 0;
    while (a.head || b.head) {
        if (a.head)
        {
            num1 = (((num1) * 10) % N +
                a.head->_data);
            a.head = a.head->_next;
        }

        if (b.head)
        {
            num2 = (((num2) * 10) % N +
                b.head->_data);
            b.head = b.head->_next;
        }

    }
    return (((num1 % N) *
        (num2 % N)) % N);
}






int main() {
    LinkedList<int> a, b, c;
    a.push_tail(7);
    a.push_tail(8);
    b.push_tail(7);
    c = add(a, b);
    cout << c;
    cout << endl;
    cout << multiply(a, b);

}




