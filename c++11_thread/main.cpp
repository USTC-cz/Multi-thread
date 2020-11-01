//
//  main.cpp
//  c++11_thread
//
//  Created by chow Choi on 2020/10/29.
//

#include <iostream>
#include <vector>
#include <list>
#include <thread>

/*  first lesson
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
*/  //first lesson


/************************************************/

/* second lesson
 
void myprint(const int &i, char *buf) {
    std::cout << "thread id = " << std::this_thread::get_id() << std::endl;
    std::cout << "const int i = " << i << std::endl;     // 实际传引用是值传递，是安全的，但不建议用
    std::cout << "char *buf = " << buf << std::endl;    // 指针在detach（）子线程时，会有问题
}


int main(int argc, const char * argv[]) {
    // 一：传递临时变量作为线程参数
    // 1.1 要避免的陷阱
    // 避免主线程的临时变量在还没detach时就析构了，导致传入子线程的参数发生问题，主要是指针。
    int mvar = 1;
    int &mvarref = mvar;
    char buf[] = "this is a test ";
    std::thread myobj1(myprint, mvarref, buf);  // buf传递可能有问题，如果被提前析构。
    myobj1.detach();
    
    // 1.2 总结
    // a）传递int等简单类型，用值传递，避免用引用。
    // b）传递累对象，避免隐式类型转换。在创建线程时就构建出临时对象，并且函数参数应该是引用形式（避免又一次的构造）
    // 子线程函数 ： void myprint(int i, std::string &buf) {}
    // 创建线程： std::thread th(myprint, i, std::string(buf));  (创建临时对象和给子线程函数参数赋值会调用两次类的构造函数，若子线程函数参数不是引用，则又会调用一次类的构造函数）
    // 这是初步认识，其实可以用 std::ref() 传真正的引用参数
    
    
    // 二：临时对象作为线程参数继续讲
    // 2。1 线程id ： id是个数字，不同线程（主线程和子线程）的id不同
    // 线程id 可用 std::this_thread::get_id() 获取
    
    // 三：传递类对象、智能指针作为线程参数
    // std::ref(Obj) 可给线程传递真正的对象的引用，不用像上面例子中需要先创建临时对象以及多次的对象拷贝构造，但是在detach（）且在主线程先结束释放时不安全
    // std::move() 传递智能指针
    
    // 四：用成员函数指针作为线程参数
    std::cout << "main thread over" << std::endl;
}
 
 
 //*/  // second lesson


//*     third lesson
 


// 线程入口函数，可以多个线程使用
void myprint(int num) {
    std::cout << "myprint thread start, num =  " << num << std::endl;
    std::cout << "myprint thread end, num = " << num << std::endl;
}

class A {
public:
    // 收到的命令如队列的线程
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            std::cout << "插入命令 " << i << std::endl;
            msgRecvQueue.push_back(i);
        }
    }
    
    // 从消息队列中取数据的线程
    void outMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            if (!msgRecvQueue.empty()) {
                std::cout << "取出数据 " << msgRecvQueue.front() << std::endl;
                msgRecvQueue.pop_front();
            } else {
                std::cout << "消息队列 空 " << std::endl;
            }
        }
    }
private:
    std::list<int> msgRecvQueue;
};

int main(int argc, const char * argv[]) {

    std::vector<int> g_v = {1, 2, 3};
    
    // 一：创建和等待多个线程
    // a) 多个线程执行顺序是乱的，和操作系统的调度机制有关
    // b）如下写法，主线程等待所有子线程结束再结束
    // c）用容器管理线程，对一次性创建大量线程并管理有利
    /*std::vector<std::thread> mythreads;
    for (int i = 0; i < 10; ++i) {
        mythreads.emplace_back(std::thread(myprint, i));      // 创建10个线程，同时这10个线程已经开始执行
    }
    
    for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
        iter->join();
    }*/
    
    
    // 二：数据共享问题
    // 2.1 只读数据是安全的
    // 2.2 有读有写，不经处理程序崩溃
    
    // 三：共享数据的保护案例代码
    // 网络游戏服务器 创建两个线程，一个线程收集玩家命令，存入队列， 另一个线程从队列取出命令做处理
    // 准备用成员函数作为线程函数的方法来写
    // 引入保护共享数据问题的第一个概念“互斥量”
    
    A myobj;
    std::thread inMsgThread(&A::inMsgRecvQueue, std::ref(myobj));   //使用std::ref()能真正传递引用
    std::thread outMsgThread(&A::outMsgRecvQueue, std::ref(myobj));
    inMsgThread.join();
    outMsgThread.join();
    
    
    
    std::cout << "main thread end " << std::endl;
}
 
 //*/
