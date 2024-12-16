/*
Gere um código C++ que faça a concatenação de 2 Strings fornecidas pelo
usuário, o usuário também deve inserir o tamanho das Strings. Para maior flexibilidade,
aloque memória para as Strings.
*/

/*
// PRIMEIRA VERSÃO

#include <iostream>
#include <cstring> // Necessário para strcpy e strcat

int main()
{
    int tamanho1, tamanho2;

    // Solicita ao usuário o tamanho da primeira string
    std::cout << "Digite o tamanho da primeira string: ";
    std::cin >> tamanho1;
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória dinamicamente para a primeira string
    char *string1 = new char[tamanho1 + 1]; // +1 para o caractere nulo '\0'

    // Solicita ao usuário para inserir a primeira string
    std::cout << "Digite a primeira string: ";
    std::cin.getline(string1, tamanho1 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string1) != tamanho1)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da primeira string!" << std::endl;
        delete[] string1; // Libera a memória alocada
        return 1;
    }

    // Solicita ao usuário o tamanho da segunda string
    std::cout << "Digite o tamanho da segunda string: ";
    std::cin >> tamanho2;
    std::cin.ignore(); // Limpa o buffer do cin para evitar problemas com getline

    // Aloca memória dinamicamente para a segunda string
    char *string2 = new char[tamanho2 + 1]; // +1 para o caractere nulo '\0'

    // Solicita ao usuário para inserir a segunda string
    std::cout << "Digite a segunda string: ";
    std::cin.getline(string2, tamanho2 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string2) != tamanho2)
    {
        std::cout << "Erro: O tamanho informado não corresponde ao tamanho da segunda string!" << std::endl;
        delete[] string1; // Libera a memória alocada
        delete[] string2; // Libera a memória alocada
        return 1;
    }

    // Calcula o tamanho da string concatenada
    int tamanhoConcatenado = tamanho1 + tamanho2;

    // Aloca memória dinamicamente para a string concatenada
    char *concatenacao = new char[tamanhoConcatenado + 1]; // +1 para o caractere nulo '\0'

    // Concatena as strings
    std::strcpy(concatenacao, string1); // Copia string1 para concatenacao
    std::strcat(concatenacao, string2); // Adiciona string2 no final de concatenacao

    // Exibe o resultado da concatenação e os tamanhos das strings fornecidas
    std::cout << "String concatenada: " << concatenacao << std::endl;
    std::cout << "Tamanho da string concatenada: " << std::strlen(concatenacao) << std::endl;

    // Libera a memória alocada
    delete[] string1;
    delete[] string2;
    delete[] concatenacao;

    return 0;
} */

// VERSÃO FINAL

#include <iostream>
#include <cstring> // Necessário para strcpy e strcat
#include <limits>  // Para std::numeric_limits

int main()
{
    int tamanho1, tamanho2;

    // Solicita ao usuário o tamanho da primeira string
    std::cout << "Digite o tamanho da primeira string: ";
    std::cin >> tamanho1;

    // Verifica se a entrada foi válida e se o tamanho é positivo
    if (std::cin.fail() || tamanho1 <= 0)
    {
        std::cerr << "Erro: Tamanho inválido para a primeira string!" << std::endl;
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer do cin

    // Aloca memória dinamicamente para a primeira string e verifica sucesso
    char *string1 = new (std::nothrow) char[tamanho1 + 1]; // +1 para o caractere nulo '\0'
    if (!string1)
    {
        std::cerr << "Erro: Falha ao alocar memória para a primeira string!" << std::endl;
        return 1;
    }

    // Solicita ao usuário para inserir a primeira string
    std::cout << "Digite a primeira string: ";
    std::cin.getline(string1, tamanho1 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string1) != tamanho1)
    {
        std::cerr << "Erro: O tamanho informado não corresponde ao tamanho da primeira string!" << std::endl;
        delete[] string1;
        return 1;
    }

    // Solicita ao usuário o tamanho da segunda string
    std::cout << "Digite o tamanho da segunda string: ";
    std::cin >> tamanho2;

    // Verifica se a entrada foi válida e se o tamanho é positivo
    if (std::cin.fail() || tamanho2 <= 0)
    {
        std::cerr << "Erro: Tamanho inválido para a segunda string!" << std::endl;
        delete[] string1;
        return 1;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer do cin

    // Aloca memória dinamicamente para a segunda string e verifica sucesso
    char *string2 = new (std::nothrow) char[tamanho2 + 1]; // +1 para o caractere nulo '\0'
    if (!string2)
    {
        std::cerr << "Erro: Falha ao alocar memória para a segunda string!" << std::endl;
        delete[] string1;
        return 1;
    }

    // Solicita ao usuário para inserir a segunda string
    std::cout << "Digite a segunda string: ";
    std::cin.getline(string2, tamanho2 + 1);

    // Verifica se o tamanho informado corresponde ao tamanho real da string
    if (std::strlen(string2) != tamanho2)
    {
        std::cerr << "Erro: O tamanho informado não corresponde ao tamanho da segunda string!" << std::endl;
        delete[] string1;
        delete[] string2;
        return 1;
    }

    // Calcula o tamanho da string concatenada
    int tamanhoConcatenado = tamanho1 + tamanho2;

    // Aloca memória dinamicamente para a string concatenada e verifica sucesso
    char *concatenacao = new (std::nothrow) char[tamanhoConcatenado + 1]; // +1 para o caractere nulo '\0'
    if (!concatenacao)
    {
        std::cerr << "Erro: Falha ao alocar memória para a string concatenada!" << std::endl;
        delete[] string1;
        delete[] string2;
        return 1;
    }

    // Concatena as strings de forma segura
    std::strncpy(concatenacao, string1, tamanho1);
    concatenacao[tamanho1] = '\0'; // Garante o caractere nulo
    std::strncat(concatenacao, string2, tamanho2);

    // Exibe o resultado da concatenação e os tamanhos das strings fornecidas
    std::cout << "String concatenada: " << concatenacao << std::endl;
    std::cout << "Tamanho da string concatenada: " << std::strlen(concatenacao) << std::endl;

    // Libera a memória alocada
    delete[] string1;
    delete[] string2;
    delete[] concatenacao;

    return 0;
}
