/*
Crie um servidor FTP com C++ para o compartilhamento de dados na
máquina em que o código é executado."
*/
/*
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void handle_client(tcp::socket &socket)
{
    try
    {
        boost::system::error_code error;
        boost::asio::streambuf buffer;
        std::ostream response_stream(&buffer);
        response_stream << "220 Welcome to the FTP server\r\n";
        boost::asio::write(socket, buffer, error);

        while (true)
        {
            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, "\r\n", error);
            if (error)
                break;

            std::istream request_stream(&request);
            std::string command;
            request_stream >> command;

            if (command == "QUIT")
            {
                response_stream << "221 Goodbye\r\n";
                boost::asio::write(socket, buffer, error);
                break;
            }
            else if (command == "USER" || command == "PASS")
            {
                response_stream << "230 Logged in\r\n";
            }
            else if (command == "LIST")
            {
                response_stream << "150 Here comes the directory listing\r\n";
                // Add directory listing logic here
                response_stream << "226 Directory send OK\r\n";
            }
            else
            {
                response_stream << "502 Command not implemented\r\n";
            }
            boost::asio::write(socket, buffer, error);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 21));

        while (true)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handle_client, std::ref(socket)).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
} */

#include <iostream>
#include <boost/asio.hpp>
#include <fstream>
#include <filesystem>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

void handle_client(tcp::socket &socket)
{
    try
    {
        boost::system::error_code error;
        boost::asio::streambuf buffer;
        std::ostream response_stream(&buffer);
        response_stream << "220 Welcome to the FTP server\r\n";
        boost::asio::write(socket, buffer, error);

        while (true)
        {
            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, "\r\n", error);
            if (error)
                break;

            std::istream request_stream(&request);
            std::string command;
            request_stream >> command;

            if (command == "QUIT")
            {
                response_stream << "221 Goodbye\r\n";
                boost::asio::write(socket, buffer, error);
                break;
            }
            else if (command == "USER" || command == "PASS")
            {
                response_stream << "230 Logged in\r\n";
            }
            else if (command == "LIST")
            {
                response_stream << "150 Here comes the directory listing\r\n";
                for (const auto &entry : fs::directory_iterator(fs::current_path()))
                {
                    response_stream << entry.path().filename().string() << "\r\n";
                }
                response_stream << "226 Directory send OK\r\n";
            }
            else if (command == "RETR")
            {
                std::string filename;
                request_stream >> filename;
                std::ifstream file(filename, std::ios::binary);
                if (file)
                {
                    response_stream << "150 Opening binary mode data connection for " << filename << "\r\n";
                    boost::asio::write(socket, buffer, error);
                    char buf[512];
                    while (file.read(buf, sizeof(buf)).gcount() > 0)
                    {
                        boost::asio::write(socket, boost::asio::buffer(buf, file.gcount()), error);
                    }
                    response_stream << "226 Transfer complete\r\n";
                }
                else
                {
                    response_stream << "550 File not found\r\n";
                }
            }
            else if (command == "STOR")
            {
                std::string filename;
                request_stream >> filename;
                std::ofstream file(filename, std::ios::binary);
                if (file)
                {
                    response_stream << "150 Opening binary mode data connection for " << filename << "\r\n";
                    boost::asio::write(socket, buffer, error);
                    char buf[512];
                    size_t len;
                    while ((len = socket.read_some(boost::asio::buffer(buf), error)) > 0)
                    {
                        file.write(buf, len);
                    }
                    response_stream << "226 Transfer complete\r\n";
                }
                else
                {
                    response_stream << "550 Cannot create file\r\n";
                }
            }
            else if (command == "CWD")
            {
                std::string path;
                request_stream >> path;
                if (fs::exists(path) && fs::is_directory(path))
                {
                    fs::current_path(path);
                    response_stream << "250 Directory successfully changed\r\n";
                }
                else
                {
                    response_stream << "550 Failed to change directory\r\n";
                }
            }
            else
            {
                response_stream << "502 Command not implemented\r\n";
            }
            boost::asio::write(socket, buffer, error);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}

int main()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 21));

        while (true)
        {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            std::thread(handle_client, std::ref(socket)).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}