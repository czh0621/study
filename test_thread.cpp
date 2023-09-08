//
// Created by viruser on 2023/6/14.
//

#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <vector>
#include <mutex>
#include <string>
#include <cstring>
#include <condition_variable>
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>


static thread_local int *ptr;
static thread_local int t_value;

void test_thread_local() {
    std::thread t([] {
                      if (ptr) {
                          std::cout << "t thread_local ptr not null" << t_value << std::endl;
                      }
                      ptr = new int(5);
                      std::cout << "t thread_local value" << t_value << std::endl;
                      t_value = 5;
                  }
    );
    t.detach();
    std::thread t1([] {
                       if (ptr) {
                           std::cout << "t1 thread_local ptr not null" << t_value << std::endl;
                       }

                       std::cout << "t1 thread_local value" << t_value << std::endl;
                   }
    );
    t1.detach();
}

//以下测试一个线程改变标志，通知另一线程停止处理
std::atomic<bool> g_flag{false};

//bool g_flag = false; //无锁变量肯定不行
void test() {
    std::thread t2([]() {
        {
            // while(!g_flag.load())
//            while (g_flag.compare_exchange_strong())

            while (!g_flag) {
                //do something
            }
        }
    });
    std::thread t([]() {
                      g_flag = true;
                  }
    );
}

std::atomic<bool> ready(false);
std::atomic<bool> winner(false);

void count1m(int id) {
    while (!ready) {}                  // wait for the ready signal
    std::cout << "get ready...\n";
    if (!winner.exchange(true)) { std::cout << "thread #" << id << " won!\n"; }

};

void test_atomic() {

    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i) threads.push_back(std::thread(count1m, i));
    ready = true;
    for (auto &th : threads) th.join();
}

void test_memory_leak() {
    std::thread t([]() {
        int i = 0;
        while (i < 500) {
            auto x = new int(4);
            i++;
        }
    });
    std::mutex m_metux;
    std::condition_variable m_condition_variable;
    std::unique_lock<std::mutex> lck(m_metux);
    m_condition_variable.wait(lck);
    if (t.joinable()) {
        t.join();
    }
}


//int main() {
////    test_thread_local();
////    test();
////    test_atomic();
////    test_memory_leak();
////    char *p1 = "1223";
////    char p2[5] = "1223";
////    std::string s1(p1);
////    std::string s2(p2);
////    std::string s3("1223");
////    std::cout<<"s1 :" <<s1.size()<<"-"<<std::strlen(p1)<<" s2:"<<s2.size()<<"-"<<std::strlen(p2)<<"-s3 :"<<s3[4];
////
////    const char* str = "Hello, World!";
////    std::string s(str);
////
////    std::cout << "Length of the string: " << s.length() <<" str length: "<<std::strlen(str) << std::endl;
////    std::cout << "String: " << s << std::endl;
//
////    char s[32] = {0};
////    sprintf(s, "%d", 32);
////    std::string str(s);
////    std::cout<<str;
//
//
//
//
//
//    return 0;
//}



struct A {
    std::string s;
};

void f(const std::string&s){
std::cout<<s;
}
void test_str(const char * p){
    f(p);
}



int main() {
//    const char * p = "111";
//    test_str(p);
std::string s ("123");
auto x=s.substr(0,s.length()-1);
std::cout<<x;
    return 0;
}


