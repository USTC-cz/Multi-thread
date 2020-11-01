//
//  main.cpp
//  c++11_thread
//
//  Created by chow Choi on 2020/10/29.
//

#include <iostream>
#include <thread>

//自己创建的线程也要从一个初始函数开始运行
void myprint_join() {
    std::cout << "我的线程开始执行" << std::endl;
    
    std::cout << "我的线程执行完毕" << std::endl;
}

void myprint_detach() {
    std::cout << "我的线程开始执行1" << std::endl;
    std::cout << "我的线程开始执行2" << std::endl;
    std::cout << "我的线程开始执行3" << std::endl;
    std::cout << "我的线程开始执行4" << std::endl;
    std::cout << "我的线程开始执行5" << std::endl;
    
    std::cout << "我的线程执行完毕" << std::endl;
}

class TA {
public:
    TA(int &i) : m_i(i) {}
    // 重载（）操作符
    void operator()() {
        std::cout << "opeartor()开始执行" << std::endl;
        std::cout << "m_i1 = " << m_i << std::endl;
        std::cout << "m_i2 = " << m_i << std::endl;
        std::cout << "m_i3 = " << m_i << std::endl;
        std::cout << "m_i4 = " << m_i << std::endl;
        std::cout << "operator()结束执行" << std::endl;
    }
public:
    int &m_i;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    // 一：范例演示线程运行的开始和结束
    // 程序运行起来，生成一个进程，该进程所属的“主线程“开始自动运行；
    
    // 实际上这个是主线程在执行，主线程丛main（）函数返回，则整个进程执行完毕。

   // 主线程丛main（）开始执行，那么我们自己创建的线程，也需要从一个函数开始运行（初始函数），一旦这个函数运行完毕，就代表我们这个线程运行结束。
    
    // 整个进程是否执行完毕的标志是 主线程是否执行完毕，如果主线程执行完毕了，就代表片整个进程执行完毕了；
    // 此时，如果其他子线程还没有执行完毕，那么这些子线程也会被操作系统强行终止。
    // 所以，一班情况下，得到一个结论：如果想保持子线程（自己创建的线程）的运行状态的话，那么要让主线程一直保持运行，不要让主线程运行完毕。
    // 【这条规律有例外，目前先这样理解和记忆】
    
    // a）包含<thread>
    // b）初始函数
    // c）main中开始写代码
    
    // 明确一点： 有两个线程再跑，程序的执行有两条线同时在走，可以同时干两个事。即使一条线被堵住，另一条线也可以走
    
    //std::thread my_thread_obj1(myprint_join);  // myprint 可调用对象。
    // （1）创建了线程，线程执行起点入口myprint（）；
    // （2）此句一执行，myprint线程就开始执行。
    
    // my_thread_obj1.join();
    // join（）：加入/汇合，说白了就是阻塞，阻塞主线程，让主线程等待子线程执行完毕，然后子线程和主线程汇合再往下走。
    // 主线程阻塞到这里等待myprint（）执行完，当子线程执行完毕，这个join（）就执行完毕，主线程就继续往前走。
    // 通常，主线程执行完毕，但子线程还没执行完毕，程序是不合格不稳定的。
    
    //std::thread my_thread_obj2(myprint_detach);
    //my_thread_obj2.detach();
    // detach（）：传统多线程程序主线程要等待子线程执行完毕，然后自己最后退出。
    // detach：分离。 也就是主线程不和子线程汇合了，各自执行各自的，主线程不必等待子线程执行结束，可以先结束，不影响子线程的执行。
    // 为什么引入detach（）：创建了很多子线程，让主线程逐个等待子线程结束，这种编程方法不好，所以引入detach（）；
    // 一旦detach（）之后，与主线程关联的thread对象就会失去与主线程的关联，此时这个子线程就会驻留在后台运行，子线程被c++运行时库接管，子线程执行完成后，由运行时库清理该线程相关资源（守护线程）
    
    
    // joinable(): 判断是否可以成功使用join（）或detach（），返回true或false
    
    
    // 二：其他创建线程方法
    // 2.1 用类
    //int i = 37;
    //TA ta(i);  // m_i是引用，i是主线程变量，detach（）时，主线程结束，变量销毁，子线程引用可能不对
    // 还有一个疑问，调用detach（），若主线程结束，这个ta对象还在吗？（对象不在了）
    // 这个对象实际上是被复制到线程中去；主线程执行完，ta会被销毁，但所复制的TA对象任然存在
    // 指针等成员变量就没问题（深拷贝浅拷贝）
    //std::thread myobj3(ta);
    //myobj3.detach();
    
    // 2.2 用lambda表达式
    auto mylambdathread = [] {
        std::cout << "lambda thread 开始执行" << std::endl;
        std::cout << "lambda thread 结束执行" << std::endl;
    };
    std::thread myobj4(mylambdathread);
    myobj4.join();
    
    
    std::cout << "I Love China!1" << std::endl;
    std::cout << "I Love China!2" << std::endl;
    std::cout << "I Love China!3" << std::endl;
    std::cout << "I Love China!4" << std::endl;
    std::cout << "I Love China!5" << std::endl;
    
    return 0;
}
