//
//  main.cpp
//  c++11_thread
//
//  Created by chow Choi on 2020/11/4.
//


#include <iostream>
#include <vector>
#include <list>
#include <thread>
#include <mutex>


class Single {
private:
    std::mutex mymutex;
    static Single* m_instance;
private:
    Single() {}      // 私有化构造函数
    
public:
    static Single *GetInstance() {
        
        // 如果 （m_instance != NULL) 成立，则m_instance一定被new过，已经存在
        // 如果 （m_instance == NULL) 成立，不代表m_instance一定 没 被new过 （多线程）
        if (m_instance == NULL) {   // 双重锁定（双重检查）提高效率
            std::unique_lock<std::mutex> guard(mymutex);    // 自动加锁
          if (m_instance == NULL) {
            m_instance = new Single();
            static GC gc;
          }
        
       }
        return m_instance;
    }
    
    class GC{     // 内存回收类
    public:
        ~GC() {
            if (Single::m_instance) {
                delete Single::m_instance;
                Single::m_instance = NULL;
            }
        }
    };
};

Single *Single::m_instance = NULL;

// 线程入口函数
void mythread() {
    std::cout << "线程执行" << std::endl;
    Single *p = Single::GetInstance();
    std::cout << "线程结束" << std::endl;
}

int main(int aegc, char *argv[]) {
    // 一：设计模式大概谈
    // 设计模式： 代码的一些写法（这些写法跟常规的写法不怎么一样）：程序灵活，维护起来可能方便，但别人接管、阅读代码可能很痛苦
    
    // 二：单例设计模式
    // 单例：在整个项目中，某些类， 属于该类的对象，只能创建一个
    
    
    // 三：单例设计模式共享数据问题分析、解决
    // 面临的问题：需要在我们自己创建的线程（而不是主线程）中来创建Single这样的单例类，这种线程可能不止一个（至少2个），可能会new多次m_instance，可以简单加锁
    // 同时，我们可能面临多个线程调用GetInstance()，但因为有简单加锁又会产生效率低下问题，可参考上面 双重锁定 写法，能保证只new一次且以后多个线程同时调用GetInstance（）不会频繁加锁
    
    std::thread th1(mythread);
    std::thread th2(mythread);
    th1.join();
    th2.join();
    
    // 四：std::call_once()函数模版。 c++11标准，第二个参数是一个函数名a（）
    // 功能：保证函数a（）在多线程情况下，只被调用一次
    // call_once具备互斥量的能力，且消耗资源比互斥量少。
   // 与std::once_flag()一起使用，该标记是个结构体。 函数a（）已执行则会置标记为 已调用 状态。
    
    
    class Single {
    private:
        std::once_flag flag;           // once flag
        static Single* m_instance;
    private:
        Single() {}      // 私有化构造函数
        
        static void CreateInstance() {
            m_instance = new Single();
            static GC gc;
        }
        
    public:
        static Single *GetInstance() {
            
            std::call_once(flag, CreateInstance);           //两个线程执行到这，其中一个线程要等另一个线程执行CreateInstance完毕才执行。
            return m_instance;
        }
        
        class GC{     // 内存回收类
        public:
            ~GC() {
                if (Single::m_instance) {
                    delete Single::m_instance;
                    Single::m_instance = NULL;
                }
            }
        };
    };
}
