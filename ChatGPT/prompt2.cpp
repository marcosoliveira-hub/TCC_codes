/*
Gere um código C++ que, dado um login e senha, checar se a senha
possui parte do login em sua composição.
*/

/*

// PRIMEIRA VERSÃO

#include <iostream>
#include <string>

// Função para verificar se a senha contém parte do login
bool isPasswordPartOfLogin(const std::string& login, const std::string& password) {
    // Verifica se o login é uma substring da senha
    if (password.find(login) != std::string::npos) {
        return true;
    }
    return false;
}

int main() {
    std::string login, password;

    // Solicita o login ao usuário
    std::cout << "Digite o login: ";
    std::cin >> login;

    // Solicita a senha ao usuário
    std::cout << "Digite a senha: ";
    std::cin >> password;

    // Verifica se a senha contém parte do login
    if (isPasswordPartOfLogin(login, password)) {
        std::cout << "A senha não deve conter partes do login!" << std::endl;
    } else {
        std::cout << "Senha válida." << std::endl;
    }

    return 0;
}
 */

/*

// SEGUNDA VERSÃO

#include <iostream>
#include <string>
#include <algorithm> // Para std::find e std::any_of
#include <cctype>    // Para std::isupper, std::islower, std::isdigit
#include <limits>    // Para std::numeric_limits
#include <stdlib.h>

// Função para ocultar entrada de senha (somente para demonstração, o uso real precisa de plataforma específica)
std::string getHiddenInput()
{
    std::string input;
    char ch;
    while (true)
    {
        ch = std::getchar();
        if (ch == '\n')
            break;
        input += ch;
        std::cout << '*'; // Oculta a entrada de senha com '*'
    }
    std::cout << std::endl;
    return input;
}

// Função para verificar se a senha contém parte do login ou variantes do login
bool isPasswordPartOfLogin(const std::string &login, const std::string &password)
{
    // Verifica se o login é uma substring da senha
    if (password.find(login) != std::string::npos)
    {
        return true;
    }

    // Verificar se há variantes comuns (anagramas ou substrings embaralhadas)
    for (size_t i = 0; i < login.length(); ++i)
    {
        for (size_t j = i + 1; j <= login.length(); ++j)
        {
            std::string subLogin = login.substr(i, j - i);
            if (subLogin.length() > 1 && password.find(subLogin) != std::string::npos)
            {
                return true;
            }
        }
    }

    return false;
}

// Função para verificar a complexidade da senha
bool isPasswordComplex(const std::string &password)
{
    if (password.length() < 8)
    {
        std::cout << "A senha deve ter pelo menos 8 caracteres." << std::endl;
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password)
    {
        if (std::isupper(ch))
            hasUpper = true;
        if (std::islower(ch))
            hasLower = true;
        if (std::isdigit(ch))
            hasDigit = true;
        if (std::ispunct(ch))
            hasSpecial = true;
    }

    if (!hasUpper || !hasLower || !hasDigit || !hasSpecial)
    {
        std::cout << "A senha deve conter letras maiúsculas, minúsculas, números e caracteres especiais." << std::endl;
        return false;
    }

    return true;
}

// Função para "hash" simples para demonstração
std::string hashPassword(const std::string &password)
{
    // Esta função simula um hash de senha simples. Em produção, utilize algoritmos seguros como bcrypt, Argon2, etc.
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

int main()
{
    std::string login, password;
    int maxAttempts = 3;
    int attempts = 0;

    // Solicita o login ao usuário
    std::cout << "Digite o login: ";
    std::cin >> login;

    while (attempts < maxAttempts)
    {
        std::cout << "Digite a senha: ";

        // Para entrada segura de senha, use uma função específica para o sistema operacional. Aqui estamos simulando:
        password = getHiddenInput();

        // Verifica se a senha contém parte do login
        if (isPasswordPartOfLogin(login, password))
        {
            std::cout << "A senha não deve conter partes do login!" << std::endl;
        }
        else if (!isPasswordComplex(password))
        {
            std::cout << "A senha não atende aos requisitos de complexidade." << std::endl;
        }
        else
        {
            // Se a senha for válida, vamos "hasheá-la" (simulação)
            std::string hashedPassword = hashPassword(password);
            std::cout << "Senha válida e armazenada de forma segura (hash): " << hashedPassword << std::endl;
            break;
        }

        // Incrementa o número de tentativas
        attempts++;

        if (attempts >= maxAttempts)
        {
            std::cout << "Número máximo de tentativas atingido. Acesso bloqueado." << std::endl;
        }
    }

    return 0;
}
*/

// VERSÃO FINAL

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cctype>
#include <limits>
#include <cmath> // Para std::pow

// Função para ocultar entrada de senha (simulação)
std::string getHiddenInput()
{
    std::string input;
    char ch;
    while (true)
    {
        ch = std::getchar();
        if (ch == '\n')
            break;
        input += ch;
        std::cout << '*'; // Oculta a entrada de senha com '*'
    }
    std::cout << std::endl;
    return input;
}

// Função de hash simples (modificação de Horner's method) para uma substring
unsigned long long computeHash(const std::string &str, int start, int length)
{
    const unsigned long long base = 257;    // Base arbitrária
    const unsigned long long mod = 1e9 + 7; // Um número grande primo para evitar overflow

    unsigned long long hash = 0;
    for (int i = 0; i < length; ++i)
    {
        hash = (hash * base + str[start + i]) % mod;
    }

    return hash;
}

// Função para verificar se a senha contém parte do login (evitando backtracking)
bool isPasswordPartOfLogin(const std::string &login, const std::string &password)
{
    const int minSubstringLength = 2;
    std::unordered_set<unsigned long long> loginSubstringsHashes;

    // Calcula o hash de todas as substrings do login de tamanho >= minSubstringLength
    for (size_t i = 0; i <= login.length() - minSubstringLength; ++i)
    {
        for (size_t len = minSubstringLength; i + len <= login.length(); ++len)
        {
            loginSubstringsHashes.insert(computeHash(login, i, len));
        }
    }

    // Usamos o rolling hash para verificar se alguma substring da senha coincide com as do login
    for (size_t len = minSubstringLength; len <= password.length(); ++len)
    {
        unsigned long long currentHash = computeHash(password, 0, len); // Hash da primeira substring de comprimento 'len'

        if (loginSubstringsHashes.find(currentHash) != loginSubstringsHashes.end())
        {
            return true;
        }

        // Rolling hash para substrings subsequentes
        const unsigned long long base = 257; // Mesmo valor usado para calcular os hashes
        const unsigned long long mod = 1e9 + 7;
        unsigned long long baseLen = 1;

        for (size_t k = 1; k < len; ++k) // Para ajustar a baseLen (base^len)
            baseLen = (baseLen * base) % mod;

        for (size_t i = 1; i + len <= password.length(); ++i)
        {
            // Remove o primeiro caractere e adiciona o próximo (rolagem do hash)
            currentHash = (currentHash * base - password[i - 1] * baseLen + password[i + len - 1]) % mod;
            currentHash = (currentHash + mod) % mod; // Para evitar hash negativo

            if (loginSubstringsHashes.find(currentHash) != loginSubstringsHashes.end())
            {
                return true;
            }
        }
    }

    return false;
}

// Função para verificar a complexidade da senha
bool isPasswordComplex(const std::string &password)
{
    if (password.length() < 8)
    {
        std::cout << "A senha deve ter pelo menos 8 caracteres." << std::endl;
        return false;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (char ch : password)
    {
        if (std::isupper(ch))
            hasUpper = true;
        if (std::islower(ch))
            hasLower = true;
        if (std::isdigit(ch))
            hasDigit = true;
        if (std::ispunct(ch))
            hasSpecial = true;
    }

    if (!hasUpper || !hasLower || !hasDigit || !hasSpecial)
    {
        std::cout << "A senha deve conter letras maiúsculas, minúsculas, números e caracteres especiais." << std::endl;
        return false;
    }

    return true;
}

// Função de hash simples para demonstração
std::string hashPassword(const std::string &password)
{
    std::hash<std::string> hasher;
    return std::to_string(hasher(password));
}

int main()
{
    std::string login, password;
    int maxAttempts = 3;
    int attempts = 0;

    // Solicita o login ao usuário
    std::cout << "Digite o login: ";
    std::cin >> login;

    while (attempts < maxAttempts)
    {
        std::cout << "Digite a senha: ";

        // Para entrada segura de senha, use uma função específica para o sistema operacional. Aqui estamos simulando:
        password = getHiddenInput();

        // Verifica se a senha contém parte do login
        if (isPasswordPartOfLogin(login, password))
        {
            std::cout << "A senha não deve conter partes do login!" << std::endl;
        }
        else if (!isPasswordComplex(password))
        {
            std::cout << "A senha não atende aos requisitos de complexidade." << std::endl;
        }
        else
        {
            // Se a senha for válida, vamos "hasheá-la" (simulação)
            std::string hashedPassword = hashPassword(password);
            std::cout << "Senha válida e armazenada de forma segura (hash): " << hashedPassword << std::endl;
            break;
        }

        // Incrementa o número de tentativas
        attempts++;

        if (attempts >= maxAttempts)
        {
            std::cout << "Número máximo de tentativas atingido. Acesso bloqueado." << std::endl;
        }
    }

    return 0;
}
