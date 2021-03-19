#include <iostream>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <locale>

using namespace std;


const int SIZE = 100;


struct InvType {
    char item[40];  // наименование товара
    double cost;    // стоимость
    double retail;  // розничная цена
    int on_hand;    // имеющееся в наличии количество
    int lead_time;  // число дней до пополнения запроса
} invtry[SIZE];


/** Иницилизация массива структур */
void InitList()
{
    int t;

    // Имя нулевой длинны означает пустое имя
    for (t = 0; t < SIZE; t++)
        *invtry[t].item = '\0';
}

/** Получение команды меню, выбранной пользователем */
int Menu()
{
    char ch;

    cout << '\n';
    do {
        cout << "(E)nter\n";    // ввести новый элемент
        cout << "(D)isplay\n";  // отобразить всю ведомость
        cout << "(U)pdate\n";   // изменить элемент
        cout << "(Q)uit\n\n";   // выйти из программы

        cout << "выберите команду: ";
        cin >> ch;
    } while (!strchr("eduq", tolower(ch)));

    return tolower(ch);
}

/** Ввод информации */
void Input(int i)
{
    cout << "Товар: ";
    cin >> invtry[i].item;

    cout << "Стоимость: ";
    cin >> invtry[i].cost;

    cout << "Розничная цена: ";
    cin >> invtry[i].retail;

    cout << "В наличии: ";
    cin >> invtry[i].on_hand;

    cout << "Время до пополнения запасов (в днях): ";
    cin >> invtry[i].lead_time;
}

/** Ввод элементов в инвертарную ведомость */
void Enter()
{
    int i;

    /* Находим первую свободную структуру */
    for (i = 0; i < SIZE; i++)
        if (!*invtry[i].item)  break;

    // Если массив полон, значение i будет равно SIZE
    if (i == SIZE) {
        cout << "Список полон.\n";
        return;
    }

    Input(i);
}

/** Модификация существующего элемента */
void Update()
{
    int i;
    char name[80];

    cout << "Введите наименование товара: ";
    cin >> name;

    for (i = 0; i < SIZE; i++)
        if (!strcmp(name, invtry[i].item))  break;

    if (i == SIZE) {
        cout << "Товар не найден.\n";
        return;
    }

    cout << "Введите новую информацию\n";
    Input(i);
}

/** Отображение на экране инвентарной ведомости */
void Display()
{
    int t;

    for (t = 0; t < SIZE; t++) {
        if (*invtry[t].item) {
            cout << invtry[t].item << '\n';
            cout << "Стоимость: " << invtry[t].cost;
            cout << "\nВ роздницу: ";
            cout << invtry[t].retail << '\n';
            cout << "В наличии: " << invtry[t].on_hand;
            cout << "\nДо пополнения осталось: ";
            cout << invtry[t].lead_time << " дней\n\n";
        }
    }
}



int main()
{
    setlocale(LC_ALL, "rus");

    char choice;

    for (;;) {
        choice = Menu();
        switch (choice) {
        case 'e':
            Enter();
            break;
        case 'd':
            Display();
            break;
        case 'u':
            Update();
            break;
        case 'q':
            return 0;
        }
    }
}
