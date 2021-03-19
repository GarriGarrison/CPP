#include <iostream>
#include <locale>  //русский язык
#include <cstdlib>  //для random

using namespace std;



/* Сыграем в игру */
void Play (int m)
{
    int x;

    for (int attempt_count = 0; attempt_count < 100; attempt_count++) {
        cout << "Угадайте магическое число: ";
        cin >> x;
        if (x == m) {
            cout << "** Правильно **\n";
            return;
        }
        else if (x < m) cout << "Маловато.\n";
        else cout << "Многовато.\n";
    }
    cout << "Вы использовали все шансы угадать число. "
         << "Попытайтесь снова.\n";
}



/******************************************************************************
*                                    -= MAIN =-                               *
******************************************************************************/
int main()
{
    setlocale(LC_ALL, "Russian");


    int option = 0;
    int magic = rand();


    do {
        cout << "1. Получить новое магическое число\n";
        cout << "2. Сыграть\n";
        cout << "0. Выйти из программы\n";

        do {
            cout << "Выберите пунк меню: ";
            cin >> option;
        } while (option < 1 || option > 3);

        switch (option) {
        case 1:
            magic = rand();
            break;
        case 2:
            Play(magic);
            break;
        case 3:
            cout << "До свидания!\n";
        }
    } while (option != 3);

    cout << "Hello world!" << endl;
    cout << "Привет!";
    return 0;
}
