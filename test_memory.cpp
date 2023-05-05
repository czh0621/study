#include <iostream>
#include "memory_assign/const_static.h"
#include "virtual_class/virtual_calss.h"

extern void g_print();//编译报错！ static 隐藏函数
using namespace std;


void test_const_static() {
    const_static::c_func();
    const_static test;
    test.print();
//    g_print();
    g_func();
}

void test_class() {
    virtual_base a;
    virtrial_class v;
    cout << "空类大小：" << sizeof(virtual_base) << " 虚函数类大小：" << sizeof(virtrial_class) << endl;
}

void test_class_memory() {
    Derived d;
    Base b;
    Base *ptr = &d;
    std::cout << "Derived address: " << &d << std::endl;
    std::cout << "Base address: " << ptr << std::endl;
    std::cout << "Base size: " << sizeof(Base) << std::endl;
    std::cout << "Derived size: " << sizeof(Derived) << std::endl;
    auto p = (char *) &d + 8;
    int *t = reinterpret_cast<int *>(p);
    std::cout << "Derived +8: " << *t << std::endl;
    int offset = (char *) &d - (char *) ptr;
    std::cout << "Offset: " << offset << std::endl;
    cout << "test ptr->base" << endl;
    ptr = &b;
    ptr->print();
    ptr->common();
    ptr->f1();
    //ptr->f2();//编译不过 ‘class Base’ has no member named ‘f2’
    ptr->override();
    ptr->redefine();

    cout << "test ptr->derived" << endl;
    ptr = &d;
    ptr->print();
    ptr->common();
    ptr->f1();
    //ptr->f2();//编译不过 ‘class Base’ has no member named ‘f2’
    ptr->override();
    ptr->redefine();
    auto ptr_derived = dynamic_cast<Derived*>(ptr);
    ptr_derived->f2();
    ptr_derived->redefine();
    ptr_derived->redefine(1);
}

int main() {
//    test_class();
//    test_class_memory();

    test_const_static();
    return 0;
}
