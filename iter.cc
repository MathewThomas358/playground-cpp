#include <iostream>
#include <memory>

using std::shared_ptr;

template <typename T>
struct Node {

    T data;
    shared_ptr<Node<T>> next;
    Node(T val): data(val), next(nullptr) {}
};

template <typename T>
class Iterator {

   private:

    shared_ptr<Node<T>> current;

   public:

    Iterator(shared_ptr<Node<T>> start) : current(std::move(start)) {}//, isEnd(false) {}

    T operator*();
    Iterator<T>& operator++();
    bool operator!=(const Iterator<T>& other);
};

template <typename T>
class LinkedList {

   private:
    shared_ptr<Node<T>> head;
    shared_ptr<Node<T>> last;

   public:
    LinkedList();
    void add(T data);
    Iterator<T> begin();
    Iterator<T> end();
};

template <typename T>
LinkedList<T>::LinkedList() {

    head = nullptr;
    last = nullptr;
}

template <typename T>
void LinkedList<T>::add(T data) {

    if(head == nullptr) {

        head = std::make_shared<Node<T>>(data);
        last = head;
    } else {

        last->next = std::make_shared<Node<T>>(data);
        last = last->next;
    }
}

template <typename T>
Iterator<T> LinkedList<T>::begin() {

    return Iterator(head);
}

template <typename T>
Iterator<T> LinkedList<T>::end() {

    return Iterator<T>(nullptr);
}

template <typename T>
T Iterator<T>::operator*() {

    return current->data;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {

    current = current->next;
    return *this;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator& other) {

    return current != other.current;
}


int main(void) {

    LinkedList<std::string> ll;

    ll.add("abc");
    ll.add("fcb");
    ll.add("rma");

    for(auto it = ll.begin(); it != ll.end(); ++it) {
        std::cout << *it << " ";
    }

    return 0;
}