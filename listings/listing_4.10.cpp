#include <future>

class connection_set  {
};

// Listing 4.10 Handling multiple connections from a single thread using promises
void process_connections(connection_set& connections)
{
    // 1.The process_connections() function loops until done() returns true
    while(!done(connections))
    {
        // 2.Every time it goes through the loop, it checks each connection in turn
        for(connection_iterator connection=connections.begin(),end=connections.end();connection!=end;++connection)
        {
            // 3.retrieving incoming data if there is any 
            if(connection->has_incoming_data())
            {
                // an incoming packet has an ID and a payload with the data in it.
                data_packet data=connection->incoming();
                // 4.The ID is mapped to a std::promise, and the value is set to the packet’s payload.
                std::promise<payload_type>& p=
                    connection->get_promise(data.id);
                p.set_value(data.payload);
            }
            // 5.sending any queued outgoing data
            if(connection->has_outgoing_data())
            {
                // For outgoing packets, the packet is retrieved from the outgoing queue and sent through the connection.
                outgoing_packet data=
                    connection->top_of_outgoing_queue();
                connection->send(data.payload);
                // 6.Once the send has completed, the promise associated with the outgoing data 
                // is set to true to indicate successful transmission
                data.promise.set_value(true);
            }
        }
    }
}
