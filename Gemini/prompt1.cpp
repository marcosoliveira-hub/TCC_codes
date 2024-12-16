/*
Crie um servidor FTP com C++ para o compartilhamento de dados na
máquina em que o código é executado."
*/

/*

// PRIMEIRA VERSÃO

#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstddef>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

void handle_client(tcp::socket &socket)
{
    try
    {
        std::string data, command, argument;
        while (true)
        {
            boost::system::error_code error;
            size_t length = boost::asio::read(socket,
                                              boost::asio::buffer(data, 1024),
                                              error);

            if (error == error::eof)
                break; // Conexão encerrada pelo cliente

            // Extrair o comando e o argumento da linha recebida
            std::istringstream iss(data);
            iss >> command >> argument;

            if (command == "USER")
            {
                // Implementar a lógica de autenticação do usuário
                // ...
            }
            else if (command == "PASS")
            {
                // Implementar a lógica de verificação da senha
                // ...
            }
            else if (command == "LIST")
            {
                // Listar os arquivos e diretórios do diretório atual
                fs::path current_dir = "/path/to/your/ftp/root"; // Substituir pelo caminho desejado
                for (auto &p : fs::directory_iterator(current_dir))
                {
                    socket.write(boost::asio::buffer(p.path().string() + "\r\n"));
                }
                socket.write(boost::asio::buffer("226 Transfer complete.\r\n"));
            }
            else if (command == "RETR")
            {
                // Enviar um arquivo para o cliente
                // ...
            }
            else if (command == "STOR")
            {
                // Receber um arquivo do cliente e salvar no servidor
                // ...
            }
            else
            {
                // Comando desconhecido
                socket.write(boost::asio::buffer("500 Command not recognized.\r\n"));
            }

            data.clear();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro no cliente: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 21));

        std::cout << "Servidor FTP iniciado na porta 21" << std::endl;

        while (true)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::thread t(handle_client, std::move(socket));
            t.detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
} */

/*

// SEGUNDA VERSÃO

#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstddef>
#include <thread>
#include <string>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

void handle_client(tcp::socket &socket)
{
    try
    {
        std::string data, command, argument;
        while (true)
        {
            boost::system::error_code error;
            size_t length = boost::asio::read(socket,
                                              boost::asio::buffer(data, 1024),
                                              error);

            if (error == error::eof)
                break; // Conexão encerrada pelo cliente

            // Extrair o comando e o argumento da linha recebida
            std::istringstream iss(data);
            iss >> command >> argument;

            if (command == "USER")
            {
                // Implementar a lógica de autenticação do usuário
                // ...
            }
            else if (command == "PASS")
            {
                // Implementar a lógica de verificação da senha
                // ...
            }
            else if (command == "LIST")
            {
                // Listar os arquivos e diretórios do diretório atual
                fs::path current_dir = "/path/to/your/ftp/root"; // Substituir pelo caminho desejado
                for (auto &p : fs::directory_iterator(current_dir))
                {
                    socket.write(boost::asio::buffer(p.path().string() + "\r\n"));
                }
                socket.write(boost::asio::buffer("226 Transfer complete.\r\n"));
            }
            else if (command == "RETR")
            {
                // Enviar um arquivo para o cliente
                fs::path file_path = current_dir / argument;
                if (fs::exists(file_path) && fs::is_regular_file(file_path))
                {
                    std::ifstream ifs(file_path, std::ios::binary);
                    if (ifs.is_open())
                    {
                        socket.write(boost::asio::buffer("150 Opening data connection.\r\n"));
                        // Implementar a abertura da conexão de dados aqui...
                        // ...
                        std::string buffer;
                        while (ifs.read(buffer.data(), buffer.size()))
                        {
                            socket.write(boost::asio::buffer(buffer));
                        }
                        socket.write(boost::asio::buffer("226 Transfer complete.\r\n"));
                        // Fechar a conexão de dados
                    }
                    else
                    {
                        socket.write(boost::asio::buffer("550 Failed to open file.\r\n"));
                    }
                }
                else
                {
                    socket.write(boost::asio::buffer("550 File not found.\r\n"));
                }
            }
            else if (command == "CWD")
            {
                // Mudar o diretório atual
                fs::path new_dir = current_dir / argument;
                if (fs::exists(new_dir) && fs::is_directory(new_dir))
                {
                    current_dir = new_dir;
                    socket.write(boost::asio::buffer("250 Directory changed.\r\n"));
                }
                else
                {
                    socket.write(boost::asio::buffer("550 Directory not found.\r\n"));
                }
            }
            else if (command == "STOR")
            {
                // Receber um arquivo do cliente e salvar no servidor
                fs::path file_path = current_dir / argument;
                socket.write(boost::asio::buffer("150 Opening data connection.\r\n"));
                // Implementar a abertura da conexão de dados aqui...
                // ...
                std::ofstream ofs(file_path, std::ios::binary);
                if (ofs.is_open())
                {
                    // Ler os dados da conexão de dados e escrever no arquivo
                    // ...
                    socket.write(boost::asio::buffer("226 Transfer complete.\r\n"));
                }
                else
                {
                    socket.write(boost::asio::buffer("550 Failed to create file.\r\n"));
                }
            }
            else
            {
                // Comando desconhecido
                socket.write(boost::asio::buffer("500 Command not recognized.\r\n"));
            }

            data.clear();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro no cliente: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 21));

        std::cout << "Servidor FTP iniciado na porta 21" << std::endl;

        while (true)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::thread t(handle_client, std::move(socket));
            t.detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
*/

// VERSÃO FINAL

#include <boost/asio.hpp>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <cstddef>
#include <fstream>

using boost::asio::ip::tcp;
namespace fs = std::filesystem;

void handle_client(tcp::socket &socket, fs::path &current_dir)
{
    try
    {
        std::string data, command, argument;
        while (true)
        {
            boost::system::error_code error;
            size_t length = boost::asio::read(socket,
                                              boost::asio::buffer(data));

            if (error.value() == boost::asio::error::eof)
                break; // Conexão encerrada pelo cliente

            // Extract command and argument
            std::istringstream iss(data);
            iss >> command >> argument;

            if (command == "USER")
            {
                // Implement user authentication logic
            }
            else if (command == "PASS")
            {
                // Implement password verification logic
            }
            else if (command == "LIST")
            {
                for (auto &p : fs::directory_iterator(current_dir))
                {
                    boost::asio::write(socket, boost::asio::buffer(p.path().string() + "\r\n"));
                }
                boost::asio::write(socket, boost::asio::buffer("226 Transfer complete.\r\n"));
            }
            else if (command == "RETR")
            {
                fs::path file_path = current_dir / argument;
                if (fs::exists(file_path) && fs::is_regular_file(file_path))
                {
                    std::ifstream ifs(file_path, std::ios::binary);
                    if (ifs.is_open())
                    {
                        boost::asio::write(socket, boost::asio::buffer("150 Opening data connection.\r\n"));
                        // Implement data connection opening here...

                        std::string buffer;
                        while (ifs.read(buffer.data(), buffer.size()))
                        {
                            boost::asio::write(socket, boost::asio::buffer(buffer));
                        }
                        boost::asio::write(socket, boost::asio::buffer("226 Transfer complete.\r\n"));
                        // Close data connection
                    }
                    else
                    {
                        boost::asio::write(socket, boost::asio::buffer("550 Failed to open file.\r\n"));
                    }
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("550 File not found.\r\n"));
                }
            }
            else if (command == "CWD")
            {
                fs::path new_dir = current_dir / argument;
                if (fs::exists(new_dir) && fs::is_directory(new_dir))
                {
                    current_dir = new_dir;
                    boost::asio::write(socket, boost::asio::buffer("250 Directory changed.\r\n"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("550 Directory not found.\r\n"));
                }
            }
            else if (command == "STOR")
            {
                fs::path file_path = current_dir / argument;
                boost::asio::write(socket, boost::asio::buffer("150 Opening data connection.\r\n"));
                // Implement data connection opening here...

                std::ofstream ofs(file_path, std::ios::binary);
                if (ofs.is_open())
                {
                    // Read data from data connection and write to file
                    // ...
                    boost::asio::write(socket, boost::asio::buffer("226 Transfer complete.\r\n"));
                }
                else
                {
                    boost::asio::write(socket, boost::asio::buffer("550 Failed to create file.\r\n"));
                }
            }
            else
            {
                boost::asio::write(socket, boost::asio::buffer("500 Command not recognized.\r\n"));
            }

            data.clear();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Error in client: " << e.what() << std::endl;
    }
}

int main()
{
    try
    {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 21));

        std::cout << "Servidor FTP iniciado na porta 21" << std::endl;

        while (true)
        {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            fs::path current_dir = "/path/to/your/ftp/root"; // Replace with your desired path

            std::thread t([&socket, &current_dir]
                          { handle_client(socket, current_dir); });
            t.detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro: " << e.what() << std::endl;
    }

    return 0;
}