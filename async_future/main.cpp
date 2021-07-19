//
//  main.cpp
//  async_future
//
//  Created by chow Choi on 2020/11/8.
//

#include <iostream>
#include <thread>
#include <future>

class A {
public:
int mythread(int arg) {
    std::cout << "mythread() start , thread id = " << std::this_thread::get_id() << std::endl;
    std::cout << "arg = " << arg << std::endl;
    std::chrono::milliseconds dura(5000);
    std::this_thread::sleep_for(dura);
    std::cout << "mythreas() end, thread id = " << std::this_thread::get_id() << std::endl;
    
    return 5;
}
};

int mythread(int arg) {
    std::cout << "mythread() start , thread id = " << std::this_thread::get_id() << std::endl;
    std::cout << "arg = " << arg << std::endl;
    std::chrono::milliseconds dura(3000);
    std::this_thread::sleep_for(dura);
    std::cout << "mythreas() end, thread id = " << std::this_thread::get_id() << std::endl;
    
    return 5;
}

void mythread1(std::promise<int> &tmp, int cal) {
    std::cout << "mythread1 start , thread id = " << std::this_thread::get_id() << std::endl;
    // 做一系列复杂操作,消耗一定时间
    cal++;
    cal *= 10;
    
    std::chrono::milliseconds dura(3000);
    std::this_thread::sleep_for(dura);
    
    // 终于算出结果
    int result = cal;
    tmp.set_value(result);     // 将结果保存到tmp对象中
    std::cout << "mythread1 end, thread id = " << std::this_thread::get_id() << std::endl;
}

//void mythread2(std::future<int> &tmp) {
void mythread2(std::shared_future<int> &tmp) {
    std::cout << "mythread2 start, thread id = " << std::this_thread::get_id() << std::endl;
    auto res = tmp.get();         // get()只能调用一次，因为是get函数移动语义
    std::cout << "mythread2 result = " << res << std::endl;
    std::cout << "mythread2 end, thread id = " << std::this_thread::get_id() << std::endl;
}

std::atomic<int> g_count(0); // 封装了int类型的原子对象
void mythreadcount() {
    g_count++;        // 原子操作，不会被打断
}

int main(int argc, const char * argv[]) {
    
    // 一： std::async  std::future创建后台任务并返回值
    // 希望线程返回一个结果
    // std::async 是一个函数模版， 用来启动一个异步任务，返回std::future对象，是一个类模版
    // 启动异步任务就是自动创建一个线程并执行入口函数，返回的std::future对象含有线程返回的结果
    // 通过调用成员函数get（）获取
    // 可以通过向std::async()函数传递std::launch枚举值，来达到一些特殊目的
    // a）std::launch::deferred: 表示线程入口函数调用被延迟到std::future的wait（）或get（）调用时才执行,实际没新建线程， 与主线程相同id
    // b）std::launch::async: 表示在调用async函数时就开始创建线程
    
    
    /*A a;
    std::cout << "main() thread id = " << std::this_thread::get_id() << std::endl;
    //std::future<int> result = std::async(mythread);
    int tmp = 12;
    std::future<int> result = std::async(std::launch::async, &A::mythread, &a, tmp);
    std::cout << "continue" << std::endl;
    int def = 0;
    def = result.get();    // 若子线程没执行完，则阻塞住等待
    // reslut.wait() // wait()等待线程返回， 但拿不到结果
    std::cout << "result = " << def << std::endl;*/
    
    
    
    // 二： std::packaged_task: 是类模版，模版参数是可调用对象，包装起来，作为线程入口函数
    
    /*std::packaged_task<int(int)> mypt(mythread);          // 把可调用对象用packaged_task包装
    std::thread t1(std::ref(mypt), 1);
    t1.join();
    std::future<int> result = mypt.get_future();
    std::cout << "result = " << result.get() << std::endl;*/
    
    
    // 三：std::promise : 类模版
    // 能够在某个线程中给它赋值，然后可以在其他线程中把这个值取出来
    
    /*std::promise<int> mypro;       // 声明一个promise对象，保存的值类型为int
    std::thread t1(mythread1, std::ref(mypro), 37);      // 在一个线程中给promise赋值
    t1.join();
    
    std::future<int> fu1 = mypro.get_future();       // promise和future绑定，用于获取线程中的值
   
    std::thread t2(mythread2, std::ref(fu1));       // promise中的值在另一个线程中使用
    t2.join();*/
    
    
    
    // 四：std::future的其他成员函数
    
    /*std::cout << "main thread id = " << std::this_thread::get_id()  << std::endl;
    std::future<int> result = std::async(std::launch::deferred, mythread, 37);
    std::cout << "continue ......" << std::endl;
    
    // wait（）等待一定时间，阻塞
    std::future_status status = result.wait_for(std::chrono::seconds(4));      // 等待 1 秒
    if (status == std::future_status::timeout) {       // 超时：我想等你 1 秒，希望你返回，若没有返回，则status == timeout
        // 表示线程还没执行完毕
        std::cout << "超时， 线程还没执行完毕" << std::endl;
    } else if (status == std::future_status::ready) {
        std::cout << "线程执行完毕，返回" << std::endl;
        std::cout << "线程返回值：" << result.get() << std::endl;
    } else if (status == std::future_status::deferred) {
        // 如果async的第一个参数被设置为deferred，则会进入本分支
        std::cout << "线程延迟执行" << std::endl;
        std::cout << "线程返回值： " << result.get() << std::endl;
    }*/
    
    /*std::cout << "main thread id = " << std::this_thread::get_id()  << std::endl;
    std::packaged_task<int(int)> mypt(mythread);
    std::thread t1(std::ref(mypt), 10);
    t1.join();
    
    std::future<int> result = mypt.get_future();
    //std::shared_future<int> result_s(std::move(result));
    std::shared_future<int> result_s(result.share());
    bool canget = result.valid();      //  false，因为已经转移给shared_future了
    auto mythreadresult = result_s.get();         // shared_future 的 get（）是复制，可在多个线程中get
    
    //std::shared_future<int> result_s(mypt.get_future());
    
    //std::thread t2(mythread2, std::ref(result));
    std::thread t2(mythread2, std::ref(result_s));
    t2.join();
    
    
    std::cout << "main thread over " << std::endl;*/
    
    
    // 五：原子操作 std::atomic
    // 3.1 原子操作概念的引出范例
    // 大家可以把原子操作理解成不需要用到互斥量加锁（无锁）技术的多线程并发编程方式
    // 也可以理解成：原子操作是在多线程中不会被打断的程序执行片段， 比互斥量效率更高
    // 互斥量的加锁一般针对一个代码段（几行代码），而原子操作针对一个变量，不是一个代码段
    // 原子操作是“不可分割操作”，即操作状态要么完成，要么未完成
    
    // std::atomic代表原子操作，是个类模版，用来封装某个类型的值的
    
    
    // 3.2 基本用法范例
    return 0;
}
