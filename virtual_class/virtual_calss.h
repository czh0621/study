//
// Created by viruser on 2023/4/28.
//

#ifndef TUTORIAL_VIRTUAL_CALSS_H
#define TUTORIAL_VIRTUAL_CALSS_H

#include <iostream>

enum Type {
    type0 = 0, type1,
};

using namespace std;

class virtrial_class {

};

class virtual_base {
public:
    virtual_base() {}

    virtual ~virtual_base() {}
};

class Base {
public:
    virtual void print() { cout << "Base" << endl; }

    void common() { cout << "base common" << endl; }

    void f1() { cout << "base f1" << endl; }

    virtual void override() {
        cout << "base virtual override" << endl;
    }

    void redefine() {
        cout << "base test redefine" << endl;
    }


private:
    int m_base = 1;
};

class Derived : public Base {
public:
    virtual void print() { cout << "Derived" << endl; }

    void f2() { cout << "Derived f2" << endl; }

    virtual void override() override {
        cout << "Derived virtual override" << endl;
    }

    void redefine() {
        cout << "Derived redefine" << endl;
    }

    void redefine(int t) {
        cout << "Derived overload " << endl;
    }


private:
    int m_derived = 2;
};


#include <iostream>

class BaseA {
public:
    virtual void funcA() { std::cout << "BaseA::funcA()" << std::endl; }

    virtual void common1() { std::cout << "BaseA::common1()" << std::endl; };

    int m_BaseA;
};

class BaseB {
public:
    virtual void funcB() { std::cout << "BaseB::funcB()" << std::endl; }

    virtual void common2() { std::cout << "BaseB::common2()" << std::endl; };

    int m_BaseB;
};

class Derived2 : public BaseA, public BaseB {
public:
    virtual void funcA() override { std::cout << "Derived::funcA()" << std::endl; }

    virtual void funcB() override { std::cout << "Derived::funcB()" << std::endl; }

    int m_Derived2;
};


class Test_Base {
public:
    Test_Base(int x) {
        m_base = x;
        //此处的this 为基类指针，但是指针地址为子类地址（也是子类对象中的基类部分首地址），它指向正在初始化的对象的内存地址
        std::cout << "name: " << typeid(*this).name() << " addr" << this << " m_base: " << m_base << std::endl;
    }

    void T_func1() {
        //此处隐式this 指针 基类类型！会形成多态！
        this->T_func_common();
    }

    virtual void T_func_common() {
        std::cout << "Test_Base call" << std::endl;
    }

    int m_base;
};

class Test_Derived : public Test_Base {
public:
    Test_Derived(int x) : m_derived(x), Test_Base(x) {}

    virtual void T_func_common() override {
        std::cout << "Test_Derived call" << std::endl;
    }

    int m_derived;
};

class Base_b {
public:
    int publicMember;
protected:
    int protectedMember;
private:
    int privateMember;
};

class Derived_d : public Base_b {
public:
    void accessBaseMembers() {
        publicMember = 42;       // 子类可以访问基类的公有成员
        protectedMember = 42;    // 子类可以访问基类的保护成员
//         privateMember = 42;   // 子类不能直接访问基类的私有成员
    }
};


#endif //TUTURIAL_VIRTUAL_CALSS_H
