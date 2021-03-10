#ifndef DEEPPTR_TCC
#define DEEPPTR_TCC

#include <vector>
#include "DeepPtr.h"
#include <typeinfo>

template <class T>
DeepPtr<T>::DeepPtr(T* ptr) : pointer(ptr) {}

template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& p) :
    pointer(p.pointer == nullptr ? nullptr : p.pointer->clone()) {}

template <class T>
DeepPtr<T>::~DeepPtr() { delete pointer; }

template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& p) {
    if (&p != this) {
        delete pointer;
        pointer = p.pointer == nullptr ? nullptr : p.pointer->clone();
    }

    return *this;
}

template <class T>
T* DeepPtr<T>::get() const { return pointer; }

template <class T>
T* DeepPtr<T>::release() {
    T* temp = pointer;
    pointer = nullptr;
    return temp;
}

template <class T>
DeepPtr<T>::operator bool() { return pointer != nullptr; }

template <class T>
T& DeepPtr<T>::operator*() const { return *pointer; }

template <class T>
T* DeepPtr<T>::operator->() const { return pointer; }

template <class T>
bool DeepPtr<T>::operator==(const DeepPtr& p) const {
    return pointer == p.pointer;
}

template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr& p) const {
    return pointer != p.pointer;
}

#endif // DEEPPTR_TCC
