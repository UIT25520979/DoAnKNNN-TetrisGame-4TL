#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

#define H 20
#define W 15

char board[H][W] = {};

char blocks[28][4][4] = {
    {{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '},{' ','I',' ',' '}},
    {{' ',' ',' ',' '},{'I','I','I','I'},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','O','O',' '},{' ','O','O',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','T',' ',' '},{'T','T','T',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','T',' ',' '},{' ','T','T',' '},{' ','T',' ',' '},{' ',' ',' ',' '}},
    {{' ',' ',' ',' '},{'T','T','T',' '},{' ','T',' ',' '},{' ',' ',' ',' '}},
    {{' ','T',' ',' '},{'T','T',' ',' '},{' ','T',' ',' '},{' ',' ',' ',' '}},
    {{' ','S','S',' '},{'S','S',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'S',' ',' ',' '},{'S','S',' ',' '},{' ','S',' ',' '},{' ',' ',' ',' '}},
    {{'Z','Z',' ',' '},{' ','Z','Z',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ',' ','Z',' '},{' ','Z','Z',' '},{' ','Z',' ',' '},{' ',' ',' ',' '}},
    {{' ',' ','L',' '},{'L','L','L',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{'L',' ',' ',' '},{'L',' ',' ',' '},{'L','L',' ',' '},{' ',' ',' ',' '}},
    {{'L','L','L',' '},{'L',' ',' ',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','L','L',' '},{' ',' ','L',' '},{' ',' ','L',' '},{' ',' ',' ',' '}},
    {{'J',' ',' ',' '},{'J','J','J',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','J','J',' '},{' ','J',' ',' '},{' ','J',' ',' '},{' ',' ',' ',' '}},
    {{'J','J','J',' '},{' ',' ','J',' '},{' ',' ',' ',' '},{' ',' ',' ',' '}},
    {{' ','J',' ',' '},{' ','J',' ',' '},{'J','J',' ',' '},{' ',' ',' ',' '}}
};

int x = 4, y = 1, b = 0;

void gotoxy(int x, int y) {
    COORD c = { (short)x, (short)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void boardDelBlock() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[b][i][j] != ' ' && y + i < H)
                board[y + i][x + j] = ' ';
        }
    }
}

void block2Board() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
        }
    }
}

void initBoard() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == H - 1 || j == 0 || j == W - 1) board[i][j] = (char)178;
            else board[i][j] = ' ';
        }
    }
}

void draw() {
    gotoxy(0, 0);
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cout << board[i][j];
        }
        cout << endl;
    }
}

bool canMove(int dx, int dy) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[b][i][j] != ' ') {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1) return false;
                if (board[ty][tx] != ' ') return false;
            }
        }
    }
    return true;
}

bool spinBlock(int newType) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (blocks[newType][i][j] != ' ') {
                int tx = x + j;
                int ty = y + i;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1 || board[ty][tx] != ' ') return false;
            }
        }
    }
    return true;
}

void removeLine() {
    int j;
    for (int i = H - 2; i > 0; i--) {
        for (j = 1; j < W - 1; j++)
            if (board[i][j] == ' ') break;

        if (j == W - 1) {
            for (int ii = i; ii > 0; ii--)
                for (int j = 1; j < W - 1; j++)
                    board[ii][j] = board[ii - 1][j];
            i++;
            draw();
            _sleep(200);
        }
    }
}

int main() {
    system("chcp 437");
    srand((unsigned int)time(0));

    int basicBlocks[] = { 0, 2, 3, 7, 9, 11, 15 };
    b = basicBlocks[rand() % 7];

    system("cls");
    initBoard();

    if (!canMove(0, 0)) {
        cout << "GAME OVER!" << endl;
        return 0;
    }

    DWORD lastUpdateTime = GetTickCount();

    while (true) {
        if (kbhit()) {
            boardDelBlock();
            char inputKey = getch();
            if (inputKey == 'a' && canMove(-1, 0)) x--;
            if (inputKey == 'd' && canMove(1, 0)) x++;
            if (inputKey == 's' && canMove(0, 1)) y++;
            if (inputKey == 'w') {
                int nextType = b;
                if (b == 0 || b == 1) nextType = (b == 0) ? 1 : 0;
                else if (b >= 3 && b <= 6) nextType = (b == 6) ? 3 : b + 1;
                else if (b == 7 || b == 8) nextType = (b == 7) ? 8 : 7;
                else if (b == 9 || b == 10) nextType = (b == 9) ? 10 : 9;
                else if (b >= 11 && b <= 14) nextType = (b == 14) ? 11 : b + 1;
                else if (b >= 15 && b <= 18) nextType = (b == 18) ? 15 : b + 1;
                if (spinBlock(nextType)) b = nextType;
            }
            if (inputKey == 'q') break;
            block2Board();
            draw();
        }

        if (GetTickCount() - lastUpdateTime > 200) {
            boardDelBlock();
            if (canMove(0, 1)) y++;
            else {
                block2Board();
                removeLine();
                x = 4; y = 1;
                b = basicBlocks[rand() % 7];
                if (!canMove(0, 0)) {
                    system("cls");
                    cout << "GAME OVER!" << endl;
                    break;
                }
            }
            block2Board();
            draw();
            lastUpdateTime = GetTickCount();
        }
        Sleep(10);
    }
    return 0;
}
