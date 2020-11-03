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
#include <mutex>

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


/* ***    third lesson & fourth lesson
 


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
            
            {     // 加打括号，提前释放mutex，使得后面的操作不被锁
            //std::lock_guard<std::mutex> guard(my_mutex1);                    // lock_guard原理：局部变量guard，构造时lock（），析构时unlock（）
            my_mutex1.lock();                  // 先锁1，再锁2， 一定要顺序不同
            my_mutex2.lock();
            msgRecvQueue.push_back(i);
            my_mutex2.unlock();
            my_mutex1.unlock();
            }
            
            // 操作数据。。。。。。
        }
    }
    
    // 从消息队列中取数据的线程
    void outMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            my_mutex2.lock();                 // 先锁2， 再锁1，一定要顺序不同
            my_mutex1.lock();
            if (!msgRecvQueue.empty()) {
                std::cout << "取出数据 " << msgRecvQueue.front() << std::endl;
                msgRecvQueue.pop_front();
                my_mutex1.unlock();      // 分支一 解锁
                my_mutex2.unlock();
            } else {
                std::cout << "消息队列 空 " << std::endl;
                my_mutex1.unlock();      // 分支二 解锁
                my_mutex2.unlock();
            }
        }
    }
private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex1;
    std::mutex my_mutex2;
};

int main(int argc, const char * argv[]) {

    std::vector<int> g_v = {1, 2, 3};
    
    // 一：创建和等待多个线程
    // a) 多个线程执行顺序是乱的，和操作系统的调度机制有关
    // b）如下写法，主线程等待所有子线程结束再结束
    // c）用容器管理线程，对一次性创建大量线程并管理有利
    //std::vector<std::thread> mythreads;
    //for (int i = 0; i < 10; ++i) {
        //mythreads.emplace_back(std::thread(myprint, i));      // 创建10个线程，同时这10个线程已经开始执行
    //}
    
    //for (auto iter = mythreads.begin(); iter != mythreads.end(); ++iter) {
        //iter->join();
    //}
    
    
    // 二：数据共享问题
    // 2.1 只读数据是安全的
    // 2.2 有读有写，不经处理程序崩溃
    
    // 三：共享数据的保护案例代码
    // 网络游戏服务器 创建两个线程，一个线程收集玩家命令，存入队列， 另一个线程从队列取出命令做处理
    // 准备用成员函数作为线程函数的方法来写
    // 引入保护共享数据问题的第一个概念“互斥量”
    
    // 第四课：互斥量
    // 一：互斥量是个类对象，理解成一把锁，多个线程尝试用lock（）成员函数来加锁，只有一个线程能锁定成功（成功的标志是lock（）返回了）
    // 如果没有锁成功，流程卡在lock（）这不断尝试加锁
    
    // 二：互斥量的用法
    // 2.1 先lock（）共享数据，操作数据，再unlock（）
    // lock（）和unlock（）成对出现,所有分支都要解锁
    
    // 2.2 为了防止unlock（），引入一个std：：lock_guard<>的类模版：自己unlock（）
    // lock_guard<>直接取代lock（）和unlock（），不能再使用lock（）和unlock（）
    
    // 三：死锁
    // 3.1 死锁的产生至少要有两个互斥量
    // 情形：某一操作要lock 金锁 和 银锁 才能执行
    // 线程A执行，先锁 金锁 ，然后lock 银锁。。。
    // 上下文切换
    // 线程B执行，先锁 银锁 ，然后lock 金锁。。。
    // 此时发生死锁
    
    // 3.2 死锁的一般解决方案
    // 保证两个互斥量上锁顺序一致，用lock（）或lock_guard都要保持顺序一致
    
    // 3.3 std::lock()函数模版：处理多个互斥量时使用（两个或以上，一个不能使用）
    // 不存在多个线程中因为多个锁的上锁顺序导致的死锁
    // 原理：如果锁住一个，另一个没锁住，则释放已锁住的锁，过段时间在尝试上锁
    // 使用：上锁时，std::lock(mutex1, mutex2);
    //      解锁时，unlock(mutex1); unlock(mutex2);         unlock()需要手动调用
    
    // 3.4 std::lock_guard<> 的 std::adopt_lock 参数：结合使用std::lock（）和 std::lock_guard<>, 而不用手动调用unlock（）
    // 使用： std::lock(mutex1, mutex2);
    //       std::lock_guard<std::mutex> guard1(mutex1, std::adopt_lock);      std::adopt_lock使得构造时不调用 lock（）
    //       std::lock_guard<std::mutex> guard2(mutex2, std::adopt_lock);
    
    A myobj;
    std::thread inMsgThread(&A::inMsgRecvQueue, std::ref(myobj));   //使用std::ref()能真正传递引用
    std::thread outMsgThread(&A::outMsgRecvQueue, std::ref(myobj));
    inMsgThread.join();
    outMsgThread.join();
    
    
    
    std::cout << "main thread end " << std::endl;
}
 */


//*       fifth lesson:   mutex.lock() （mutex的加锁） -> lock_guar<> (自动上下锁) -> std::lock()（多个mutex的避免死锁的加锁）  -> unique_lock()

class A {
public:
    // 收到的命令如队列的线程
    void inMsgRecvQueue() {
        for (int i = 0; i < 1000; ++i) {
            std::cout << "插入命令 " << i << std::endl;
            
            
            std::unique_lock<std::mutex> guard(my_mutex, std::try_to_lock);
            if (guard.owns_lock()) {
                msgRecvQueue.push_back(i);
            } else {
                std::cout << "没拿到锁， 干点别的事" << std::endl;
            }
            
            
            // 操作数据。。。。。。
        }
    }
    
    // 从消息队列中取数据的线程
    void outMsgRecvQueue() {
        
        std::unique_lock<std::mutex> guard(my_mutex);
        std::chrono::milliseconds dura(20000);
        std::this_thread::sleep_for(dura);
      
            if (!msgRecvQueue.empty()) {
                std::cout << "取出数据 " << msgRecvQueue.front() << std::endl;
                msgRecvQueue.pop_front();
            } else {
                std::cout << "消息队列 空 " << std::endl;
            }
        
    }
private:
    std::list<int> msgRecvQueue;
    std::mutex my_mutex;
};

int main(int argc, char *argv[]) {
    
    // 一： unique_lock()取代lock_guard
    // unique_lock()是个类模版， 工作中，一般用lock_guard
    // unique_lock比lock_guard更灵活，但效率要低，内存占用要高
    
    // 二：unique_lock 的第二个参数
    
    // 2.1 std::adopt_lock : 表示这个互斥量已经被lock了，构造时不需要再被lock，若互斥量在之前没有被lock却使用该参数，则出错报异常
    // 所以使用前提是自己要提前lock（）
    
    // 2.2 std::try_to_lock : 尝试用mutex的lock（）去上锁，但如果没有锁定成功，则会立即返回，并不会阻塞在那里
    // 使用std::try_to_lock的前提是自己不能先去lock（）
    
    // 2。3 std::defer_lock: 使用前提是自己不能先lock（），否则报异常
    // std::defer_lock的含义并没有给mutex加锁：初始化一个没有上锁的mutex
    // 多与unique_lock的成员函数一块使用，体现unique_lock的灵活性
    
    // 三：unique_lock的成员函数
    // 3.1 lock（）：随时加锁，操作共享数据
    // 3.2 unlock（）：随时解锁，操作非共享数据， 体现灵活性
    // 3.3 try_lock() : 尝试给互斥量加锁，如果拿到锁，返回true，否则返回false。该函数不阻塞
    // 3.4 release（）：返回它所管理的mutex对象，并释放所有权，unique_lock和mutex不再有关系
    
    // 锁住的代码多少称为锁的 粒度
    
    // 四： unique_lock 所有权的传递
    // std::unique_lock<std::mutex> guard1(my_mutex);  guard 拥有 my_mutex的所有权
    
    // 所有权的转移方法
    // 4.1 ：std::move()
    // std::unique_lock<std::mutex> guard2(std::move(guard1));
    
    // 4.2 : 返回值
    // return std::unique_lock<std::mutex> ;
    
    
    A myobj;
    std::thread outMsgThread(&A::inMsgRecvQueue, std::ref(myobj));   //使用std::ref()能真正传递引用
    std::thread inMsgThread(&A::outMsgRecvQueue, std::ref(myobj));
    inMsgThread.join();
    outMsgThread.join();
}
 
// */
