#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>

template <class T>
class vector {
private:
    unsigned _size, _capacity;
    T* data;

    void extend();

public:
    class const_iterator;
    class iterator {
        friend class vector;
    private:
        T* ptr;

    public:
        iterator(T*);
        T& operator*() const;
        T* operator->() const;
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator operator+(int) const;
        iterator operator-(int) const;
        int operator-(const_iterator) const;
        bool operator==(const iterator&) const;
        bool operator!=(const iterator&) const;
    };
    class const_iterator {
        friend class vector;
    private:
        const T* ptr;

    public:
        const_iterator(const T*);
        const_iterator(const iterator&);

        const T& operator*() const;
        const T* operator->() const;
        const_iterator& operator++();
        const_iterator operator++(int);
        const_iterator& operator--();
        const_iterator operator--(int);
        const_iterator operator+(int) const;
        const_iterator operator-(int) const;
        int operator-(const_iterator) const;
        bool operator==(const const_iterator&) const;
        bool operator!=(const const_iterator&) const;
    };
    vector(unsigned size = 0, const T& init = T());
    vector(const_iterator, const_iterator);
    vector(std::initializer_list<T>);

    vector(const vector&);

    ~vector();
    vector& operator=(const vector&);

    bool empty() const;
    unsigned size() const;
    unsigned capacity() const;

    void push_back(const T&);
    void pop_back();

    void clear();

    const T& back() const;
    T& back();

    const T& front() const;
    T& front();

    const T& operator[](unsigned) const;
    T& operator[](unsigned);

    bool operator==(const vector&) const;
    bool operator!=(const vector&) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    iterator insert(const T&, const_iterator);
    iterator erase(const const_iterator&);

    void sort();
};

#include "vector.tcc"

#endif // VECTOR_H
