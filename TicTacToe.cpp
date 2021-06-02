/**
* @author: Garrison
*
* @project: Tic Tac Toe (игра Крестики-Нолики)
* @version: 1.0
* @date: 02.06.2021
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
    cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
    cout << "--where human brain is pit against silicon processor\n\n";
    cout << "Make your move known by entering a number, 0 - 8. The number\n";
    cout << "corresponds to the desired board position, as illustrated:\n\n";
    cout << " 0 | 1 | 2 \n";
    cout << " --------- \n";
    cout << " 3 | 4 | 5 \n";
    cout << " --------- \n";
    cout << " 6 | 7 | 8 \n\n";
    cout << "Prepare yourself, human. The battle is about to begin. \n\n";
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

    do {
        cout << question << " (" << low << " - " << high << "): ";
        cin >> number;
    }
    while (number > high || number < low);

    return number;
}


char HumanPiece()
{
    char go_first = AskYesNo("Do you require the first move?");
    if (go_first == 'y') {
        cout << "\nThen take the first move. You will need it.\n";
        return X;
    }
    else {
        cout << "\nYour bravery will be your undoing...I will go first.\n";
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
    int move = AskNumber("Where will you move?", (board.size()-1));

    while (!IsLegal(move, board)) {
        cout << "\nThat square ia already occupied, foolish human.\n";
        move = AskNumber("Where will you move?", (board.size()-1));
    }
    cout << "Fine...\n";

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

    cout << "I shall take square number " << move << endl;
    return move;
}


void AnnounceWinner(char winner, char computer, char human)
{
    if (winner == computer) {
        cout << winner << " 's won!\n";
        cout << "As I predicted, human, I am triumphant once more -- proof\n";
        cout << "that computers are superior to humans in all regards.\n";
    }
    else if (winner == human) {
        cout << winner << " 's won!\n";
        cout << "No, no! It cannot be! Somehow you tricked me, human.\n";
        cout << "But never again! I, the computer, so swear it!\n";
    }
    else {
        cout << "It's a tie.\n";
        cout << "You were most lucky, human, and somehow managed to tie me.\n";
        cout << "Celebrate...for this is the best you will ever achieve.\n";
    }
}
