#pragma once
#include <iostream>

using namespace std;

template <typename T>
class dynamic_array {

public:
	dynamic_array();
	dynamic_array(const dynamic_array<T>& a);
	dynamic_array(size_t size);
	~dynamic_array();
	void replace(size_t pos);
	void resize(size_t size);
	size_t size() const;
	T operator[] (size_t i);
	void print();
	void push_back(T val);

private:
	size_t m_size;
	size_t m_capacity;
	T* m_data;
};

template <typename T>
dynamic_array<T>::dynamic_array() {
	m_size = 1;
	m_capacity = 1;
	m_data = NULL;
}

template <typename T>
dynamic_array<T>::dynamic_array(const dynamic_array<T>& a) {
	m_size = a.m_size;
	m_capacity = m_size;
	m_data = NULL;
	if (m_size != 0) m_data = new T[m_size]; else m_data = 0;
	for (size_t i = 0; i < m_size; ++i) m_data[i] = a.m_data[i];
}

template <typename T>
dynamic_array<T>::dynamic_array(size_t size) {
	m_size = size;
	m_capacity = size;
	if (size != 0) m_data = new T[size]; else m_data = 0;
}

template <typename T>
dynamic_array<T>::~dynamic_array() {
	if (m_data) delete[] m_data;
}

template <typename T>
void dynamic_array<T>::resize(size_t size) {
	if (size > m_capacity) {
		size_t new_capacity = max(size, m_size * 2);
		T* new_data = new T[new_capacity];
		for (size_t i = 0; i < m_size; ++i) new_data[i] = m_data[i];
		delete[] m_data;
		m_data = new_data;
		m_capacity = new_capacity;
	}
	m_size = size;
}

template <typename T>
size_t dynamic_array<T>::size() const{
	return m_size;
}

template <typename T>
T dynamic_array<T>::operator[] (size_t i) {
	return m_data[i];
}

template <typename T>
void dynamic_array<T>::print() {
	for (size_t i = 0; i < m_size; i++) std::cout << m_data[i] << " ";
}

template <typename T>
void dynamic_array<T>::push_back(T val) {
	resize(m_size + 1);
	m_data[m_size - 1] = val;
}

template <typename T>
void dynamic_array<T>::replace(size_t pos) {
	m_size--;
	for (size_t i = pos; i < m_size; i++) m_data[i] = m_data[i + 1];
	resize(m_size);
}
