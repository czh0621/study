//
// Created by viruser on 2023/5/25.
//

#ifndef TUTORIAL_DEDUCE_TEMPLATE_H
#define TUTORIAL_DEDUCE_TEMPLATE_H

#include <iostream>
#include <type_traits>
#include <utility>
#include <concepts> // C++20 标准引入的头文件，包含 concept 相关内容

//
template<typename T, typename =std::enable_if_t<!std::is_void<T>::value, T>>
void set_value(T &&value) {
//    T m_value;
}

template<typename T, typename =std::enable_if_t<std::is_void<T>::value, void>>
void set_value(void) {

};


// 声明数组引用 可以推导数组个数。
template<typename T, typename std::size_t N>
constexpr std::size_t array_size(T(&)[N]) {
    return N;
}

//此处需保证 T不被推导T&等
template<typename T>
class test {
public:
    test() {
        T m_value;
    }
};


template<typename... Args, size_t Indices>
void print_impl(std::index_sequence<Indices>, Args &&... args) {
    std::cout << "Indices" << Indices << "";
    ((std::cout << args << " "), ...);
    std::cout << std::endl;
}

template<typename... Args>
void print(Args &&... args) {
    print_impl(std::make_index_sequence<sizeof...(args)>(), args...);
}

template<typename T>
concept Callable = requires(T
t) {
t(); // 要求类型 T 可以被调用
};

// 使用 concept 对模板参数进行约束
template<Callable T>
void callAndPrint(T
func) {
func();
}


#endif //TUTURIAL_DEDUCE_TEMPLATE_H
