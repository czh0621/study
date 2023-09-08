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
    auto ptr_derived = dynamic_cast<Derived *>(ptr);
    ptr_derived->f2();
    ptr_derived->redefine();
    ptr_derived->redefine(1);
}


void test_cast() {
    Derived2 d;
    BaseA *pA = &d;
    BaseB *pB = &d;
    {
        Derived2 *pD = dynamic_cast<Derived2 *>(pA);
        if (pD != nullptr) {
            std::cout << "pD != nullptr" << std::endl;
            pD->funcA();
            pD->funcB();
        }
        pD = (Derived2 *) pA;
        pD->funcA();
        pD->funcB();
        //都是子类地址 调用子类函数 此时也走虚函数表（读取的时子类的虚函数表），只不过这里没有重写，调用的都是基类函数。
        d.common1();
        d.common2();
    }
    {
        BaseA *pA2 = dynamic_cast<BaseA *>(pB);
        if (pA2 != nullptr) {
            std::cout << "pA2 != nullptr" << std::endl;
            pA2->funcA();
            pA2->common1();
        }
        pA2 = (BaseA *) pB;
        pA2->funcA();
        pA2->common1();
    }

    {
        BaseB *pB2 = dynamic_cast<BaseB *>(pA); //进行了地址偏移，pB2地址指向了BaseB部分地址
        if (pB2 != nullptr) {
            std::cout << "pB2 != nullptr dynamic_cast addr :" << pB2 << std::endl; // 0x7fffd79f5300
            pB2->funcB();
            //pB2->common2(); 编译不过！
        }
        pB2 = (BaseB *) pA; //PA 原来指向的就是BaseA部分，进行强转过后，未进行偏移，此时指向的还是子类对象首地址
        std::cout << "普通转换 addr :" << pB2 << endl; // 0x7fffd79f52f0 相差16字节 正好是int+vptr 16字节

        //因此调用的都是BaseA内的虚函数表中的虚函数
        pB2->funcB(); //Derived::funcA()
        pB2->common2(); //BaseA::common1()

        auto ptr = &d;
        std::cout << "ptr addr :" << ptr << endl; //
        ptr->funcB();
        ptr->common2();
    }

}

void test_class_constructor() {
    auto ptr = new Test_Derived(1);
    std::cout << "name: " << typeid(*ptr).name() << " addr" << ptr << " m_derived: " << ptr->m_derived << std::endl;
    ptr->T_func1();

    auto d = Test_Derived(2);
    d.T_func1();
    auto b = Test_Base(2);
    b.T_func1();
}

void test_volatile() {
    int i = 10;
    int a = i;
    cout << "i=" << a << endl;
    asm volatile(
    "movl $0x20, %0" // 将立即数 0x20 存储到变量 i
    : "=m" (i) // 输出操作数为内存变量 i
    );
    int b = i;
    cout << "i=" << b << endl;
}


int main() {
//    test_class();

//    test_class_memory();

//    test_const_static();

//    test_cast();

//    test_class_constructor();

//    test_volatile();

    return 0;
}
