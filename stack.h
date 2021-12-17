
#include <iostream>
#include <string>

template<class T>           // CТРУКТУРА ДАННЫХ FIFO (стек)
struct StackUnit
{
    T Data;
    StackUnit* Tail;
};

template<class T>
class Stack     
{
    StackUnit<T>* _head = nullptr;

public:
    T Peek() {      // проверить верхний элемент
        if (_head == nullptr) return NULL;
        return _head->Data;
    }

    T Pop()         // взять верхний элемент
    {
        T data = _head->Data;
        StackUnit<T>* newHead = _head->Tail;
        delete _head;
        _head = newHead;
        return data;
    }

    void Push(T data)       // закинуть верхний элемент стека
    {
        StackUnit<T>* newUnit = new StackUnit<T>;
        newUnit->Data = data;
        newUnit->Tail = _head;
        _head = newUnit;
    }
}