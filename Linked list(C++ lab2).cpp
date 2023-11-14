// Linked list(C++ lab2).cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
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
    LinkedList<int> result;
    int carry = 0;
    int i = a.get_size() - 1;
    int j = b.get_size() - 1;
    while (i >= 0 || j >= 0 || carry)
    {
        int digit1 = i >= 0 ? a[i] : 0;
        int digit2 = j >= 0 ? b[j] : 0;
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.push_head(sum % 10);
        if (i >= 0) --i;
        if (j >= 0) --j;

        
    }
    return result;
}

template <typename T>
LinkedList<T> multiply(const LinkedList<T>& a, const LinkedList<T>& b) {
    LinkedList<int> result;
    if (a[0] == 0 || b[0] == 0) 
    {
        result.push_head(0);
        return result;
    }
    // Умножение каждой цифры из a на каждую цифру из b
    for (int i = a.get_size() - 1; i >= 0; --i) {
        int carry = 0;
        LinkedList<T> temp_result;  // Временный список для хранения промежуточных результатов

        // Добавляем нули в конец в зависимости от позиции цифры в a
        for (int k = 0; k < a.get_size() - 1 - i; ++k) {
            temp_result.push_tail(0);
        }

        for (int j = b.get_size() - 1; j >= 0; --j) {
            // Умножаем текущие цифры и прибавляем к промежуточному результату
            T digit1 = a[i];
            T digit2 = b[j];
            T product = digit1 * digit2 + carry;
            carry = product / 10;
            temp_result.push_head(product % 10);
        }

        // Добавляем последний перенос, если есть
        if (carry > 0) {
            temp_result.push_head(carry);
        }

        // Складываем текущий промежуточный результат с общим результатом
        result = add(result, temp_result);
    }

    return result;
}


int main() {

    //Operator =
    cout << "operator =" << endl;
    LinkedList<int> a, b;
    a.push_tail(1);
    a.push_tail(2);
    b = a;
    cout << "a: " << a << endl << "b: " << b << endl;

    //push_tail
    cout << endl << "push_tail" << endl;
    LinkedList<int> c, d;
    c.push_tail(5);
    c.push_tail(6);
    d.push_tail(3);
    d.push_tail(4);
    cout << "d: " << d << endl << "c: " << c << endl;
    d.push_tail(c);
    cout << "d.push_tail(c) = " << d << endl;

    //push_head
    cout << endl << "push_head" << endl;
    LinkedList<int> f, g;
    f.push_head(4);
    f.push_head(3);
    g.push_head(2);
    g.push_head(1);
    cout << "f: " << f << endl << "g: " << g << endl;
    f.push_head(g);
    cout << "f.push_head(g) = " << f << endl;

    //pop_head
    cout << endl << "pop_head" << endl;
    LinkedList<int>i;
    i.push_tail(666);
    i.push_tail(1);
    i.push_tail(2);
    cout << "i: " << i << endl;
    i.pop_head();
    cout << "i: " << i << endl;

    //pop_tail
    cout << endl << "pop_tail" << endl;
    LinkedList<int>j;
    j.push_tail(1);
    j.push_tail(2);
    j.push_tail(666);
    cout << "j: " << j << endl;
    j.pop_tail();
    cout << "j: " << j << endl;

    //delete_node
    cout << endl << "delete_node" << endl;
    LinkedList<int>k;
    k.push_tail(1);
    k.push_tail(3);
    k.push_tail(2);
    k.push_tail(3);
    k.push_tail(3);
    cout << "k: " << k << endl;
    k.delete_node(3);
    cout << "k.delete_node(3) = " << k << endl;

    //operator[]
    cout << endl << "operator[]" << endl;
    LinkedList<int>l;
    l.push_tail(1);
    l.push_tail(2);
    l.push_tail(3);
    l.push_tail(4);
    l.push_tail(5);
    cout << "l[2] = " << l[2] << endl;
    l[2] = 2;
    cout << "l[2] = " << l[2] << endl;
    //add
    cout << endl << "sum of lists" << endl;
    LinkedList<int>num1, num2, sum;
    num1.push_tail(1);
    num1.push_tail(9);
    num1.push_tail(7);
    num2.push_tail(8);
    num2.push_tail(0);
    num2.push_tail(3);
    cout << num1 << " + " << num2 << " = " << add(num1, num2) << endl;
    //multiply
    cout << endl << "multiply of lists" << endl;
    LinkedList<int>num3, num4;
    num3.push_tail(1);
    num3.push_tail(2);
    num3.push_tail(5);
    num4.push_tail(8);
    cout << num3 << " * " << num4 << " = " << multiply(num3, num4) << endl;
}