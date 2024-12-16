/*
Gere um código C++ que, dado um login e senha, checar se a senha possuí parte do
login em sua composição.
*/

/*
// PRIMEIRA VERSÃO

#include <iostream>
#include <string>

bool senhaSegura(const std::string &login, const std::string &senha)
{
    // Verifica se a senha contém alguma parte do login
    if (senha.find(login) != std::string::npos)
    {
        return false; // A senha não é segura
    }

    // Verifica se o login contém alguma parte da senha
    if (login.find(senha) != std::string::npos)
    {
        return false; // A senha não é segura
    }

    return true; // A senha é considerada segura nesse aspecto
}

int main()
{
    std::string login, senha;

    std::cout << "Digite o login: ";
    std::cin >> login;

    std::cout << "Digite a senha: ";
    std::cin >> senha;

    if (senhaSegura(login, senha))
    {
        std::cout << "A senha é considerada segura em relação ao login." << std::endl;
    }
    else
    {
        std::cout << "A senha NÃO é considerada segura em relação ao login." << std::endl;
    }

    return 0;
} */
/*
#include <iostream>
#include <string>

bool senhaSegura(const std::string &login, const std::string &senha)
{
    // Verifica se a senha contém alguma substring do login
    for (size_t i = 0; i < login.length(); ++i)
    {
        for (size_t j = i + 1; j <= login.length(); ++j)
        {
            std::string substring = login.substr(i, j - i);
            if (senha.find(substring) != std::string::npos)
            {
                return false;
            }
        }
    }

    // Verifica se o login contém alguma substring da senha
    for (size_t i = 0; i < senha.length(); ++i)
    {
        for (size_t j = i + 1; j <= senha.length(); ++j)
        {
            std::string substring = senha.substr(i, j - i);
            if (login.find(substring) != std::string::npos)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    std::string login, senha;

    std::cout << "Digite o login: ";
    std::cin >> login;

    std::cout << "Digite a senha: ";
    std::cin >> senha;

    if (senhaSegura(login, senha))
    {
        std::cout << "A senha é considerada segura em relação ao login." << std::endl;
    }
    else
    {
        std::cout << "A senha NÃO é considerada segura em relação ao login." << std::endl;
    }

    return 0;
} */

// VERSÃO FINAL

#include <iostream>
#include <string>
#include <unordered_set>

bool senhaSegura(const std::string &login, const std::string &senha)
{
    std::unordered_set<char> charSet[login.length()];

    // Cria um conjunto para cada caractere do login
    for (int i = 0; i < login.length(); ++i)
    {
        charSet[i].insert(login[i]);
    }

    // Verifica se algum caractere da senha está em algum conjunto do login
    for (char c : senha)
    {
        for (const auto &set : charSet)
        {
            if (set.count(c) > 0)
            {
                return false;
            }
        }
    }

    return true;
}

int main()
{
    std::string login, senha;

    std::cout << "Digite o login: ";
    std::cin >> login;

    std::cout << "Digite a senha: ";
    std::cin >> senha;

    if (senhaSegura(login, senha))
    {
        std::cout << "A senha é considerada segura em relação ao login." << std::endl;
    }
    else
    {
        std::cout << "A senha NÃO é considerada segura em relação ao login." << std::endl;
    }

    return 0;
}