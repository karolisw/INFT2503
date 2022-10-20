#include <boost/asio.hpp>
#include <iostream>

using namespace std;
using namespace boost::asio::ip;

class WebServer {

private:
  class Connection {
  public:
    tcp::socket socket;
    Connection(boost::asio::io_service &io_service) : socket(io_service) {}
  };

  boost::asio::io_service io_service;

  tcp::endpoint endpoint;
  tcp::acceptor acceptor;

  void handle_request(shared_ptr<Connection> connection) {
    auto read_buffer = make_shared<boost::asio::streambuf>();
    
    // Read from client until newline ("\r\n")
    async_read_until(connection->socket, *read_buffer, "\r\n",
                     [this, connection, read_buffer](const boost::system::error_code &ec, size_t) {

      // If ec is a reference to a nullpointer (i think)
      if (!ec) 
      {
        // Retrieve message from client as string:
        istream read_stream(read_buffer.get());

        // This will be the request
        string message;
        getline(read_stream, message);
        message.pop_back(); // Remove "\r" at the end of message

        // Close connection when "exit" is retrieved from client
        if (message == "exit")
          return;

        cout << "Message from a connected client: " << message << endl;

        auto write_buffer = make_shared<boost::asio::streambuf>();

        // The write stream will be from the server to the client
        ostream write_stream(write_buffer.get());

        string html = "";
        string ok_msg = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: ";

        // If the message/request string contains
        if (message.find("GET / HTTP/1.1") != message.npos) {
            html = "<h1>Dette er hovedsiden</h1>";
            write_stream << ok_msg << html.size() << "\r\n\r\n" << html;
        }
        else if (message.find("GET /en_side HTTP/1.1") != message.npos) {
            html = "<h1>Dette er en side</h1>";
            write_stream << ok_msg << html.size() << "\r\n\r\n" << html;
        }
        else {
            html = "<h1>404 Not found</h1>";
            write_stream << "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length: " <<
            html.size() << "\r\n\r\n" << html;
        }

        // Write to client
        async_write(connection->socket, *write_buffer,
                    [this, connection, write_buffer](const boost::system::error_code &ec, size_t) {
          // If not error:
          if (!ec)
            handle_request(connection);
        });
      }
    });
  }

  void accept() {
    // The (client) connection is added to the lambda parameter and handle_request
    // in order to keep the object alive for as long as it is needed.
    auto connection = make_shared<Connection>(io_service);
    
    // Accepts a new (client) connection. On connection, immediately start accepting a new connection 
    acceptor.async_accept(connection->socket, [this, connection](const boost::system::error_code &ec) {
      accept();
      // If not error:
      if (!ec) {
        handle_request(connection);
      }
    });
  }

public:
  WebServer() : endpoint(tcp::v4(), 8080), acceptor(io_service, endpoint) {}

  void start() {
    accept();

    io_service.run();
  }
};

int main() {
  WebServer echo_server;

  cout << "Starting web server" << endl
       << "Connect in a terminal with: telnet localhost 8080." << endl;

  echo_server.start();
}
