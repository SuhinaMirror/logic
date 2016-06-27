#include "websockets/server_ws.hpp"

using namespace std;

typedef SimpleWeb::SocketServer<SimpleWeb::WS> WsServer;

int main()
{
    //WebSocket (WS)-server at port 8080 using 4 threads
    WsServer server(8080, 4);
    
    auto& echo = server.endpoint["^/echo/?$"];
    
    echo.onmessage = [&server](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message)
    {
        auto message_str = message->string();
        
        cout << "Server: Message received: \"" << message_str << "\" from " << (size_t)connection.get() << endl;        
        cout << "Server: Sending message \"" << message_str <<  "\" to " << (size_t)connection.get() << endl;
        
        auto send_stream = make_shared<WsServer::SendStream>();
        *send_stream << message_str;
        
        server.send(connection, send_stream, [](const boost::system::error_code& ec)
        {
            if(ec)
            {
                cout << "Server: Error sending message. " <<
                //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
                "Error: " << ec << ", error message: " << ec.message() << endl;
            }
        });
    };
    
    echo.onopen = [](shared_ptr<WsServer::Connection> connection)
    {
        cout << "Server: Opened connection " << (size_t)connection.get() << endl;
    };
    
    //See RFC 6455 7.4.1. for status codes
    echo.onclose = [](shared_ptr<WsServer::Connection> connection, int status, const string& /*reason*/)
    {
        cout << "Server: Closed connection " << (size_t)connection.get() << " with status code " << status << endl;
    };
    
    //See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    echo.onerror = [](shared_ptr<WsServer::Connection> connection, const boost::system::error_code& ec)
    {
        cout << "Server: Error in connection " << (size_t)connection.get() << ". " << 
        "Error: " << ec << ", error message: " << ec.message() << endl;
    };
    
    thread server_thread([&server]()
    {
        server.start();
    });
    server_thread.join();

    return 0;
}
