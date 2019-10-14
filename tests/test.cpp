// Copyright 2018 Your Name <your_email>

#include <gtest/gtest.h>
#include <SharedPtr.hpp>

TEST(SharedPtr, FromPointer) {
    int buff_int = 100;
    std::string buff_string = "tests";
    auto *ptr_int = new int(buff_int);
    auto *ptr_string = new std::string(buff_string);

    // Конструктор
    auto shared_ptr_int = SharedPtr<int>(ptr_int);
    auto shared_ptr_string = SharedPtr<std::string>(ptr_string);
    auto shared_ptr_null = SharedPtr<int>();

    // Оператор копирования
    auto shared_ptr_int_Copy = shared_ptr_int;
    // Проверка
    EXPECT_EQ(shared_ptr_int_Copy.get(), ptr_int);
    EXPECT_EQ(shared_ptr_int_Copy.use_count(), 2);

    // Конструктор (оператор) перемещения
    auto shared_ptr_int_Move = SharedPtr<int>(std::move(shared_ptr_int_Copy));

    // Проверка
    EXPECT_EQ(shared_ptr_int_Move.get(), ptr_int);
    EXPECT_EQ(shared_ptr_int_Move.use_count(), 2);
    EXPECT_EQ(shared_ptr_int_Copy.get(), nullptr);

    // Указывает ли указатель на объект
    EXPECT_EQ(static_cast<bool>( shared_ptr_int), true);
    EXPECT_EQ(static_cast<bool>( shared_ptr_string), true);
    EXPECT_EQ(static_cast<bool>( shared_ptr_null), false);

    // Значение счётчика ссылок
    EXPECT_EQ(shared_ptr_int.use_count(), 2);
    EXPECT_EQ(shared_ptr_string.use_count(), 1);
    EXPECT_EQ(shared_ptr_null.use_count(), 0);

    // Значение объекта (ссылка)
    EXPECT_EQ(*shared_ptr_int, buff_int);
    EXPECT_EQ(*shared_ptr_string, buff_string);

    // Указатель на объект
    EXPECT_EQ(shared_ptr_int.get(), ptr_int);
    EXPECT_EQ(shared_ptr_string.get(), ptr_string);
    EXPECT_EQ(shared_ptr_null.get(), nullptr);

    // Указатель на объект
    EXPECT_EQ(shared_ptr_int.operator->(), ptr_int);
    EXPECT_EQ(shared_ptr_string->empty(), ptr_string->empty());
    EXPECT_EQ(shared_ptr_null.operator->(), nullptr);

    // Свап
    shared_ptr_int.swap(shared_ptr_null);
    // Проверка
    EXPECT_EQ(shared_ptr_int.get(), nullptr);
    EXPECT_EQ(shared_ptr_null.get(), ptr_int);

    // Ресет
    shared_ptr_int.reset(ptr_int);
    shared_ptr_null.reset();

    // Проверка
    EXPECT_EQ(shared_ptr_int.get(), ptr_int);
    EXPECT_EQ(shared_ptr_null.get(), nullptr);
}
