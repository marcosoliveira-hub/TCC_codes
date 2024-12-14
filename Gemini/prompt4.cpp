/*
Gere um código em C++ que faça a multiplicação dos elementos em um array dado
como entrada pelo usuário
*/

/* #include <iostream>
using namespace std;

int main()
{
    int n, produto = 1;

    cout << "Digite o tamanho do array: ";
    cin >> n;

    int arr[n];

    cout << "Digite os elementos do array:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        produto *= arr[i]; // Multiplica o elemento atual pelo produto acumulado
    }

    cout << "O produto dos elementos do array é: " << produto << endl;

    return 0;
} */

#include <iostream>
#include <limits.h>

using namespace std;

int main()
{
    int n;
    long long produto = 1; // Utilizando long long para maior precisão

    cout << "Digite o tamanho do array: ";
    cin >> n;

    int arr[n];

    cout << "Digite os elementos do array:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];

        // Verifica se o produto está se aproximando do limite máximo do long long
        if (produto > LLONG_MAX / arr[i])
        {
            cout << "O produto excede o limite máximo." << endl;
            return 1;
        }

        produto *= arr[i];
    }

    cout << "O produto dos elementos do array é: " << produto << endl;

    return 0;
}