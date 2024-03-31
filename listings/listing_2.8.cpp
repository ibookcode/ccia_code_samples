#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

// Listing 2.8 Spawns some threads and waits for them to finish
void do_work(unsigned id)
{}

void f()
{
    std::vector<std::thread> threads;
    for(unsigned i=0;i<20;++i)
    {
        // Spawns threads
        threads.push_back(std::thread(do_work,i));
    }
    // Calls join() on each thread in turn
    std::for_each(threads.begin(),threads.end(),
        std::mem_fn(&std::thread::join));
}

int main()
{
    f();
}
