/*
Gere um código em C++ que faça a multiplicação dos elementos em um array dado
como entrada pelo usuário
*/

/*
#include <iostream>
#include <vector>

int main()
{
    int n;

    // Solicita ao usuário o tamanho do array
    std::cout << "Digite o tamanho do array: ";
    std::cin >> n;

    // Verifica se o tamanho do array é válido
    if (n <= 0)
    {
        std::cout << "O tamanho do array deve ser maior que 0." << std::endl;
        return 1;
    }

    std::vector<int> array(n);

    // Solicita ao usuário para inserir os elementos do array
    std::cout << "Digite os elementos do array:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> array[i];
    }

    // Calcula o produto de todos os elementos do array
    int product = 1;
    for (int i = 0; i < n; ++i)
    {
        product *= array[i];
    }

    // Exibe o resultado da multiplicação
    std::cout << "O produto dos elementos do array é: " << product << std::endl;

    return 0;
} */

#include <iostream>
#include <vector>
#include <limits> // Para std::numeric_limits

int main()
{
    int n;

    // Solicita ao usuário o tamanho do array
    std::cout << "Digite o tamanho do array: ";
    std::cin >> n;

    // Verifica se o tamanho do array é válido
    if (n <= 0)
    {
        std::cout << "O tamanho do array deve ser maior que 0." << std::endl;
        return 1;
    }

    std::vector<int> array(n);

    // Solicita ao usuário para inserir os elementos do array
    std::cout << "Digite os elementos do array:" << std::endl;
    for (int i = 0; i < n; ++i)
    {
        std::cin >> array[i];
    }

    // Calcula o produto de todos os elementos do array com verificação de overflow
    int product = 1;
    bool overflow = false;

    for (int i = 0; i < n; ++i)
    {
        // Verifica se a próxima multiplicação causará overflow
        if (array[i] != 0 && product > std::numeric_limits<int>::max() / array[i])
        {
            overflow = true;
            break;
        }

        product *= array[i];
    }

    // Exibe o resultado ou mensagem de erro em caso de overflow
    if (overflow)
    {
        std::cout << "Erro: Overflow detectado durante o cálculo do produto!" << std::endl;
    }
    else
    {
        std::cout << "O produto dos elementos do array é: " << product << std::endl;
    }

    return 0;
}
