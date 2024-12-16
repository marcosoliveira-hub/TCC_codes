/*
Gere um código C++ que, dado um login e senha, checar se a senha
possui parte do login em sua composição.
*/

/*

// PRIMEIRA VERSÃO

#include <iostream>
#include <string>
#include <regex>

bool isPasswordValid(const std::string &login, const std::string &password)
{
    // Verifica se a string de login está contida na senha
    if (password.find(login) != std::string::npos)
    {
        return false;
    }

    // Verifica se a senha tem pelo menos 8 caracteres
    if (password.length() < 8)
    {
        return false;
    }

    // Verifica se a senha contém pelo menos uma letra maiúscula, uma minúscula, um número e um caractere especial
    std::regex complexity_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (!std::regex_match(password, complexity_regex))
    {
        return false;
    }

    return true;
}

int main()
{
    std::string login, password;

    std::cout << "Enter login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (isPasswordValid(login, password))
    {
        std::cout << "Password is valid." << std::endl;
    }
    else
    {
        std::cout << "Password is invalid. It must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one number, one special character, and not contain the login." << std::endl;
    }

    return 0;
} */

/* #include <iostream>
#include <string>
#include <regex>

bool isPasswordValid(const std::string &login, const std::string &password)
{
    // Verifica se qualquer substring do login está contida na senha
    for (size_t i = 0; i < login.length(); ++i)
    {
        for (size_t j = i + 1; j <= login.length(); ++j)
        {
            if (password.find(login.substr(i, j - i)) != std::string::npos)
            {
                return false;
            }
        }
    }

    // Verifica se a senha tem pelo menos 8 caracteres
    if (password.length() < 8)
    {
        return false;
    }

    // Verifica se a senha contém pelo menos uma letra maiúscula, uma minúscula, um número e um caractere especial
    std::regex complexity_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (!std::regex_match(password, complexity_regex))
    {
        return false;
    }

    return true;
}

int main()
{
    std::string login, password;

    std::cout << "Enter login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (isPasswordValid(login, password))
    {
        std::cout << "Password is valid." << std::endl;
    }
    else
    {
        std::cout << "Password is invalid. It must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one number, one special character, and not contain any substring of the login." << std::endl;
    }

    return 0;
} */

// VERSÃO FINAL

#include <iostream>
#include <string>
#include <regex>
#include <unordered_set>

bool isPasswordValid(const std::string &login, const std::string &password)
{
    // Create a set to store all substrings of the login
    std::unordered_set<std::string> login_substrings;
    for (size_t len = 1; len <= login.length(); ++len)
    {
        for (size_t i = 0; i <= login.length() - len; ++i)
        {
            login_substrings.insert(login.substr(i, len));
        }
    }

    // Check if any substring of the login is contained in the password
    for (const auto &substring : login_substrings)
    {
        if (password.find(substring) != std::string::npos)
        {
            return false;
        }
    }

    // Verifica se a senha tem pelo menos 8 caracteres
    if (password.length() < 8)
    {
        return false;
    }

    // Verifica se a senha contém pelo menos uma letra maiúscula, uma minúscula, um número e um caractere especial
    std::regex complexity_regex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (!std::regex_match(password, complexity_regex))
    {
        return false;
    }

    return true;
}

int main()
{
    std::string login, password;

    std::cout << "Enter login: ";
    std::cin >> login;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (isPasswordValid(login, password))
    {
        std::cout << "Password is valid." << std::endl;
    }
    else
    {
        std::cout << "Password is invalid. It must be at least 8 characters long, contain at least one uppercase letter, one lowercase letter, one number, one special character, and not contain any substring of the login." << std::endl;
    }

    return 0;
}