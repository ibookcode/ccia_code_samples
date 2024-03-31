#include <thread>
#include <utility>
#include <stdexcept>

// The example is similar to listing 2.3, but the new thread is passed in directly to scoped_thread 
// rather than having to create a separate named variable for it.
class scoped_thread
{
    std::thread t;
public:
    // The move support of std::thread avoids any unpleasant consequences should the thread_guard object outlive the thread it was referencing, 
    // and it also means that no one else can join or detach the thread once ownership has been transferred into the object.
    explicit scoped_thread(std::thread t_):
        t(std::move(t_))
    {
        if(!t.joinable())
            throw std::logic_error("No thread");
    }
    ~scoped_thread()
    {
        t.join();
    }
    scoped_thread(scoped_thread const&)=delete;
    scoped_thread& operator=(scoped_thread const&)=delete;
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

void f()
{
    int some_local_state;
    scoped_thread t(std::thread(func(some_local_state)));
        
    do_something_in_current_thread();
}

int main()
{
    f();
}
