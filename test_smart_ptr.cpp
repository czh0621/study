//
// Created by viruser on 2023/5/5.
//
#include "smart_ptr/smart_ptr.h"
#include <iostream>

using namespace std;

void test_return_ptr() {
    Test *t_ptr = new Test();

    // smart_ptr1 和 smart_ptr2  t_ptr 三个指针同时管理同一个对象，double free 且 两个智能指针的引用计数相互独立。
    auto smart_ptr1 = t_ptr->getPtr();
    auto smart_ptr2 = t_ptr->getPtr();
    cout << "smart_ptr1 count:" << smart_ptr1.use_count() << " type :" << typeid(smart_ptr1.get()).name() << endl;
    cout << "smart_ptr2 count:" << smart_ptr2.use_count() << " type :" << typeid(smart_ptr2.get()).name() << endl;
    cout << "t_ptr addr " << t_ptr << " smart_ptr addr" << smart_ptr1.get() << endl;

    //double free 了 ，原因手动管理t_ptr 和智能指针管理 同一个对象
    {
        delete t_ptr;
        t_ptr = nullptr;
    }

    cout << "test str :" << smart_ptr1->m_str << endl;

    shared_ptr<Test> spt(new Test());
    cout << "当前资源被引用数： " << spt.use_count() << endl;    // 1
    shared_ptr<Test> sptb = spt->getShared_ptr();
    cout << "当前资源被引用数： " << spt.use_count() << endl;    // 2
}

void test_smart_ptr() {
    auto derived_ptr = make_shared<Derived>();
    shared_ptr<Base> base_prt = derived_ptr; //隐式转换 向上转换安全
    auto ptr = derived_ptr->shared_from_this();
    cout << "derived_ptr count:" << derived_ptr.use_count() << " type :" << typeid(ptr.get()).name()
         << endl; //返回基类指针，引用计数3
    cout << "base str: " << derived_ptr->m_base << " base2 str: " << derived_ptr->m_base2 << " derived str: "
         << derived_ptr->m_derived << endl;



    // shared_ptr<Derived> convert_ptr = static_pointer_cast<Derived>(ptr);
    ptr->call();
    // cout<<ptr->m_derived<<endl; 基类不可以访问子类对象！
    shared_ptr<Derived> convert_ptr = dynamic_pointer_cast<Derived>(ptr);
    convert_ptr->call();
    cout << "convert :" << convert_ptr->m_derived << " base2 str:" << convert_ptr->m_base2 << endl;
}

void test_convert() {
    int n = 10;
    void *pv = &n; // 将 int 指针转换为 void 指针

    double *pd = reinterpret_cast<double*>(pv); // 将 void 指针转换为 double 指针

    *pd = 3.14; // 在 double 指针上进行赋值操作

    std::cout << "n = " << n << std::endl; // 输出 n 的值
}


int main() {
//    test_return_ptr();
//    test_smart_ptr();
    test_convert();
    return 0;
}