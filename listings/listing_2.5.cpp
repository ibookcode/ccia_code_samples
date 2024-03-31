#include <thread>

void some_function()
{}

void some_other_function(int)
{}

// Listing 2.5 Returning a std::thread from a function
std::thread f()
{
    void some_function();
    return std::thread(some_function);
}
std::thread g()
{
    void some_other_function(int);
    std::thread t(some_other_function,42);
    return t;
}

// If ownership should be transferred into a function, 
// it can accept an instance of std::thread by value as one of the parameters
void f1(std::thread t);
void g1()
{
    void some_function();
    f1(std::thread(some_function));
    std::thread t(some_function);
    f1(std::move(t));
}

int main()
{
    std::thread t1=f();
    t1.join();
    std::thread t2=g();
    t2.join();
}
