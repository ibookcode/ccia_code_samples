#include <string>
#include <vector>
#include <future>

// Listing 4.8 Partial class definition for a specialization of std::packaged_task< >
template<>
class packaged_task<std::string(std::vector<char>*,int)>
{
public:
    template<typename Callable>
    explicit packaged_task(Callable&& f);
    std::future<std::string> get_future();
    void operator()(std::vector<char>*,int);
};
