#include <future>

// Listing 4.14 A sample implementation of spawn_task
template<typename F,typename A>
std::future<std::result_of<F(A&&)>::type>
spawn_task(F&& f,A&& a)
{
    typedef std::result_of<F(A&&)>::type result_type;
    // you’d create a std::packaged_task for the result of the function call, 
    // get the future from it, run it on a thread, and return the future.
    std::packaged_task<result_type(A&&)> task(std::move(f));
    std::future<result_type> res(task.get_future());
    std::thread t(std::move(task),std::move(a));
    t.detach();
    return res;
}
