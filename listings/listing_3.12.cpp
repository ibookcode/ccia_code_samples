#include <mutex>

struct connection_info
{};

struct data_packet
{};

struct connection_handle
{
    void send_data(data_packet const&)
    {}
    data_packet receive_data()
    {
        return data_packet();
    }
};

struct remote_connection_manager
{
    connection_handle open(connection_info const&)
    {
        return connection_handle();
    }
} connection_manager;


// Listing 3.12 Thread-safe lazy initialization of a class member using std::call_once
class X
{
private:
    connection_info connection_details;
    connection_handle connection;
    std::once_flag connection_init_flag;

    // The use of the open_connection() member function to initialize the data also requires that the this pointer be passed in.
    void open_connection()
    {
        connection=connection_manager.open(connection_details);
    }
public:
    X(connection_info const& connection_details_):
        connection_details(connection_details_)
    {}
    // the initialization is done either by the first call to send_data(), or by the first call to receive_data()
    void send_data(data_packet const& data)
    {
        std::call_once(connection_init_flag,&X::open_connection,this);
        connection.send_data(data);
    }
    data_packet receive_data()
    {
        std::call_once(connection_init_flag,&X::open_connection,this);
        return connection.receive_data();
    }
};

int main()
{}
