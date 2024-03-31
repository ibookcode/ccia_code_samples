#include <thread>

// Listing 2.3 Using RAII to wait for a thread to complete
class thread_guard
{
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_):
        t(t_)
    {}
    // Use the RAII idiom and provide a class that does the join() in its destructor
    ~thread_guard()
    {
        // join() can be called only once for a given thread of execution
        if(t.joinable())
        {
            t.join();
        }
    }
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

void do_something(int& i)
{
    ++i;
}

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
    }
};

void do_something_in_current_thread()
{}

// When the execution of the current thread reaches the end of f, the local objects are destroyed in reverse order of construction.
void f()
{
    int some_local_state;
    func my_func(some_local_state);
    std::thread t(my_func);
    thread_guard g(t);
        
    do_something_in_current_thread();
}

int main()
{
    f();
}
