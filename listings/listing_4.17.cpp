#include <experimental/future>

// Listing 4.17 A simple equivalent to std::async for Concurrency TS futures
template<typename Func>
std::experimental::future<decltype(std::declval<Func>()())>
spawn_async(Func&& func){
    std::experimental::promise<
        decltype(std::declval<Func>()())> p;
    // use std::experimental::promise to obtain a future, 
    // and then spawn a new thread running a lambda that sets the promise’s value to the return value of the supplied function
    auto res=p.get_future();
    std::thread t(
        [p=std::move(p),f=std::decay_t<Func>(func)]()
            mutable{
            try{
                p.set_value_at_thread_exit(f());
            } catch(...){
                p.set_exception_at_thread_exit(std::current_exception());
            }
    });
    t.detach();
    return res;
}
