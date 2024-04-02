#include <deque>
#include <mutex>
#include <future>
#include <thread>
#include <utility>

// Listing 4.9 Running code on a GUI thread using std::packaged_task
std::mutex m;
std::deque<std::packaged_task<void()> > tasks;

bool gui_shutdown_message_received();
void get_and_process_gui_message();

void gui_thread()
{
    // 1.the GUI thread loops until a message has been received telling the GUI to shut down
    while(!gui_shutdown_message_received())
    {
        // 2.repeatedly polling for GUI messages to handle
        get_and_process_gui_message();
        std::packaged_task<void()> task;
        {
            std::lock_guard<std::mutex> lk(m);
            // 3.If there are no tasks on the queue, it loops again
            if(tasks.empty())
                continue;
            // 4.otherwise it extracts the task from the queue
            task=std::move(tasks.front());
            tasks.pop_front();
        }
        // 5.then runs the task
        task();
    }
}

std::thread gui_bg_thread(gui_thread);

template<typename Func>
std::future<void> post_task_for_gui_thread(Func f)
{
    // 6.a new packaged task is created from the supplied function
    std::packaged_task<void()> task(f);
    // 7.the future is obtained from that task by calling the get_future() member function
    std::future<void> res=task.get_future();
    std::lock_guard<std::mutex> lk(m);
    // the task is put on the list before the future is returned to the caller
    tasks.push_back(std::move(task));
    return res;
}
