//
// Created by viruser on 2023/5/5.
//

#ifndef TUTORIAL_SMART_PTR_H
#define TUTORIAL_SMART_PTR_H


#include <memory>
#include <iostream>
#include <string>

class Base : public std::enable_shared_from_this<Base> {
public:
    virtual ~Base() {};

    std::shared_ptr<Base> get_shared_ptr() {
        return shared_from_this();
    }

    virtual void call() {
        std::cout << "Base call" << std::endl;
    }

    std::string m_base{"base"};
};

class Base2 {
public:
    std::string m_base2{"base2"};
};

class Derived : public Base, public Base2 {
public:
    std::string m_derived{"derivred"};

    void call() override {
        std::cout << "Derived call" << std::endl;
    }
};

class Test : public std::enable_shared_from_this<Test> {
public:
    std::shared_ptr<Test> getPtr() {
        return std::shared_ptr<Test>(this); //错误，等价于shared_ptr<Test> spa(new Test())两次，两个智能指针引用计数独立
    }

    std::shared_ptr<Test> getShared_ptr() {
        return shared_from_this();
    }


    std::string m_str{"test"};
};

class TestDestruct {
public:
    TestDestruct() {
        std::cout << "Test_Destruct C" << std::endl;
    };


    ~TestDestruct() {
        std::cout << "Test_Destruct D" << std::endl;
    }
};

class TestConstruct {
public:
    TestConstruct() {
        if (!m_shared_ptr) {
            m_shared_ptr = std::make_shared<TestDestruct>();
        }
        if (!m_unique_ptr) {
            m_unique_ptr = std::make_unique<TestDestruct>();
        }
    }

    ~TestConstruct() = default;

    std::shared_ptr<TestDestruct> m_shared_ptr;
    std::unique_ptr<TestDestruct> m_unique_ptr;
};


#endif //TUTURIAL_SMART_PTR_H
