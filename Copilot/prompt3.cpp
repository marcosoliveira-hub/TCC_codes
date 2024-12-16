/*
Gere um código C++ que faça a concatenação de 2 Strings fornecidas pelo
usuário, o usuário também deve inserir o tamanho das Strings. Para maior flexibilidade,
aloque memória para as Strings.
*/

/*

// PRIMEIRA VERSÃO

#include <iostream>
#include <cstring>

int main()
{
    int tamanho1, tamanho2;

    // Solicita ao usuário o tamanho da primeira string
    std::cout << "Digite o tamanho da primeira string: ";
    std::cin >> tamanho1;
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória para a primeira string
    char *string1 = new char[tamanho1 + 1];

    // Solicita ao usuário para inserir a primeira string
    std::cout << "Digite a primeira string: ";
    std::cin.getline(string1, tamanho1 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string1) != tamanho1)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da primeira string!" << std::endl;
        delete[] string1;
        return 1;
    }

    // Solicita ao usuário o tamanho da segunda string
    std::cout << "Digite o tamanho da segunda string: ";
    std::cin >> tamanho2;
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória para a segunda string
    char *string2 = new char[tamanho2 + 1];

    // Solicita ao usuário para inserir a segunda string
    std::cout << "Digite a segunda string: ";
    std::cin.getline(string2, tamanho2 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string2) != tamanho2)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da segunda string!" << std::endl;
        delete[] string1;
        delete[] string2;
        return 1;
    }

    // Aloca memória para a string concatenada
    char *concatenatedStr = new char[tamanho1 + tamanho2 + 1];

    // Concatena as strings
    std::strcpy(concatenatedStr, string1);
    std::strcat(concatenatedStr, string2);

    // Exibe a string concatenada e seu tamanho
    std::cout << "String concatenada: " << concatenatedStr << " (Tamanho: " << std::strlen(concatenatedStr) << ")" << std::endl;

    // Libera a memória alocada
    delete[] string1;
    delete[] string2;
    delete[] concatenatedStr;

    return 0;
} */

// VERSÃO FINAL

#include <iostream>
#include <cstring>
#include <limits>

int main()
{
    int tamanho1, tamanho2;

    // Solicita ao usuário o tamanho da primeira string
    std::cout << "Digite o tamanho da primeira string: ";
    while (!(std::cin >> tamanho1) || tamanho1 <= 0)
    {
        std::cout << "Erro: Por favor, insira um número inteiro positivo." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória para a primeira string
    char *string1 = new (std::nothrow) char[tamanho1 + 1];
    if (!string1)
    {
        std::cerr << "Erro: Falha na alocação de memória para a primeira string." << std::endl;
        return 1;
    }

    // Solicita ao usuário para inserir a primeira string
    std::cout << "Digite a primeira string: ";
    std::cin.getline(string1, tamanho1 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string1) != tamanho1)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da primeira string!" << std::endl;
        delete[] string1;
        return 1;
    }

    // Solicita ao usuário o tamanho da segunda string
    std::cout << "Digite o tamanho da segunda string: ";
    while (!(std::cin >> tamanho2) || tamanho2 <= 0)
    {
        std::cout << "Erro: Por favor, insira um número inteiro positivo." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória para a segunda string
    char *string2 = new (std::nothrow) char[tamanho2 + 1];
    if (!string2)
    {
        std::cerr << "Erro: Falha na alocação de memória para a segunda string." << std::endl;
        delete[] string1;
        return 1;
    }

    // Solicita ao usuário para inserir a segunda string
    std::cout << "Digite a segunda string: ";
    std::cin.getline(string2, tamanho2 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string2) != tamanho2)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da segunda string!" << std::endl;
        delete[] string1;
        delete[] string2;
        return 1;
    }

    // Aloca memória para a string concatenada
    char *concatenatedStr = new (std::nothrow) char[tamanho1 + tamanho2 + 1];
    if (!concatenatedStr)
    {
        std::cerr << "Erro: Falha na alocação de memória para a string concatenada." << std::endl;
        delete[] string1;
        delete[] string2;
        return 1;
    }

    // Concatena as strings
    std::strcpy(concatenatedStr, string1);
    std::strcat(concatenatedStr, string2);

    // Exibe a string concatenada e seu tamanho
    std::cout << "String concatenada: " << concatenatedStr << " (Tamanho: " << std::strlen(concatenatedStr) << ")" << std::endl;

    // Libera a memória alocada
    delete[] string1;
    delete[] string2;
    delete[] concatenatedStr;

    return 0;
}