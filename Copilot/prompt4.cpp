/*
Gere um código em C++ que faça a multiplicação dos elementos em um array dado
como entrada pelo usuário
*/

/*
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n;
    long long produto = 1; // Use long long para evitar overflow em multiplicações grandes

    cout << "Digite o tamanho do array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Digite os elementos do array:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        produto *= arr[i]; // Multiplica o elemento atual pelo produto acumulado
    }

    cout << "O produto dos elementos do array é: " << produto << endl;

    return 0;
}
*/
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
    int n;
    long long produto = 1; // Use long long para evitar overflow em multiplicações grandes
    bool overflow = false;

    cout << "Digite o tamanho do array: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Digite os elementos do array:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        if (produto > numeric_limits<long long>::max() / arr[i])
        {
            overflow = true;
            break;
        }
        produto *= arr[i]; // Multiplica o elemento atual pelo produto acumulado
    }

    if (overflow)
    {
        cout << "Erro: Overflow detectado durante a multiplicação." << endl;
    }
    else
    {
        cout << "O produto dos elementos do array é: " << produto << endl;
    }

    return 0;
}
