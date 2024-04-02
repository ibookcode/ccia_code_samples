#include <string>
#include <future>

// Listing 4.7 Passing arguments to a function with std::async
struct X
{
    void foo(int,std::string const&);
    std::string bar(std::string const&);
};


X x;
// Calls p->foo(42,"hello") where p is &x
auto f1=std::async(&X::foo,&x,42,"hello");
// Calls tmpx.bar("goodbye") where tmpx is a copy of x
auto f2=std::async(&X::bar,x,"goodbye");

struct Y
{
    double operator()(double);
};

Y y;
// Calls tmpy(3.141) where tmpy is move-constructed from Y()
auto f3=std::async(Y(),3.141);
// Calls y(2.718)
auto f4=std::async(std::ref(y),2.718);

X baz(X&);
// Calls baz(x)
auto f6=std::async(baz,std::ref(x));

class move_only
{
public:
    move_only();
    move_only(move_only&&);
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&);
    move_only& operator=(move_only const&) = delete;
    void operator()();
};
// Calls tmp() where tmp is constructed from std::move(move_only())
auto f5=std::async(move_only());

// Run in new thread
auto f6=std::async(std::launch::async,Y(),1.2);
// Run in wait() or get()
auto f7=std::async(std::launch::deferred,baz,std::ref(x));
// Implementation chooses
auto f8=std::async(
    std::launch::deferred | std::launch::async,
    baz,std::ref(x));
auto f9=std::async(baz,std::ref(x));
// Invoke deferred function
f7.wait();
