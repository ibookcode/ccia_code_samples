#include <mutex>

// Listing 3.6 Using std::lock() and std::lock_guard in a swap operation
class some_big_object
{};

void swap(some_big_object& lhs,some_big_object& rhs)
{}

class X
{
private:
    some_big_object some_detail;
    mutable std::mutex m;
public:
    X(some_big_object const& sd):some_detail(sd){}

    friend void swap(X& lhs, X& rhs)
    {
        // First, the arguments are checked to ensure they are different instances
        if(&lhs==&rhs)
            return;
        // the call to std::lock() locks the two mutexes
        std::lock(lhs.m,rhs.m);
        // two std::lock_guard instances are constructed
        std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);
        std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);
        swap(lhs.some_detail,rhs.some_detail);
    }
};

int main()
{}
