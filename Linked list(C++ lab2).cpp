// Linked list(C++ lab2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <stack>
#include <iostream>
#include<algorithm>
using namespace std;

template<typename T>
class LinkedList
{
private:
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
    void swap(LinkedList<T>& other);
    Node* head;
    int _size;
public:
    LinkedList();
    ~LinkedList();
    friend ostream& operator<<(ostream& os, const LinkedList<T> list)
    {
        for (Node* current = list.head; current != nullptr; current = current->_next)
        {
            os << current->_data << " ";
        }
        return os;
    }

    LinkedList<T>& operator=(LinkedList<T> other);
    void push_back(T data);
    void push_front(T data);
    void pop_front();
    void pop_back();
    void push_back(LinkedList<T>& other);
    void push_front(LinkedList<T>& other);
    LinkedList(const LinkedList<T>& other);
    void delete_node(T data);
    void remove(int index);
    T& operator[](int index);
    friend LinkedList<T>& lucky_numbers(int end);
    friend bool isPrime(int number);
    int get_size()
    {
        return this->_size;
    }
};

template<typename T>
T& LinkedList<T>::operator[](int index)
{
    if (index < 0 || index >= _size)
    {
        throw std::out_of_range("wrong index");
    }
    Node* current = head;
    for (int i = 0; i < index; i++)
    {
        current = current->_next;
    }
    return current->_data;
}


template<typename T>
void LinkedList<T>::remove(int index)
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


template<typename T>
void LinkedList<T>::delete_node(T data)
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

template<typename T>
void LinkedList<T>::push_front(LinkedList<T>& other)
{
    Node* otherCurrent = other.head;
    std::stack<T> tempStack;
    while (otherCurrent != nullptr)
    {
        tempStack.push(otherCurrent->_data);
        otherCurrent = otherCurrent->_next;
    }
    while (!tempStack.empty())
    {
        this->push_front(tempStack.top());
        tempStack.pop();
    }
}


template<typename T>
void LinkedList<T>::push_back(LinkedList<T>& other)
{
    Node* otherCurrent = other.head;
    while (otherCurrent != nullptr)
    {
        this->push_back(otherCurrent->_data);
        otherCurrent = otherCurrent->_next;
    }
}


template<typename T>
void LinkedList<T>::pop_back()
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


template<typename T>
void LinkedList<T>::pop_front()
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


template<typename T>
void LinkedList<T>::push_front(T data)
{
    head = new Node(data, head);
    if (head->_next != nullptr) {
        head->_next->_prev = head;
    }
    _size++;
}


template<typename T>
LinkedList<T>::~LinkedList()
{
    Node* current = head;
    while (current != nullptr)
    {
        Node* nodeToDelete = current;
        current = current->_next;
        delete nodeToDelete;
    }
}

template<typename T>
void LinkedList<T>::push_back(T data)
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

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
{
    this->head = nullptr;
    this->_size = 0;
    Node* tmp = other.head;
    while (tmp != nullptr)
    {
        this->push_back(tmp->_data);
        tmp = tmp->_next;
    }

}

template<typename T>
LinkedList<T>::LinkedList()
{
    head = nullptr;
    _size = 0;
}

template<typename T>
void LinkedList<T>::swap(LinkedList<T>& other)
{
    std::swap(head, other.head);
    std::swap(_size, other._size);
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> other)
{
    if (this == &other)
    {
        return *this;
    }
    swap(other);
    return *this;
}

template <typename T>
LinkedList<T>& lucky_numbers(int end) {
    LinkedList<T> nonLuckyNumbers; 

    for (int i = 1; i <= end; ++i) {
        nonLuckyNumbers.push_back(i);
    }

    int current = 2;
    int count = 1;

    while (current <= end && count <= end) {
        Node* current_node = new Node(nonLuckyNumbers.head);
        Node* prev_node = new Node(, ,nullptr);
        int position = 1;

        while (current_node != nullptr) {
            if (position == current) {
                if (prev_node != nullptr) {
                    prev_node->_next = current_node->_next;
                    if (current_node->_next != nullptr) {
                        current_node->_next->_prev = prev_node;
                    }
                }
                else {
                    nonLuckyNumbers.head = current_node->_next;
                    if (current_node->_next != nullptr) {
                        current_node->_next->_prev = nullptr;
                    }
                }
                current_node = current_node->_next;
            }
            else {
                prev_node = current_node;
                current_node = current_node->_next;
            }
            position++;
        }

        do {
            current++;
        } while (!isPrime(current));

        count++;
    }

    return nonLuckyNumbers;
}

template <typename T>
bool isPrime(int number) {
    if (number <= 1) {
        return false;
    }

    for (int i = 2; i * i <= number; ++i) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

int main() {
    LinkedList<int>list1;
    list1 = lucky_numbers(10);
    for (int i = 0; i < list1.get_size(); ++i) {
        cout << list1[i] << endl;
    }
}




