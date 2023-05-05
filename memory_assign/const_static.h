//
// Created by viruser on 2023/4/28.
//

#ifndef TUTURIAL_CONST_STATIC_H
#define TUTURIAL_CONST_STATIC_H

#include <string>
#include <iostream>

char *g_char_ptr_uninit; //B
int g_int_unnit; //B

int g_int_init = 5; //D
char g_char_init = 0x11;//D

const char *g_const_char_ptr_uninit;//B

static char *g_static_ptr_uninit;//b

const char *const g_const_char_ptr_const_init = "g_const_char_ptr_const_init"; //r
const char *g_const_char_ptr_init = "g_const_char_ptr_init";//D 注意！！！！！

const int g_const_int_init = 22; //r
const char g_const_char_init = 0xff;//r

char g_char_array_init[] = "g_char_array"; //D
const char g_const_char_array_init[] = "g_const_char_array"; //r

static char *g_static_char_ptr_init = "g_static_char_ptr_init"; //d
static const std::string g_static_const_str_init = "g_static_const_str_init";//b

//t
static void g_func() {
    std::string tmp("tmp");
    std::cout << tmp << std::endl;
}


class const_static {

public:
    const_static() : m_ci(5), m_char("123") {}

    static void c_func() {
        std::cout << m_s << std::endl;
        std::cout << m_static_const_char << std::endl;
    }

    void print() {
        std::cout << m_i << m_ci << *m_char << std::endl;
    }


public:
    int m_i; //构造未初始化，随机赋值！
    const int m_ci = 0; // const 成员变量（1）类内初始化 （2）构造初始化
    const char *m_char;
    static std::string m_s; //无法类内初始化，构造初始化---因为不是简单类型string,只能类显示外初始化
//    static const std::string m_str='1';
    static const char m_static_const_char = '1'; //const static 简单类型可以类内初始化
};

std::string const_static::m_s = "static_member";


#endif //TUTURIAL_CONST_STATIC_H
