#include <mutex>

// Listing 3.10 Locking one mutex at a time in a comparison operator
class Y
{
private:
    int some_detail;
    mutable std::mutex m;

    int get_detail() const
    {
        std::lock_guard<std::mutex> lock_a(m);
        return some_detail;
    }
public:
    Y(int sd):some_detail(sd){}

    friend bool operator==(Y const& lhs, Y const& rhs)
    {
        if(&lhs==&rhs)
            return true;
        // The comparison operator first retrieves the values to be compared by calling the get_detail() member function
        int const lhs_value=lhs.get_detail();
        int const rhs_value=rhs.get_detail();
        // The comparison operator then compares the retrieved values
        return lhs_value==rhs_value;
    }
};

int main()
{}
