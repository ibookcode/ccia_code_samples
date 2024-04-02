#include <string>

// Listing 4.15 A simple implementation of an ATM logic class
struct card_inserted
{
    std::string account;

};
class atm
{
    messaging::receiver incoming;
    messaging::sender bank;
    messaging::sender interface_hardware;
    void (atm::*state)();
    std::string account;
    std::string pin;
    // 1.The state functions are simple member functions of the atm class.
    void waiting_for_card()
    {
        // 2.The state function sends a message to the interface to display a “waiting for card” message
        interface_hardware.send(display_enter_card());
        // 3.and then waits for a message to handle
        incoming.wait()
            .handle<card_inserted>(
                // 4.The only type of message that can be handled here is a card_inserted message, which you handle with a lambda function
                [&](card_inserted const& msg)
                {
                    account=msg.account;
                    pin="";
                    interface_hardware.send(display_enter_pin());
                    state=&atm::getting_pin;
                }
                );
    }
    void getting_pin();
public:
    void run()
    {
        // 5.Execution starts with the run() member function, 
        // which sets the initial state to waiting_for_card
        state=&atm::waiting_for_card;
        try
        {
            for(;;)
            {
                // 6.and then repeatedly executes the member function representing the current state
                (this->*state)();
            }
        }
        catch(messaging::close_queue const&)
        {
        }
    }
};
