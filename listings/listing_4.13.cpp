#include <list>
#include <algorithm>
#include <future>

// Listing 4.13 Parallel Quicksort using futures
template<typename T>
std::list<T> parallel_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    std::list<T> result;
    result.splice(result.begin(),input,input.begin());
    T const& pivot=*result.begin();
    auto divide_point=std::partition(input.begin(),input.end(),
        [&](T const& t){return t<pivot;});
    std::list<T> lower_part;
    lower_part.splice(lower_part.end(),input,input.begin(),
        divide_point);

    // 1.The big change here is that rather than sorting the lower portion on the current thread, 
    // you sort it on another thread using std::async()
    std::future<std::list<T> > new_lower(
        std::async(&parallel_quick_sort<T>,std::move(lower_part)));
    // 2.The upper portion of the list is sorted with direct recursion as before
    auto new_higher(
        parallel_quick_sort(std::move(input)));
    // 3.Because you just used direct recursion to get new_higher, you can splice it into place as before
    result.splice(result.end(),new_higher);
    // 4.But new_lower is now std::future<std::list<T>> rather than a list, 
    // so you need to call get() to retrieve the value before you can call splice()
    result.splice(result.begin(),new_lower.get());
    return result;
}
