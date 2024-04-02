#include <memory>
template<typename T>
class threadsafe_queue
{
public:
    threadsafe_queue();
    threadsafe_queue(const threadsafe_queue&);
    // Disallow assignment for simplicity.
    threadsafe_queue& operator=(const threadsafe_queue&) = delete;

    void push(T new_value);
    
    // 1.The first overload of try_pop() stores the retrieved value in the referenced variable, 
    // so it can use the return value for status; 
    // it returns true if it retrieved a value and false otherwise
    bool try_pop(T& value);
    // 2.The second overload can’t do this, because it returns the retrieved value directly.
    std::shared_ptr<T> try_pop();

    void wait_and_pop(T& value);
    std::shared_ptr<T> wait_and_pop();

    bool empty() const;
};

int main()
{}
