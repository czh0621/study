//
// Created by viruser on 2023/5/5.
//
#include "smart_ptr/smart_ptr.h"
#include <iostream>
#include <map>
#include <atomic>
#include <vector>

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

    double *pd = reinterpret_cast<double *>(pv); // 将 void 指针转换为 double 指针

    *pd = 3.14; // 在 double 指针上进行赋值操作

    std::cout << "n = " << n << std::endl; // 输出 n 的值
}

void test_unique_ptr() {
    std::unique_ptr<int> p = std::make_unique<int>(5);
    std::map<int, std::unique_ptr<int>> m_map;
    m_map[0] = std::move(p);
    auto tmp = std::move(m_map[0]);// map 中0号索引存储的智能指针被掏空，置为默认值NULL
    std::cout << *m_map[0] << m_map.size() << std::endl;
//    std::cout << *tmp << m_map.size() << std::endl;
}

void test_int() {
    // int 有符号 根据平台来显示一般32位、64位
    // int32_t 有符号 指定32长度
    //size_t 无符号 根据平台来显示
    // long 有符号 根据平台来显示 32位等于int
    // long long 强指定64位 有符号
    std::cout << sizeof(int) << "---" << sizeof(int32_t) << "-----" << sizeof(size_t) << "---" << sizeof(long) << "---"
              << sizeof(long long);
}

void test_destruct_ptr() {
    TestConstruct();
}

int main() {
//    test_return_ptr();
//    test_smart_ptr();
//    test_convert();
//    test_unique_ptr();
//    test_destruct_ptr();
    const std::string s1 = "";
    std::string s2;
    s2 = s1+"1";
    std::cout<<"xx";


    return 0;
}