#include <mutex>
#include <stdexcept>
#include <climits>

// Listing 3.8 A simple hierarchical mutex
class hierarchical_mutex
{
    std::mutex internal_mutex;
    unsigned long const hierarchy_value;
    unsigned long previous_hierarchy_value;
    // The thread_local value represents the hierarchy value for the current thread
    static thread_local unsigned long this_thread_hierarchy_value;

    void check_for_hierarchy_violation()
    {
        // The first time a thread locks an instance of hierarchical_mutex, the value of this_thread_hierarchy_value is ULONG_MAX. 
        // This is greater than any other value, so the check in check_for_hierarchy_violation() passes.
        if(this_thread_hierarchy_value <= hierarchy_value)
        {
            throw std::logic_error("mutex hierarchy violated");
        }
    }
    void update_hierarchy_value()
    {
        // Store this previous hierarchy value only when you hold the internal_mutex.
        previous_hierarchy_value=this_thread_hierarchy_value;
        this_thread_hierarchy_value=hierarchy_value;
    }
public:
    explicit hierarchical_mutex(unsigned long value):
        hierarchy_value(value),
        previous_hierarchy_value(0)
    {}
    void lock()
    {
        check_for_hierarchy_violation();
        // lock() delegates to the internal mutex for the locking.
        internal_mutex.lock();
        // Once this lock has succeeded, you can update the hierarchy value.
        update_hierarchy_value();
    }
    void unlock()
    {
        // You throw error if the mutex being unlocked is not the most recently locked one.
        if(this_thread_hierarchy_value!=hierarchy_value)
            throw std::logic_error("mutex hierarchy violated");
        // Restore previous hierarchy value before you unlock the internal mutex
        this_thread_hierarchy_value=previous_hierarchy_value;
        internal_mutex.unlock();
    }
    // If the call to try_lock() on the internal_mutex fails, then you don’t own the lock, 
    // so you don’t update the hierarchy value, and return false rather than true.
    bool try_lock()
    {
        check_for_hierarchy_violation();
        if(!internal_mutex.try_lock())
            return false;
        update_hierarchy_value();
        return true;
    }
};

// this_thread_hierarchy_value is initialized to the maximum value, so initially any mutex can be locked.
thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

int main()
{
    hierarchical_mutex m1(42);
    hierarchical_mutex m2(2000);
    
}
