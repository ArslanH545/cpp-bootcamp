#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>
template<typename T> 
class List {
    private:
        struct Node
        {
            T data;
            Node* next;
            Node(const T& data) : data(data), next(nullptr) {}
        };
        size_t size;
        Node* head;
        Node* tail;
        void clear();
    public:
        List();
        ~List();
        List(const List<T>& other);
        size_t getSize() const;
        void front_push(const T& value);
        void back_push(const T& value);
        void pop_front();
        void pop_back();
        void insert(const T& value, const size_t pos);
        size_t search(const T& value) const;
        bool empty() const;
        void printLL();
};

#endif


template<typename T> 
void List<T>::clear() {
    while(head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

// Deffination of methods. 
template<typename T>
List<T>::List() : size(0), head(nullptr), tail(nullptr) {}

// Destructor
template<typename T>
List<T>::~List() {
    if (!empty()){
        clear();
    }
}

// deep copy ctor 
template<typename T>
List<T>::List(const List<T>& other): size(0), head(nullptr), tail(nullptr) {
    Node* cur = other.head;
    while(cur != nullptr){
        back_push(cur->data);
        cur = cur->next;
    }
}

template<typename T>
void List<T>::front_push(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    size++;
}


template<typename T> 
void List<T>::back_push(const T& value){
    Node* newNode = new Node(value);
    if (head == nullptr){
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

template <typename T> 
void List<T>::pop_front(){
    if (head == nullptr){
        return;
    } 
    Node* temp = head;
    head = head->next;
    temp->next =  nullptr;
    delete temp;
    size--;
}

template<typename T>
void List<T>::pop_back() {
    if (head == nullptr){
        return;
    }
    Node* temp = head;
    while (temp->next != tail){
        temp = temp->next;
    }    
    temp->next = nullptr;
    delete tail;
    tail = temp;
    size--;
}

template <typename T> 
void List<T>::insert(const T& value, const size_t pos) {
    if (pos > size) {
        return;
    } 
    if (pos == 0) {
        front_push(value);
    }

    Node* temp = head; 
    for (size_t i = 0; i < size - 1; i++){
        if (temp == nullptr){
            return;
        }
        temp = temp->next;
    }
    Node* newNode = new Node(value);
    newNode->next = temp->next;
    temp->next = newNode;
    size++;
}

template<typename T>
size_t List<T>::search(const T& value) const{
    Node* temp = head;
    size_t idx;
    while(temp != nullptr){
        if (temp->date == value) {
            return idx;
        }
        temp = temp->next;
        idx++;
    }
    return idx;
}

template<typename T> 
bool List<T>::empty() const{
    return size == 0;
}

template<typename T>
size_t List<T>::getSize() const{
    return size;
}

template <typename T>
void List<T>::printLL(){
    Node* temp = head;
    while(temp != nullptr) {
        std::cout << temp->data << "->";
        temp = temp->next;
    }
    std::cout << "->NULL\n";
}   