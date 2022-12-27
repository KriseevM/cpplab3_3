//
// Created by k17 on 26.12.2022.
//

#ifndef CPPLAB3_3_TSTACK_H
#define CPPLAB3_3_TSTACK_H

template<class T>
class TStack {
private:
    size_t stackSize{};
    size_t nextIndex = 0;
    T *elements;
public:
    explicit TStack(size_t size = 50) : stackSize(size), nextIndex(0), elements(new T[size]){};
    TStack(TStack &&s)  noexcept;
    TStack &operator = (TStack &&s)  noexcept;
    T &Top();
    const T &Top() const;
    void Pop();
    void Push(const T &elem);
    bool isFull();
    bool isEmpty();
    size_t getSize();
    ~TStack();
};

template<class T>
TStack<T>::~TStack() {
    delete[] elements;
}

template<class T>
TStack<T>::TStack(TStack &&s) noexcept : stackSize(s.stackSize), nextIndex(s.nextIndex), elements(s.elements){
    s.elements = nullptr;
}

template<class T>
TStack<T>& TStack<T>::operator=(TStack &&s) noexcept {
    if(&s == this) return *this;
    elements = s.elements;
    s.elements = nullptr;
    nextIndex = s.nextIndex;
    stackSize = s.stackSize;
    return *this;
}

template<class T>
T &TStack<T>::Top() {
    if(isEmpty())
        throw std::out_of_range("Stack is empty");
    return elements[nextIndex-1];
}

template<class T>
const T &TStack<T>::Top() const {
    if(isEmpty())
        throw std::out_of_range("Stack is empty");
    return elements[nextIndex-1];
}

template<class T>
void TStack<T>::Pop() {
    if(isEmpty())
        throw std::out_of_range("Stack is empty");
    nextIndex--;
}

template<class T>
bool TStack<T>::isFull() {
    return nextIndex == stackSize;
}

template<class T>
void TStack<T>::Push(const T &elem) {
    if(isFull())
        throw std::out_of_range("Stack is full");
    elements[nextIndex] = elem;
    nextIndex++;
}

template<class T>
bool TStack<T>::isEmpty() {
    return nextIndex == 0;
}

template<class T>
size_t TStack<T>::getSize() {
    return nextIndex;
}

#endif //CPPLAB3_3_TSTACK_H
