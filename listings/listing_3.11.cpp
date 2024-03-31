#include <memory>
#include <mutex>

struct some_resource
{
    void do_something()
    {}
    
};

// Listing 3.11 Thread-safe lazy initialization using a mutex
std::shared_ptr<some_resource> resource_ptr;
std::mutex resource_mutex;
void foo()
{
    // All threads are serialized here
    std::unique_lock<std::mutex> lk(resource_mutex);
    if(!resource_ptr)
    {
        // Only the initialization needs protection
        resource_ptr.reset(new some_resource);
    }
    lk.unlock();
    resource_ptr->do_something();
}

int main()
{
    foo();
}
