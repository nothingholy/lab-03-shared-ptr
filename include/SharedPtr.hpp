#pragma once

#include <iostream>
#include <atomic>
#include <algorithm>
#include <cstddef>
#include <string>
using namespace std;

template <typename T>
class SharedPtr{
private:
    T* pointer;
    atomic_uint *counter;
public:
    SharedPtr(){
        pointer = nullptr;
        counter= nullptr;
    };
    explicit SharedPtr(T* ptr){
        pointer=ptr;
        counter = new atomic_uint(1);
    };
    SharedPtr(const SharedPtr& r){
        counter= nullptr;
        *this=r;
    };
    SharedPtr(SharedPtr&& r) noexcept {
        counter= nullptr;
        *this=std::move(r);
    };
    ~SharedPtr() {
        if (counter == nullptr)
            return;
        (counter)--;
        if (counter == 0) {
            delete pointer;
            delete counter;
        }
    };
    auto operator=(const SharedPtr& r)->SharedPtr&{
        if(this==&r)
            return *this;

        this->~SharedPtr();

        pointer=r.pointer;
        counter=r.counter;
        (*counter)++;

        return *this;
    };
    auto operator=(SharedPtr&& r)->SharedPtr&{ //сократить
        if(this==&r)
            return *this;

        this->~SharedPtr();

        pointer=r.pointer;
        counter=r.counter;
        r.counter= nullptr;
        r.pointer= nullptr;

        return *this;
    };
    operator bool() const{
        return pointer!=nullptr;
    };
    auto operator*() const->T&{
        return *pointer;
    };
    auto operator->() const->T*{
        return pointer;
    };
    auto get()->T*{
        return pointer;
    };
    void reset(){
        *this=SharedPtr();
    };
    void reset(T* ptr){
        *this=SharedPtr(ptr);
    };

    void swap(SharedPtr& r){
        std::swap(pointer,r.pointer);
        std::swap(counter,r.counter);
    };

    auto use_count() const->size_t {
        if(counter!= nullptr)
            return *counter;
        else
            return 0;
    };
};
