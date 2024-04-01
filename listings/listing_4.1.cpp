#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>

bool more_data_to_prepare()
{
    return false;
}

struct data_chunk
{};

data_chunk prepare_data()
{
    return data_chunk();
}

void process(data_chunk&)
{}

bool is_last_chunk(data_chunk&)
{
    return true;
}

std::mutex mut;
// 1.you have a queue that’s used to pass the data between the two threads.
std::queue<data_chunk> data_queue;
std::condition_variable data_cond;

void data_preparation_thread()
{
    while(more_data_to_prepare())
    {
        data_chunk const data=prepare_data();
        {
            // 2.When the data is ready, the thread preparing the data locks the mutex protecting the queue using a std::lock_guard 
            // and pushes the data onto the queue
            std::lock_guard<std::mutex> lk(mut);
            data_queue.push(data);
        }
        // 3.It then calls the notify_one() member function on the std::condition_variable instance to notify the waiting thread 
        data_cond.notify_one();
    }
}

void data_processing_thread()
{
    while(true)
    {
        // 4.The processing thread first locks the mutex
        std::unique_lock<std::mutex> lk(mut);
        // 5.The thread then calls wait() on the std:: condition_variable,
        // passing in the lock object and a lambda function that expresses the condition being waited for.
        data_cond.wait(lk,[]{return !data_queue.empty();});
        data_chunk data=data_queue.front();
        data_queue.pop();
        // 6.The flexibility to unlock a std::unique_lock isn’t just used for the call to wait(); 
        // it’s also used once you have the data to process but before processing it
        lk.unlock();
        process(data);
        if(is_last_chunk(data))
            break;
    }
}

int main()
{
    std::thread t1(data_preparation_thread);
    std::thread t2(data_processing_thread);
    
    t1.join();
    t2.join();
}
