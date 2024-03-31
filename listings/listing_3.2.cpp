#include <mutex>

// Listing 3.2 Accidentally passing out a reference to protected data
class some_data
{
    int a;
    std::string b;
public:
    void do_something()
    {}
};

class data_wrapper
{
private:
    some_data data;
    std::mutex m;
public:
    template<typename Function>
    void process_data(Function func)
    {
        std::lock_guard<std::mutex> l(m);
        // Pass "protected" data to user-supplied function
        func(data);
    }
};

some_data* unprotected;

void malicious_function(some_data& protected_data)
{
    unprotected=&protected_data;
}

data_wrapper x;

void foo()
{
    // Pass in a malicious function to bypass the protection
    x.process_data(malicious_function);
    // Unprotected access to protected data
    unprotected->do_something();
}

int main()
{
    foo();
}
