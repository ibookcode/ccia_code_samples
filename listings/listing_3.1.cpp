#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>

// Listing 3.1 Protecting a list with a mutex
// 1.There’s a single global variable
std::list<int> some_list;
// 2.It’s protected with a corresponding
global instance of std::mutex
std::mutex some_mutex;

void add_to_list(int new_value)
{
    // 3.The std::lock_guard locks the supplied mutex on construction and unlocks it on destruction
    std::lock_guard<std::mutex> guard(some_mutex);
    // C++17 has a new feature called class template argument deduction
    // std::lock_guard guard(some_mutex);
    // C++17 also introduces an enhanced version of lock guard
    // std::scoped_lock guard(some_mutex);
    some_list.push_back(new_value);
}
bool list_contains(int value_to_find)
{
    std::lock_guard<std::mutex> guard(some_mutex);
    return std::find(some_list.begin(),some_list.end(),value_to_find)
        != some_list.end();
}


int main()
{
    add_to_list(42);
    std::cout<<"contains(1)="<<list_contains(1)<<", contains(42)="<<list_contains(42)<<std::endl;
}
