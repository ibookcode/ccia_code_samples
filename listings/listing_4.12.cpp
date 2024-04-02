#include <list>
#include <algorithm>

// Listing 4.12 A sequential implementation of Quicksort
template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
    if(input.empty())
    {
        return input;
    }
    std::list<T> result;
    // 1.You take the first element as the pivot by slicing it off the front of the list using splice()
    result.splice(result.begin(),input,input.begin());
    // 2.let’s take a reference to it to avoid copying
    T const& pivot=*result.begin();
    // 3.You can then use std::partition to divide the sequence into those values 
    // less than the pivot and those not less than the pivot.
    // The lambda function use a reference capture to avoid copying the pivot value
    auto divide_point=std::partition(input.begin(),input.end(),
        [&](T const& t){return t<pivot;});

    // You’re going to use recursion to sort the two “halves,” you’ll need to create two lists.
    std::list<T> lower_part;
    // 4.You can do this by using splice() again to move the values from input up to the divide_point into a new list: lower_part.
    lower_part.splice(lower_part.end(),input,input.begin(),
        divide_point);
    // 5.You can then sort the two lists with recursive calls
    auto new_lower(
        sequential_quick_sort(std::move(lower_part)));
    auto new_higher(
        sequential_quick_sort(std::move(input)));
    // 6.Finally, you can use splice() yet again to piece the result together in the right order. 
    // The new_higher values go on the end, after the pivot.
    result.splice(result.end(),new_higher);
    // 7.the new_lower values go at the beginning, before the pivot.
    result.splice(result.begin(),new_lower);
    return result;
}

