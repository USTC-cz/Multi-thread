//
//  main.cpp
//  conditionV
//
//  Created by chow Choi on 2020/11/6.
//


class A {
public:
    // 收到的命令如队列的线程
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            
            
            std::cout << "插入命令 " << i << std::endl;
            
            std::unique_lock<std::mutex> guard(my_mutex );
            msgRecvQueue.push_back(i);
            
            
            // 假如outMsgRecvQueue正在处理一个事物，需要一段时间，而不是卡在wait（）那里等待唤醒，则此时这个notify_one()没什么用
            //my_cond.notify_one(); //   尝试唤醒wait（）的线程
            my_cond.notify_all();
            
            
            // 操作数据。。。。。。
        }
    }
    
    // 从消息队列中取数据的线程
    void outMsgRecvQueue() {
        while (true) {
            std::unique_lock(std::mutex) guard(my_mutex);    //自动上锁
            
            
            // wait()用来等一个东西
            // 如果第二个参数返回true，那wait（）直接返回，执行后面代码
            // 如果第二个参数返回false， wait（）将解锁互斥量，并阻塞在本行，
            //           阻塞到什么时候为止？ 阻塞到其他某个线程调用notify_one()为止
            // 如果没有第二个参数：my_cond.wait(guard); 那么就跟第二个参数返回false一样
            //           即 wait（）将解锁互斥量，并阻塞在本行，阻塞到其他某个线程调用notify_one()为止
            
            // 当其他线程调用notify_one()将本wait（原来是阻塞）的状态唤醒后，wait开始工作，干什么呢？
            // a）wait（）不断尝试获取互斥量，如果获取不到，则流程卡在wait这等着获取，如果获取到锁
            // b）
                        //b.1) 如果wait（）有第二个参数，如果返回false，则wait（）又对互斥量解锁
                        //b。2）如果有第二个参数， 表达式为true， 则wait（）返回，流程接着走（此时占据着互斥量）
                        //b。3）如果wait（）没有第二个参数，则wait（）返回，流程接着走
            
            my_cond.wait(guard, [this] {      // 第二个参数是可调用对象
                if (!msgRecvQueu.empty()) {
                    return true;
                } else {
                    return false;
                }
            })；
            
            // 只要流程能走到这，锁一定是锁着的,且msgRecvQueue至少有一条数据
            msgRecvQueue.front();
            msgRecvQueue.pop();
            guard.unlock();
            
        }
       
    }
private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex;
    std::condition_variable my_cond;
};

#include <iostream>

int main(int argc, const char * argv[]) {
    
    // 一：条件变量std::condition_varibale  wait()  notify_one():只能通知一个线程
    // 线程A：等待一个条件满足
    // 线程B：专门往消息队列中扔消息
    
    // std::condition_variable实际上是个和条件相关的类
    // 需要和互斥量配合工作，用的时候需要生成类的对象
    
    
    // 二：上述代码深入思考
    // 写队列多，去队列一次只取一条？
    // 写队列加个限制？写多少条就缓缓
    
    // 三：notify_all()
    
    A myobj;
    std::thread outMsgThread(&A::inMsgRecvQueue, std::ref(myobj));
    std::thread outMsgThread2(&A::inMsgRecvQueue, std::ref(myobj));
    std::thread inMsgThread(&A::outMsgRecvQueue, std::ref(myobj));
    inMsgThread.join();
    outMsgThread.join();
    outMsgThread2.join();
    return 0;
}
