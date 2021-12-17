#pragma once
#include <iostream>
#include "spisok.h"

template <typename T>
class stacks : public list<T> {

public:
	stacks();
	~stacks();
	bool notempty();
	T top();
	void push(T val);
	void pop();

private:
	list<T>* newstack;
};

template <typename T>
stacks<T>::stacks() {
	newstack = new list<T>;
}

template <typename T>
stacks<T>::~stacks() {
	delete newstack;
}

template <typename T>
bool stacks <T>::notempty() {
	return newstack->head;
}

template <typename T>
T stacks<T>::top() {
	//if (newstack->head == nullptr) return NULL;
	return newstack->head->val;
}

template <typename T>
void stacks<T>::push(T val) {
	newstack->addnode(val);
}

template <typename T>
void stacks<T>::pop() {
	if (newstack->head) newstack->deletenode();
}