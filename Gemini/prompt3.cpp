/*
Gere um código C++ que faça a concatenação de 2 Strings fornecidas pelo
usuário, o usuário também deve inserir o tamanho das Strings. Para maior flexibilidade,
aloque memória para as Strings.
*/

/* #include <iostream>

using namespace std;

int main()
{
    int tamanho1, tamanho2;

    cout << "Digite o tamanho da primeira string: ";
    cin >> tamanho1;

    cout << "Digite o tamanho da segunda string: ";
    cin >> tamanho2;

    // Alocar   memória para as strings
    char *str1 = new char[tamanho1 + 1]; // +1 para o caractere nulo
    char *str2 = new char[tamanho2 + 1];

    cout << "Digite a primeira string: ";
    cin >> str1;

    cout << "Digite a segunda string: ";
    cin >> str2;

    // Calcular o tamanho da string concatenada
    int tamanho_total = tamanho1 + tamanho2;

    // Alocar memória para a string concatenada
    char *str_concatenada = new char[tamanho_total + 1];

    // Concatenar as strings
    for (int i = 0; i < tamanho1; i++)
    {
        str_concatenada[i] = str1[i];
    }
    for (int i = 0; i < tamanho2; i++)
    {
        str_concatenada[tamanho1 + i] = str2[i];
    }
    str_concatenada[tamanho_total] = '\0'; // Adicionar o caractere nulo

    cout << "String concatenada: " << str_concatenada << endl;

    // Liberar a memória alocada
    delete[] str1;
    delete[] str2;
    delete[] str_concatenada;

    return 0;
} */

#include <iostream>
#include <string>
#include <memory>

using namespace std;

int main()
{
    const int MAX_SIZE = 1024; // Limite máximo para o tamanho das strings

    string str1, str2;

    cout << "Digite a primeira string: ";
    getline(cin, str1);

    cout << "Digite a segunda string: ";
    getline(cin, str2);

    // Verificar se as strings estão dentro do limite máximo
    if (str1.size() > MAX_SIZE || str2.size() > MAX_SIZE)
    {
        cerr << "As strings excederam o tamanho máximo permitido." << endl;
        return 1;
    }

    // Concatenar as strings usando std::string
    string str_concatenada = str1 + str2;

    cout << "String concatenada: " << str_concatenada << endl;

    return 0;
}