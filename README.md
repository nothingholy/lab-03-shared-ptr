[![Build Status](https://travis-ci.org/nothingholy/lab-03-shared-ptr.svg?branch=master)](https://travis-ci.org/nothingholy/lab-03-shared-ptr) [![forthebadge](https://forthebadge.com/images/badges/60-percent-of-the-time-works-every-time.svg)](https://forthebadge.com) ![nothingholy](https://img.shields.io/badge/nothing-holy-red) ![GitHub repo size](https://img.shields.io/github/repo-size/nothingholy/lab-03-shared-ptr)

# Лабораторная работа №3

### Задание

**SharedPtr** реализует подсчет ссылок на ресурс. Ресурс освободится тогда, когда счетчик ссылок на него будет равен 0. Как видно, система реализует одно из основных правил сборщика мусора.
Многопоточное программирование сложно представить без использования класса `shared_ptr`. Например, класс `scoped_refptr` (аналог `std::shared_ptr`) используется в Chromium [32,753 раз](https://cs.chromium.org/search/?q=scoped_refptr&sq=package:chromium&type=cs). Чтобы лучше усвоить и понять принцип работы этого "умного" указателя, необходимо его реализовать своими руками.

Реализуйте шаблон класса `SharedPtr`. Для счетчика ссылок используйте переменную класса `std::atomic_uint`. Интерфейс работы с этим классом аналогичен работе с переменной типа `unsigned int`, т.е. к нему применимы операции префиксного инкремента и декремента.

```cpp
template <typename T>
class SharedPtr {
public:
    SharedPtr();
    SharedPtr(T* ptr);
    SharedPtr(const SharedPtr& r);
    SharedPtr(SharedPtr&& r);
    ~SharedPtr();
    auto opeartor=(const SharedPtr& r) -> SharedPtr&;
    auto opeartor=(SharedPtr&& r) -> SharedPtr&;

    // проверяет, указывает ли указатель на объект
    operator bool() const;
    auto operator*() const -> T&;
    auto operator->() const -> T*;
    
    auto get() -> T*;
    void reset();
    void reset(T* ptr);
    void swap(SharedPtr& r);
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t;
};
```
