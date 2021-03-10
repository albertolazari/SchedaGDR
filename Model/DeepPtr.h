#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>
class DeepPtr {
private:
    T* pointer;

public:
    DeepPtr(T* = nullptr);

    DeepPtr(const DeepPtr&);
    ~DeepPtr();
    DeepPtr& operator=(const DeepPtr&);
    DeepPtr& operator=(T*);

    T* get() const;
    T* release();

    operator bool();

    T& operator*() const;
    T* operator->() const;

    bool operator==(const DeepPtr&) const;
    bool operator!=(const DeepPtr&) const;
};

#include "DeepPtr.tcc"

#endif // DEEPPTR_H
