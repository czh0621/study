//
// Created by viruser on 2023/5/25.
//

#include_next "template/deduce_template.h"
#include <string>
#include <iostream>
#include <thread>

#define X 2;


void test_template_void() {
    set_value<void>();
}

void test_template_char() {
    int v[] = {1, 2, 3, 4};
    auto num = array_size(v);
    std::cout << "num :" << num;
}

void test_init_class() {
    int x = 5;
    auto &y = x;
//    test<decltype(y)> t; // 编译报错！error: ‘m_value’ declared as reference but not initialized  T m_value;
}

void test_concpet() {
    auto lambda = []() { std::cout << "Lambda is called." << std::endl; };
    callAndPrint(lambda); // 可以通过，因为 lambda 满足 Callable 概念
     callAndPrint(42);
}


int main() {
//    test_template_char();
    test_concpet();
    return 0;
}