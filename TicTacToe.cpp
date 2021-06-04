/**
* @author: Garrison
*
* @project: Tic Tac Toe (игра Крестики-Нолики)
* @version: 1.1
* @date: 04.06.2021
*
* std: C++ 11
* ide: CodeBlocks 20.03
*
* about: программа "классическая игра Крестики-Нолики" из книги
*        "Изучаем С++ через программирование игр" Майк Доусон. Издательство "Питер",2021 г.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <clocale>
//#include <windns.h>

using namespace std;

/* Global constants */
const char X = 'X';
const char O = 'O';
const char EMPTY = ' ';
const char TIE = 'T';
const char NO_ONE = 'N';

/** Prototypes function */
void Instructions();  /* вывод на экран правила игры */
char AskYesNo(string question);  /* вопрос пользователю - "да" или "нет" */
int AskNumber(string question, int high, int low=0);  /* запрашивает у пользователя число из определённого диапазона */
char HumanPiece();  /* спрашивает, хочит ли пользователь ходить первым (по традиции Х ходят первыми) */
char Opponent(char piece);  /* узнаёт фигуру пользователя (Х/О) -> возвращает фигуру компьютеру */
void DisplayBoard(const vector<char>& board);  /* отображает переданное ей игравое поле */
char Winner(const vector<char>& board);  /* получает игровое поле и возвращает победителя */
bool IsLegal(const vector<char>& board, int move);  /* получает игровое поле и сделанный ход, вовращает корректность хода */
int HumanMove(const vector<char>& board, char human);  /* проверяет корректность хода пользователя */
int ComputerMove(vector<char> board, char computer);  /* делает ход компьютера */
void AnnounceWinner(char winner, char computer, char human);  /* объявляет победителя партии или констатирует ничью */


/** -= MAIN =- */
int main()
{
    setlocale(LC_ALL, "rus");
    //SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

    int move;
    const int NUM_SQUARES = 9;
    vector<char> board(NUM_SQUARES, EMPTY);
    Instructions();
    char human = HumanPiece();
    char computer = Opponent(human);
    char turn = X;
    DisplayBoard(board);

    while (Winner(board) == NO_ONE) {
        if (turn == human) {
            move = HumanMove(board, human);
            board[move] = human;
        }
        else {
            move = ComputerMove(board, computer);
            board[move] = computer;
        }

        DisplayBoard(board);
        turn = Opponent(turn);
    }

    AnnounceWinner(Winner(board), computer, human);

    return 0;
}


/** Functions */
void Instructions()
{
    cout << "Добро пожаловать в финальную битву человек-машина: крестики-нолики.\n";
    cout << "--где человеческий мозг противостоит кремниевому процессору\n\n";
    cout << "Сделайте свой ход, введя число от 1 до 9. Число\n";
    cout << "соответствует желаемому положению доски, как показано на рисунке:\n\n";
    cout << " 1 | 2 | 3 \n";
    cout << " --------- \n";
    cout << " 4 | 5 | 6 \n";
    cout << " --------- \n";
    cout << " 7 | 8 | 9 \n\n";
    cout << "Приготовься, человек. Битва вот-вот начнется.\n\n";
}


char AskYesNo(string question)
{
    char response;

    do {
        cout << question << " (y/n): ";
        cin >> response;
    }
    while (response != 'y' && response != 'n');

    return response;
}


int AskNumber(string question, int high, int low)
{
    int number;

    ++high;
    ++low;

    do {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    }
    while (number > high || number < low);

    return --number;
}


char HumanPiece()
{
    char go_first = AskYesNo("Хочешь ходить первым?");
    if (go_first == 'y') {
        cout << "\nТогда сделайте первый шаг.\n";
        return X;
    }
    else {
        cout << "\nТвоя храбрость погубит тебя...Я пойду первым.\n";
        return O;
    }
}


char Opponent(char piece)
{
    if (piece == X)
        return O;
    else
        return X;
}


void DisplayBoard(const vector<char>& board)
{
    cout << "\n\t" << board[0] << " | " << board[1] << " | " << board[2];
    cout << "\n\t" << " ---------";
    cout << "\n\t" << board[3] << " | " << board[4] << " | " << board[5];
    cout << "\n\t" << " ---------";
    cout << "\n\t" << board[6] << " | " << board[7] << " | " << board[8];
    cout << "\n\n";
}


char Winner(const vector<char>& board)
{
    /* Все возможные выигрышные ряды */
    const int WINNING_ROWS[8][3] = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
        {0, 3, 6},
        {1, 4, 7},
        {2, 5, 8},
        {0, 4, 8},
        {2, 4, 6}
    };

    /* Проверка на наличия победителя */
    const int TOTAL_ROWS = 8;
    // если в одном из выйгрышных рядов уже присутствуют три одинаковых значения
    // (причём они не рапвны EMPTY), то победитель определился
    for (int row = 0; row < TOTAL_ROWS; ++row) {
        if ((board[WINNING_ROWS[row][0]] != EMPTY) &&
            (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) &&
            (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]])
            ) {
                return board[WINNING_ROWS[row][0]];
        }
    }

    // поскольку победитель не определился, проверяем, не наступила ли ничья
    // (остались ли на поле пустые клетки)
    if (count(board.begin(), board.end(), EMPTY) == 0)
        return TIE;

    // поскольку победитель не определился, но и ничья ещё не наступила
    // игра продолжается
    return NO_ONE;
}


inline bool IsLegal(int move, const vector<char>& board)
{
    return (board[move] == EMPTY);
}


int HumanMove(const vector<char>& board, char human)
{
    int move = AskNumber("Какую ячейку займёшь?", (board.size()-1));

    while (!IsLegal(move, board)) {
        cout << "\nЭта ячейка уже занята, глупый человек.\n";
        move = AskNumber("Какую ячейку займёшь?", (board.size()-1));
    }
    cout << "Хорошо...\n";

    return move;
}


int ComputerMove(vector<char> board, char computer)
{
    /* Шаг 1 */
    // если у компьютера сделать ход, который принесёт ему победу, - сделать этот ход
    unsigned int move = 0;
    bool found = false;
    while (!found && move < board.size()) {
        if (IsLegal(move, board)) {
            board[move] = computer;
            found = (Winner(board) == computer);
            board[move] = EMPTY;
        }
        if (!found)
            ++move;
    }

    /* Шаг 2 */
    // иначе, если человек может победить следующим ходом, блокировать этот ход
    if (!found) {
        move = 0;
        char human = Opponent(computer);
        while (!found && move < board.size()) {
            if (IsLegal(move, board)) {
                board[move] = human;
                found = (Winner(board) == human);
                board[move] = EMPTY;
            }
            if (!found)
                ++move;
        }
    }

    /* Шаг 3 */
    // иначе занять следующим ходом оптимальную свободную клетку
    if (!found) {
        move = 0;
        unsigned int i = 0;
        const int BEST_MOVE[] = {4, 0, 2, 6, 8, 1, 3, 5, 7};

        // выбрать оптимальную свободную клетку
        while (!found && i < board.size()) {
            move = BEST_MOVE[i];
            if (IsLegal(move, board))
                found = true;
            ++i;
        }
    }

    cout << "Я займу ячейку - " << move << endl;
    return move;
}


void AnnounceWinner(char winner, char computer, char human)
{
    if (winner == computer) {
        cout << winner << " - выйграл!\n";
        cout << "Как я и предсказывал, человек, я снова торжествую - доказательство\n";
        cout << "что компьютеры превосходят людей во всех отношениях.\n";
    }
    else if (winner == human) {
        cout << winner << " 's won!\n";
        cout << "Нет, нет! Этого не может быть! Каким-то образом ты обманул меня, человек.\n";
        cout << "Но больше этого никогда не произойдёт! Я, компьютер, клянусь в этом!\n";
    }
    else {
        cout << "Это ничья.\n";
        cout << "Тебе очень повезло, человек, и ты каким-то образом сумел связать меня.\n";
        cout << "Празднуй...ибо это лучшее, чего ты когда - либо смог достигнуть.\n";
    }
}
