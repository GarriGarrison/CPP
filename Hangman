/**
* @author: Garrison
*
* @project: Hangman (игра Виселица)
* @version: 1.0
* @date: 09.05.2021
*
* std: C++ 11
* ide: CodeBlocks 20.03
*
* about: программа "классическая игра Виселица" из книги
*        "Изучаем С++ через программирование игр" Майк Доусон. Издательство "Питер",2021 г.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
//#include <clocale>
#include <windows.h>

using namespace std;

int main()
{
    //setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода


    /* Подготовка, объявление переменных и констат */
    const int MAX_WRONG = 8;  //максимально допустимое кол-во ошибок
    vector<string> words;  //подборка слов для загадывания
    words.push_back("толерантность");
    words.push_back("экспонат");
    words.push_back("эпиграф");
    words.push_back("жульен");
    words.push_back("парашютист");
    words.push_back("выхухоль");
    words.push_back("россомаха");
    words.push_back("галстук");
    words.push_back("скоросшиватель");
    words.push_back("перпендикуляр");
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(words.begin(), words.end());
    const string word = words[0];  //берём 1-е слово после перемешивания массива слов
    int wrong = 0;  //кол-во ошибочных вариантов
    string soFar(word.size(), '-');  //часть слова открытая на данный момент
    string used = "";  //уже угаданные буквы
    //cout << "Welcome to Hangman. Good luck!\n";
    cout << "Добро пожаловать в игру «Виселица». Желаю удачи!\n" << endl;

    /* Основной цикл программы */
    while (wrong < MAX_WRONG && soFar != word) {
        cout << "У Вас " << (MAX_WRONG - wrong);
        cout << " попыток угадать слово\n";
        cout << "Вы использовали следующие буквы:\n" << used << endl;
        cout << "слово: " << soFar << endl;

        char guess;
        cout << "\n\nВведите букву: ";
        cin >> guess;
        guess = tolower(guess);  //перевод в нижний регистр

        while (used.find(guess) != string::npos) {
            cout << "Вы уже догадались " << guess << endl;
            cout << "\n\nВведите букву: ";
            cin >> guess;
            guess = tolower(guess);
        }

        used += guess;
        used += ' ';

        if (word.find(guess) != string::npos) {
            cout << "Верно! " << guess << " находиться в слове.\n";
            // обновляем переменную soFar, включив в неё новую угаданную букву
            for (int i = 0; i < word.length(); ++i) {
                if (word[i] == guess)
                    soFar[i] = guess;
            }
        }
        else {
            cout << "Извини, " << guess << " такой буквы нет в слове.\n";
            ++wrong;
        }
    }

    /* Конец игры */
    if (wrong == MAX_WRONG)
        cout << "Увы, Вы проиграли\n";
    else
        cout << "Вы угадали!!!\n";

    cout << "Угадаваемое слово: " << word << endl;


    return 0;
}
