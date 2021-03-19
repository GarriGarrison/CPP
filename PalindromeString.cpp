#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Определяет, будет ли слово палиндромом
// text может быть строкой, содержащей строчные символы английского алфавита и пробелы
// Пустые строки и строки, состоящие только из пробелов, — это не палиндромы
bool IsPalindrome(const string& text) {
    // Напишите недостающий код
    bool polindrom_flag = true;
    string test;
    bool only_space_flag = true;
    //vector

    if (text.empty())
        return false;

    for (const char c : text) {
        if (c != ' ')
            test += c;
    }

    if (test.size() == 1)
        return true;

    for (int i = 0; i < test.size() / 2; ++i) {
        if (test[i] != test[test.size() - 1 - i])
            polindrom_flag = false;
        else
            if (test[i] != ' ')
                only_space_flag = false;
    }

 

    if (polindrom_flag && !only_space_flag)
        return true;
    else
        return false;
}

int main() {
    string text;
    getline(cin, text);

    if (IsPalindrome(text)) {
        cout << "palindrome"s << endl;
    }
    else {
        cout << "not a palindrome"s << endl;
    }
}
