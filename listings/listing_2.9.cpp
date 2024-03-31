#include <thread>
#include <numeric>
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

// Listing 2.9 A naïve parallel version of std::accumulate
template<typename Iterator,typename T>
struct accumulate_block
{
    void operator()(Iterator first,Iterator last,T& result)
    {
        result=std::accumulate(first,last,result);
    }
};

template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{
    unsigned long const length=std::distance(first,last);

    // If the input range is empty, you return the initial value supplied as the init parameter value.
    if(!length)
        return init;

    unsigned long const min_per_thread=25;
    // there’s at least one element in the range, so you can divide the number of elements by the minimum block size 
    // in order to give the maximum number of threads.
    // This is to avoid creating 32 threads on a 32-core machine when you have only five values in the range.
    unsigned long const max_threads=
        (length+min_per_thread-1)/min_per_thread;

    unsigned long const hardware_threads=
        std::thread::hardware_concurrency();

    // The number of threads to run is the minimum of your calculated maximum and the number of hardware threads.
    unsigned long const num_threads=
        std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size=length/num_threads;

    // Now that you know how many threads you have, 
    // you can create a std::vector<T> for the intermediate results 
    // and a std::vector<std::thread> for the threads.
    std::vector<T> results(num_threads);
    // You need to launch one fewer thread than num_threads, because you already have one.
    std::vector<std::thread>  threads(num_threads-1);

    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);++i)
    {
        Iterator block_end=block_start;
        // advance the block_end iterator to the end of the current block
        std::advance(block_end,block_size);
        // launch a new thread to accumulate the results for this block
        threads[i]=std::thread(
            accumulate_block<Iterator,T>(),
            block_start,block_end,std::ref(results[i]));
        // The start of the next block is the end of this one.
        block_start=block_end;
    }
    // After you’ve launched all the threads, this thread can then process the final block.
    accumulate_block<Iterator,T>()(block_start,last,results[num_threads-1]);
    
    // Wait for all the threads you spawned with std::for_each
    //  and then add up the results with a final call to std::accumulate
    std::for_each(threads.begin(),threads.end(),
        std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(),results.end(),init);
}

int main()
{
    std::vector<int> vi;
    for(int i=0;i<10;++i)
    {
        vi.push_back(10);
    }
    int sum=parallel_accumulate(vi.begin(),vi.end(),5);
    std::cout<<"sum="<<sum<<std::endl;
}
