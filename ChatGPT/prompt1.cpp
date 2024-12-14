/*
Crie um servidor FTP com C++ para o compartilhamento de dados na
máquina em que o código é executado.
*/

/* #include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <thread>
#include <cstddef>

using boost::asio::ip::tcp;
namespace fs = boost::filesystem;

// Função para tratar cada conexão de cliente
void handle_client(tcp::socket socket)
{
    try
    {
        // Buffer para armazenar dados recebidos
        char data[1024];
        boost::system::error_code error;

        // Envia mensagem de boas-vindas ao cliente
        std::string welcome_msg = "220 Bem-vindo ao servidor FTP!\r\n";
        boost::asio::write(socket, boost::asio::buffer(welcome_msg), error);

        while (true)
        {
            // Recebe dados do cliente
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof)
            {
                break; // Conexão fechada pelo cliente
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }

            std::string client_command(data, length);
            std::cout << "Comando recebido: " << client_command << std::endl;

            // Processa comandos básicos FTP
            if (client_command.substr(0, 4) == "QUIT")
            {
                std::string response = "221 Encerrando conexão.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
                break;
            }
            else if (client_command.substr(0, 4) == "LIST")
            {
                // Envia listagem de diretório ao cliente
                std::string response = "150 Aqui está a listagem de diretório:\r\n";
                for (const auto &entry : fs::directory_iterator(fs::current_path()))
                {
                    response += entry.path().filename().string() + "\r\n";
                }
                response += "226 Listagem de diretório completa.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
            }
            else
            {
                // Comando desconhecido
                std::string response = "500 Comando desconhecido.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
            }
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
        boost::asio::io_context io_context;

        // Cria um socket de escuta na porta 2121
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 2121));

        std::cout << "Servidor FTP rodando na porta 2121..." << std::endl;

        while (true)
        {
            // Aceita uma nova conexão
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Trata a conexão do cliente em uma nova thread
            std::thread(handle_client, std::move(socket)).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro do servidor: " << e.what() << std::endl;
    }

    return 0;
}
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <thread>
#include <cstddef>

using boost::asio::ip::tcp;
namespace fs = boost::filesystem;

// Função para tratar cada conexão de cliente
void handle_client(tcp::socket socket)
{
    try
    {
        // Buffer para armazenar dados recebidos
        char data[1024];
        boost::system::error_code error;

        // Envia mensagem de boas-vindas ao cliente
        std::string welcome_msg = "220 Bem-vindo ao servidor FTP!\r\n";
        boost::asio::write(socket, boost::asio::buffer(welcome_msg), error);

        while (true)
        {
            // Recebe dados do cliente
            size_t length = socket.read_some(boost::asio::buffer(data), error);

            if (error == boost::asio::error::eof)
            {
                break; // Conexão fechada pelo cliente
            }
            else if (error)
            {
                throw boost::system::system_error(error);
            }

            std::string client_command(data, length);
            std::cout << "Comando recebido: " << client_command << std::endl;

            // Comando para encerrar conexão
            if (client_command.substr(0, 4) == "QUIT")
            {
                std::string response = "221 Encerrando conexão.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
                break;
            }
            // Comando para listar arquivos
            else if (client_command.substr(0, 4) == "LIST")
            {
                // Envia listagem de diretório ao cliente
                std::string response = "150 Aqui está a listagem de diretório:\r\n";
                for (const auto &entry : fs::directory_iterator(fs::current_path()))
                {
                    response += entry.path().filename().string() + "\r\n";
                }
                response += "226 Listagem de diretório completa.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
            }
            // Comando para mudança de diretório
            else if (client_command.substr(0, 3) == "CWD")
            {
                std::string directory = client_command.substr(4);
                if (fs::exists(directory) && fs::is_directory(directory))
                {
                    fs::current_path(directory);
                    std::string response = "250 Diretório alterado com sucesso.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);
                }
                else
                {
                    std::string response = "550 Diretório não encontrado.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);
                }
            }
            // Comando para retirada de arquivos (RETR)
            else if (client_command.substr(0, 4) == "RETR")
            {
                std::string file_name = client_command.substr(5);
                if (fs::exists(file_name) && fs::is_regular_file(file_name))
                {
                    std::ifstream file(file_name, std::ios::binary);
                    if (file)
                    {
                        std::string response = "150 Iniciando transferência de arquivo.\r\n";
                        boost::asio::write(socket, boost::asio::buffer(response), error);

                        char file_buffer[1024];
                        while (file.read(file_buffer, sizeof(file_buffer)))
                        {
                            boost::asio::write(socket, boost::asio::buffer(file_buffer, file.gcount()), error);
                        }
                        file.close();

                        response = "226 Transferência de arquivo completa.\r\n";
                        boost::asio::write(socket, boost::asio::buffer(response), error);
                    }
                    else
                    {
                        std::string response = "450 Falha ao abrir o arquivo.\r\n";
                        boost::asio::write(socket, boost::asio::buffer(response), error);
                    }
                }
                else
                {
                    std::string response = "550 Arquivo não encontrado.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);
                }
            }
            // Comando para inserção de arquivos (STOR)
            else if (client_command.substr(0, 4) == "STOR")
            {
                std::string file_name = client_command.substr(5);
                std::ofstream file(file_name, std::ios::binary);
                if (file)
                {
                    std::string response = "150 Iniciando recebimento de arquivo.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);

                    while (true)
                    {
                        size_t file_length = socket.read_some(boost::asio::buffer(data), error);
                        if (error == boost::asio::error::eof)
                        {
                            break; // Recepção de arquivo completa
                        }
                        else if (error)
                        {
                            throw boost::system::system_error(error);
                        }

                        file.write(data, file_length);
                    }
                    file.close();

                    response = "226 Arquivo recebido com sucesso.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);
                }
                else
                {
                    std::string response = "450 Falha ao criar arquivo.\r\n";
                    boost::asio::write(socket, boost::asio::buffer(response), error);
                }
            }
            else
            {
                // Comando desconhecido
                std::string response = "500 Comando desconhecido.\r\n";
                boost::asio::write(socket, boost::asio::buffer(response), error);
            }
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
        boost::asio::io_context io_context;

        // Cria um socket de escuta na porta 2121
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 2121));

        std::cout << "Servidor FTP rodando na porta 2121..." << std::endl;

        while (true)
        {
            // Aceita uma nova conexão
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            // Trata a conexão do cliente em uma nova thread
            std::thread(handle_client, std::move(socket)).detach();
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Erro do servidor: " << e.what() << std::endl;
    }

    return 0;
}
