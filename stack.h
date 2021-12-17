
#include <iostream>
#include <string>

template<class T>
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
    T Peek() {
        if (_head == nullptr) return NULL;
        return _head->Data;
    }

    T Pop()
    {
        T data = _head->Data;
        StackUnit<T>* newHead = _head->Tail;
        delete _head;
        _head = newHead;
        return data;
    }

    void Push(T data)
    {
        StackUnit<T>* newUnit = new StackUnit<T>;
        newUnit->Data = data;
        newUnit->Tail = _head;
        _head = newUnit;
    }
}