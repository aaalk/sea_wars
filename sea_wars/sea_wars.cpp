using namespace std;

#include <iostream>
#include <string>
#include <cstring>
#include <conio.h>


const int board_size = 10;
const int ship_num = 8;
int board_1[board_size][board_size]{};
int board_2[board_size][board_size]{};
int board_hod_1[board_size][board_size]{};
int board_hod_2[board_size][board_size]{};
void initializeBoard();
void printBoard();
void check();
void placeShips();
int rowcol[2]{};
string rco[2]{};
string str_stolb[2]{ "строкy", "столбец" };
bool f = false;
int ship_added = 0;
bool isPlayer1Turn = true;


void initializeBoard(int board[board_size][board_size]) {
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            board[i][j] = 0;
        }
    }
}

void printBoard(int board[board_size][board_size]) {
    cout << "   ";
    for (int j = 0; j < board_size; j++) {
        cout << j << " ";
    }
    cout << "\n";
    for (int i = 0; i < board_size; i++) {
        cout << i << " |";
        for (int j = 0; j < board_size; j++) {
            cout << board[i][j] << "|";
        }
        cout << "\n";
    }
}

void check() {
    for (int j = 0; j < 2; j++) {
        f = false;
        while (!f) {
            cout << "Введите " + str_stolb[j] << endl;
            getline(cin, rco[j]);
            if (rco[j].length() != 1 || !isdigit(rco[j][0])) {
                cout << "Ошибка. Нужно ввести цифру!" << endl;
                continue;
            }
            rowcol[j] = stoi(rco[j]);
            if (0 <= rowcol[j] < 10) {
                f = true;
            }
            else {
                cout << "Ошибка. Нужно ввести числа от 0 до 9: ";
            }
        }
    }
}

void placeShips(int board[board_size][board_size]) {
    cout << (isPlayer1Turn ? "Игрок 1" : "Игрок 2") << " расставьте свои кораблики\n";
    while (ship_added < ship_num) {
        cout << "Введите ряд и столбец кораблика " << ship_added + 1 << ": ";
        check();
        if (board[rowcol[0]][rowcol[1]] != 1) {
            board[rowcol[0]][rowcol[1]] = 1;
            ship_added++;
        }
        else {
            cout << "Это поле занято, введите другое\n";
        }
    }
    ship_added = 0;
    isPlayer1Turn = !isPlayer1Turn;

}

bool isGameOver(int board[board_size][board_size]) {
    int numShips = 0;
    int numSunkShips = 0;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            if (board[i][j] == 1) {
                numShips++;
                bool isSunk = true;
                for (int k = 0; k < board_size; k++) {
                    if (board[i][k] == 1 || board[k][j] == 1) {
                        isSunk = false;
                        break;
                    }
                }
                if (isSunk) {
                    numSunkShips++;
                }
            }
        }
    }
    return numShips == numSunkShips;
}

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "Правила: каждому игроку нужно расставить свои кораблики на клеточки(1 корабль – 1 клетка) по координатам.\n";
    cout << "Координаты определяются двумя цифрами от 0 до 9(сначала вводится ряд, потом столбец).\n";
    cout << "Каждый игрок будет видеть поле со своими ходами. И если повторно вводить клетку, которую уже проверяли, то ход переходит к другому игроку\n";
    cout << "0 – клетка не проверялась, что под ней - неизвестно\n";
    cout << "2 - корабль был тут\n";
    cout << "3 – корабля на этой клетке нет\n";
    cout << "\n";

    initializeBoard(board_1);
    initializeBoard(board_2);

    placeShips(board_1);
    system("cls");
    placeShips(board_2);
    system("cls");


    while (!isGameOver(board_1) && !isGameOver(board_2)) {
        if (isPlayer1Turn) {
            printBoard(board_hod_1);
            cout << "Игрок 1, ваша очередь\n";
            cout << "Введите ряд и столбец атаки " << ": ";

            check();
            system("cls");

            if (board_2[rowcol[0]][rowcol[1]] == 1) {
                cout << "Попал!\n";
                board_2[rowcol[0]][rowcol[1]] = 2;
                board_hod_1[rowcol[0]][rowcol[1]] = 2;

            }
            else if (board_2[rowcol[0]][rowcol[1]] == 0) {
                cout << "Не попал!\n";
                board_2[rowcol[0]][rowcol[1]] = 3;
                board_hod_1[rowcol[0]][rowcol[1]] = 3;

            }
            else {
                cout << "Уже пробовали эту клетку и упустили свой шанс..\n";
            }
        }

        else {
            printBoard(board_hod_2);
            cout << "Игрок 2, ваша очередь\n";
            cout << "Введите ряд и столбец атаки " << ": ";

            check();
            system("cls");

            if (board_1[rowcol[0]][rowcol[1]] == 1) {
                cout << "Попал!\n";
                board_1[rowcol[0]][rowcol[1]] = 2;
                board_hod_2[rowcol[0]][rowcol[1]] = 2;

            }
            else if (board_1[rowcol[0]][rowcol[1]] == 0) {
                cout << "Не попал!\n";
                board_1[rowcol[0]][rowcol[1]] = 3;
                board_hod_2[rowcol[0]][rowcol[1]] = 3;

            }
            else {
                cout << "Уже пробовали эту клетку и упустили свой шанс..\n";
            }
        }

        isPlayer1Turn = !isPlayer1Turn;
    }

    cout << (isPlayer1Turn ? "Игрок 2" : "Игрок 1") << " Выиграл!!\n";

    cout << "Поле 1 игрока:\n";
    cout << "0 - пустая клетка\n";
    cout << "1 - кораблик стоит тут\n";
    cout << "2 - кораблик был убит противником\n";
    cout << "3 - клетка проверялась противником, и кораблика там нет\n";

    printBoard(board_1);

    cout << "Поле 2 игрока:\n";
    cout << "0 - пустая клетка\n";
    cout << "1 - кораблик стоит тут\n";
    cout << "2 - кораблик был убит противником\n";
    cout << "3 - клетка проверялась противником, и кораблика там нет\n";

    printBoard(board_2);
}


