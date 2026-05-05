#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
#define H 20
#define W 15
char board[H][W] = {};
char blocks[][4][4] = {
    {{' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '}},
    {{' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '},
     {' ', 'I', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'I', 'I', 'I', 'I'},
     {' ', ' ', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'O', 'O', ' '},
     {' ', 'O', 'O', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'T', ' ', ' '},
     {'T', 'T', 'T', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', 'S', 'S', ' '},
     {'S', 'S', ' ', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'Z', 'Z', ' ', ' '},
     {' ', 'Z', 'Z', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {'J', ' ', ' ', ' '},
     {'J', 'J', 'J', ' '},
     {' ', ' ', ' ', ' '}},
    {{' ', ' ', ' ', ' '},
     {' ', ' ', 'L', ' '},
     {'L', 'L', 'L', ' '},
     {' ', ' ', ' ', ' '}}};

int x = 4, y = 0, b = 1;
int score = 0; // Tại đây tui thêm hệ thống tính điểm
void gotoxy(int x, int y)
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void boardDelBlock()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ' && y + j < H)
                board[y + i][x + j] = ' ';
}
void block2Board()
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
                board[y + i][x + j] = blocks[b][i][j];
}
void initBoard()
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
            if ((i == H - 1) || (j == 0) || (j == W - 1))
                board[i][j] = '#';
            else
                board[i][j] = ' ';
}
void draw()
{
    gotoxy(0, 0);
    for (int i = 0; i < H; i++, cout << endl)
        for (int j = 0; j < W; j++)
            cout << board[i][j];
    gotoxy(0, H);
    cout << "Score: " << score << "    " << endl;
}
bool canMove(int dx, int dy)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (blocks[b][i][j] != ' ')
            {
                int tx = x + j + dx;
                int ty = y + i + dy;
                if (tx < 1 || tx >= W - 1 || ty >= H - 1)
                    return false;
                if (board[ty][tx] != ' ')
                    return false;
            }
    return true;
}
int removeLine() {
    int linesCleared = 0;
    int writeRow = H - 2;

    for (int readRow = H - 2; readRow > 0; readRow--) {

        // Đầu tiên là check hàng readRow có đầy hay không sau đó khai báo biến và vòng lặp j
        // j bắt đầu từ 1 vì j=0 là viền '#', kết thúc trước W-1 cũng vì lý do đó
        bool full = true;
        for (int j = 1; j < W - 1; j++) {
            if (board[readRow][j] == ' ') {
                full = false;
                break;
            }
        }

        // Tiếp đó sẽ xử lý tùy theo kết quả
        if (full) {
            // Nếu hàng đầy -> đếm lên, bỏ qua không ghi
            // writeRow không dịch chuyển -> hàng này sẽ bị "ghi đè" sau
            linesCleared++;
        } else {
            // ngược lại nếu hàng chưa đầy -> giữ lại bằng cách copy xuống writeRow
            // Chỉ copy khi 2 con trỏ khác nhau, không thì tự copy chính nó 
            if (readRow != writeRow) {
                for (int j = 1; j < W - 1; j++)
                    board[writeRow][j] = board[readRow][j];
            }
            writeRow--; // xong rồi thì dịch writeRow lên 1 để chuẩn bị cho hàng tiếp theo
        }
    }

    // Sau đó xóa trắng phần còn thừa phía trên
    // Sau khi dồn xong, từ writeRow trở lên vẫn còn dữ liệu cũ chưa bị ghi đè
    // Do đó phải tự tay xóa, không thì rác dữ liệu hiện lên board
    for (int i = writeRow; i > 0; i--)
        for (int j = 1; j < W - 1; j++)
            board[i][j] = ' ';

    // cuối cùng trả về về số hàng xóa được để main tính điểm
    return linesCleared;
}
int main()
{
    srand(time(0));
    b = rand() % 7;
    system("cls");
    initBoard();
    while (1)
    {
        boardDelBlock();
        if (kbhit())
        {
            char c = getch();
            if (c == 'a' && canMove(-1, 0))
                x--;
            if (c == 'd' && canMove(1, 0))
                x++;
            if (c == 'x' && canMove(0, 1))
                y++;
            if (c == 'q')
                break;
        }
        if (canMove(0, 1))
            y++;
        else
        {
            block2Board();
            // Sau khi block đặt xuống mới check hàng đầy
            // Gọi hàm removeLine() trả về số hàng xóa được để tính điểm
            int lines = removeLine();
            if (lines > 0)
            {
                // Xóa càng nhiều hàng 1 lúc thì điểm nhân càng cao
                int bonus[] = {0, 100, 300, 500, 800};
                score += bonus[lines];
            }

            x = 5;
            y = 0;
            b = rand() % 7;
        }
        block2Board();
        draw();
        _sleep(200);
    }
    return 0;
}