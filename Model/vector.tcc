#ifndef VECTOR_TCC
#define VECTOR_TCC

#include <stdexcept>
#include "vector.h"
#include <algorithm>

template <class T>
void vector<T>::extend() {
    T* temp = new T[_capacity == 0 ? 1 : _capacity * 2];
    for (unsigned i = 0; i < _size; ++i)
        temp[i] = data[i];
    _capacity = _capacity == 0 ? 1 : _capacity * 2;
    delete[] data;
    data = temp;
}

template <class T>
vector<T>::vector(unsigned size, const T& init) : _size(size) {
    if (_size != 0) {
        _capacity = 1;
        while (_capacity < _size)
            _capacity *= 2;

        data = new T[_capacity];
        for (unsigned i = 0; i < _size; ++i)
            data[i] = init;
    }
    else {
        _capacity = 0;
        data = nullptr;
    }
}

template <class T>
vector<T>::vector(const_iterator b, const_iterator e) : _size(e - b) {
    if (_size != 0) {
        _capacity = 1;
        while (_capacity < _size)
            _capacity *= 2;

        data = new T[_capacity];
        for (unsigned i = 0; i < _size; ++i)
            data[i] = *(b + i);
    }
    else {
        _capacity = 0;
        data = nullptr;
    }
}

template <class T>
vector<T>::vector(std::initializer_list<T> init) : _size(init.end() - init.begin()) {
    if (_size != 0) {
        _capacity = 1;
        while (_capacity < _size)
            _capacity *= 2;

        data = new T[_capacity];
        for (unsigned i = 0; i < _size; ++i)
            data[i] = *(init.begin() + i);
    }
    else {
        _capacity = 0;
        data = nullptr;
    }
}

template <class T>
vector<T>::vector(const vector& v) :
    _size(v._size), _capacity(v._capacity), data(_size == 0 ? nullptr : new T[_capacity]) {
    for (unsigned i = 0; i < _size; ++i)
        data[i] = v.data[i];
}

template <class T>
vector<T>::~vector() { delete[] data; }

template <class T>
vector<T>& vector<T>::operator=(const vector& v) {
    if (&v != this) {
        _size = v._size;
        _capacity = v._capacity;
        delete[] data;
        data = v.data == nullptr ? nullptr : new T[_capacity];

        for (unsigned i = 0; i < _size; ++i)
            data[i] = v.data[i];
    }
    return *this;
}

template <class T>
bool vector<T>::empty() const { return _size == 0; }

template <class T>
unsigned vector<T>::size() const { return _size; }

template <class T>
unsigned vector<T>::capacity() const { return _capacity; }

template <class T>
void vector<T>::push_back(const T& t) {
    if (_size == _capacity) extend();
    data[_size] = t;
    ++_size;
}

template <class T>
void vector<T>::pop_back() {
    if (_size != 0)
        --_size;
    else
        throw std::runtime_error("vector is empty");
}

template <class T>
void vector<T>::clear() {
    _size = 0;
    _capacity = 0;
    delete[] data;
    data = nullptr;
}

template <class T>
const T& vector<T>::back() const {
    if (_size != 0)
        return data[_size - 1];
    else
        throw std::runtime_error("vector is empty");
}

template <class T>
T& vector<T>::back() {
    if (_size != 0)
        return data[_size - 1];
    else
        throw std::runtime_error("vector is empty");
}

template<class T>
const T &vector<T>::front() const {
    if (_size != 0)
        return data[0];
    else
        throw std::runtime_error("vector is empty");
}

template<class T>
T &vector<T>::front() {
    if (_size != 0)
        return data[0];
    else
        throw std::runtime_error("vector is empty");
}

template <class T>
const T& vector<T>::operator[](unsigned i) const { return data[i]; }

template <class T>
T& vector<T>::operator[](unsigned i) { return data[i]; }

template <class T>
bool vector<T>::operator==(const vector& v) const {
    if (_size == v._size) {
        for (unsigned i = 0; i < _size; ++i)
            if (data[i] != v.data[i])
                return false;
        return true;
    }
    else
        return false;
}

template <class T>
bool vector<T>::operator!=(const vector& v) const {
    if (_size == v._size) {
        for (unsigned i = 0; i < _size; ++i)
            if (data[i] != v.data[i])
                return true;
        return false;
    }
    else
        return true;
}

template<class T>
typename vector<T>::iterator vector<T>::begin() {
    if (_size == 0)return iterator(nullptr);
    else return iterator(data);
}

template<class T>
typename vector<T>::iterator vector<T>::end() {
    return iterator(_size == 0 ? nullptr : data + _size);
}

template <class T>
typename vector<T>::const_iterator vector<T>::begin() const {
    if (_size == 0)return const_iterator(nullptr);
    return const_iterator(data);
}

template <class T>
typename vector<T>::const_iterator vector<T>::end() const {
    return const_iterator(_size == 0 ? nullptr : data + _size);
}

template<class T>
typename vector<T>::iterator vector<T>::insert(const T & t, vector::const_iterator pt) {
    if (_size == 0) {
        push_back(t);
        return begin();
    }
    // size > 0
    int offset = pt.ptr - begin().ptr;
    if (offset<0 || static_cast<unsigned>(offset) >_size) {
        throw std::out_of_range("iterator out of range");
    }
    // range corretto, offset >= 0
    if (_size == _capacity) {
        extend();
        pt = begin() + offset;
    }
    for (int i = _size - 1; i >= offset; --i)
        data[i + 1] = data[i];

    data[offset] = t;
    _size++;
    return iterator(data + offset);
}

template<class T>
typename vector<T>::iterator vector<T>::erase(const vector::const_iterator& pt) {
    if (_size != 0) {
        int offset = pt - begin();
        if (offset<0 || offset > static_cast<int>(_size)) {
            throw std::out_of_range("iterator out of range");
        }
        for (unsigned i = static_cast<unsigned>(offset); i < _size - 1; ++i)
            data[i] = data[i + 1];
        _size--;

        return iterator(data + offset);
    }
    else
        throw std::runtime_error("vector is empty");
}

// iterator:
// ====================================================================================
template<class T>
vector<T>::iterator::iterator(T * p) :ptr(p) {}

template<class T>
T &vector<T>::iterator::operator*() const {
    return *ptr;
}

template<class T>
T *vector<T>::iterator::operator->() const {
    return ptr;
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator++() {
    ptr++;
    return *this;
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator--() {
    ptr--;
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator++(int) {
    iterator aux = *this;
    ptr++;
    return aux;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator--(int) {
    iterator aux = *this;
    ptr--;
    return aux;
}

template<class T>
bool vector<T>::iterator::operator==(const vector::iterator & it) const {
    return ptr == it.ptr;
}

template<class T>
bool vector<T>::iterator::operator!=(const vector::iterator & it) const {
    return ptr != it.ptr;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator+(int n) const {
    return iterator(ptr + n);
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator-(int n) const { return iterator(ptr - n); }

template<class T>
int vector<T>::iterator::operator-(const_iterator cit) const { return ptr - cit.ptr; }

// const_iterator:
// ===================================================================================================
template<class T>
vector<T>::const_iterator::const_iterator(const T* p) : ptr(p) {}

template<class T>
vector<T>::const_iterator::const_iterator(const iterator& it) : ptr(it.ptr) {}

template<class T>
const T& vector<T>::const_iterator::operator*() const { return *ptr; }

template<class T>
const T* vector<T>::const_iterator::operator->() const { return ptr; }

template<class T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator++() {
    ptr++;
    return *this;
}

template<class T>
typename vector<T>::const_iterator& vector<T>::const_iterator::operator--() {
    ptr--;
    return *this;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++(int) {
    iterator aux = *this;
    ptr++;
    return aux;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator--(int) {
    iterator aux = *this;
    ptr--;
    return aux;
}

template<class T>
bool vector<T>::const_iterator::operator==(const vector::const_iterator & it) const { return ptr == it.ptr; }

template<class T>
bool vector<T>::const_iterator::operator!=(const vector::const_iterator & it) const { return ptr != it.ptr; }

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator+(int n) const {
    return const_iterator(ptr + n);
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator-(int n) const {
    return const_iterator(ptr - n);
}

template<class T>
int vector<T>::const_iterator::operator-(const_iterator cit) const {
    return ptr - cit.ptr;
}

template <class T>
void vector<T>::sort() { std::sort(data, data + _size); }

#endif // VECTOR_TCC
