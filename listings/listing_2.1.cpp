#include <thread>
#include <chrono>
#include <iostream>

void do_something(int& i)
{
    ++i;
}

// Listing 2.1 A function that returns while a thread still has access to local variables
struct func
{
    int& i;

    func(int& i_):i(i_){}

    void operator()()
    {
        for(unsigned j=0;j<1000000;++j)
        {
            do_something(i);
        }
        std::cout << "i = " << i << std::endl;
    }
};


void oops()
{
    int some_local_state=0;
    func my_func(some_local_state);
    // the new thread associated with my_thread will probably still be running when oops exits, 
    // because you’ve explicitly decided not to wait for it by calling detach().
    // oops退出时my_thread可能还在运行，这时调用do_something(i)可能会访问已经销毁的变量
    std::thread my_thread(my_func);
    my_thread.detach();
}

int main()
{
    oops();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1000ms);
}
