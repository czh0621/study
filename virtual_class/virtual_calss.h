//
// Created by viruser on 2023/4/28.
//

#ifndef TUTURIAL_VIRTUAL_CALSS_H
#define TUTURIAL_VIRTUAL_CALSS_H

#include <iostream>

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
    virtual void print() { cout << "hello" << endl; }

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
    virtual void print() { cout << "world" << endl; }

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


#endif //TUTURIAL_VIRTUAL_CALSS_H
