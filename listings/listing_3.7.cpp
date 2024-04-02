#include <mutex>

// Listing 3.7 Using a lock hierarchy to prevent deadlock
class hierarchical_mutex
{
public:
    explicit hierarchical_mutex(unsigned level)
    {}
    
    void lock()
    {}
    void unlock()
    {}
};

// 1.This code has three instances of hierarchical_mutex
hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);
hierarchical_mutex other_mutex(6000);

int do_low_level_stuff()
{
    return 42;
}


int low_level_func()
{
    // 2.Assuming do_low_level_stuff doesn’t lock any mutexes,
    // low_level_func is the bottom of your hierarchy, and locks the low_level_mutex
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_param)
{}


void high_level_func()
{
    // 3.high_level_func calls low_level_func, 
    // 4.while holding a lock on high_level_mutex
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
}

// The hierarchy level of high_level_mutex (10000) is higher than that of low_level_mutex (5000).
// 5.thread_a() abides by the rules, so it runs fine.
void thread_a()
{
    high_level_func();
}


void do_other_stuff()
{}


void other_stuff()
{
    // 8.When other_stuff() calls high_level_func(), it’s violating the hierarchy: 
    // high_level_func() tries to acquire the high_level_mutex, which has a value of 10000, 
    // considerably more than the current hierarchy value of 6000.
    // The hierarchical_mutex will therefore report an error
    high_level_func();
    do_other_stuff();
}

// 6.thread_b() disregards the rules and therefore will fail at runtime.
void thread_b()
{
    // 7.First off, it locks other_mutex, which has a hierarchy value of only 6000
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

int main()
{}
