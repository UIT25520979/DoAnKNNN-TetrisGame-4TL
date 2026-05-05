#include "spinningBlock.h"
//----------------------------------------------------//
const int spinningBlock::SHAPES[4][4][4][4] = {
    // 0: I-Piece
    {{{0,0,0,0},{1,1,1,1},{0,0,0,0},{0,0,0,0}}, {{0,0,1,0},{0,0,1,0},{0,0,1,0},{0,0,1,0}}, {{0,0,0,0},{0,0,0,0},{1,1,1,1},{0,0,0,0}}, {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}}},
    // 1: L-Piece
    {{{0,0,1,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, {{0,1,0,0},{0,1,0,0},{0,1,1,0},{0,0,0,0}}, {{0,0,0,0},{1,1,1,0},{1,0,0,0},{0,0,0,0}}, {{1,1,0,0},{0,1,0,0},{0,1,0,0},{0,0,0,0}}},
    // 2: T-Piece
    {{{0,1,0,0},{1,1,1,0},{0,0,0,0},{0,0,0,0}}, {{0,1,0,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}, {{0,0,0,0},{1,1,1,0},{0,1,0,0},{0,0,0,0}}, {{0,1,0,0},{1,1,0,0},{0,1,0,0},{0,0,0,0}}},
    // 3: Z-Piece
    {{{1,1,0,0},{0,1,1,0},{0,0,0,0},{0,0,0,0}}, {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}}, {{0,0,0,0},{1,1,0,0},{0,1,1,0},{0,0,0,0}}, {{0,1,0,0},{1,1,0,0},{1,0,0,0},{0,0,0,0}}}
};

spinningBlock::spinningBlock() {
    rotationState = 0;
    BlockType = I_PIECE;
    currentVelocity = MIN_SPEED;
    wasWDownLastFrame = false;
    lastPressTime = std::chrono::steady_clock::now();
}

//main function 
void spinningBlock::rotate() {
    rotationState = (rotationState + 1) % 4;
    lastPressTime = std::chrono::steady_clock::now();
}

void spinningBlock::updateVelocity(bool isholdingW) {
    if (isholdingW) {
        if (currentVelocity < MAX_SPEED) {
            currentVelocity += 2.0f;
        }
    }
    else {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = now - lastPressTime;
        if (elapsed.count() > RESET_THRESHOLD) {
            currentVelocity = MIN_SPEED;
        }
    }
}
//-----------------------------------------------------//
//graphic for tester func//
void spinningBlock::setPiece(PieceType newType) {
    BlockType = newType;
    rotationState = 0;
}

int spinningBlock::getCell(int x, int y) const {
    if (x < 0 || x >= 4 || y < 0 || y >= 4) return 0;
    return SHAPES[BlockType][rotationState][y][x];
}
//--------------------------------------------//
//package
void spinningBlock::handleW(bool isWPress) {
    //fresh spin -> spin
    if (isWPress && !wasWDownLastFrame) {
        rotate();
    }
    // hold w? spin faster
    updateVelocity(isWPress);
    // save the spin so refresh easily
    wasWDownLastFrame = isWPress;
}
//---------------------------------------------------//
//tester function - vi du ve cach goi ham
#ifdef ENABLE_INTERACTIVE_TESTER
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void spinningBlock::runInteractiveTest() {
    spinningBlock testBlock;
    bool isRunning = true;

    while (isRunning) {
        bool isWDown = false;

        //Input
        if (_kbhit()) {
            char key = _getch();
            if (key == '1') testBlock.setPiece(I_PIECE);
            else if (key == '2') testBlock.setPiece(L_PIECE);
            else if (key == '3') testBlock.setPiece(T_PIECE);
            else if (key == '4') testBlock.setPiece(Z_PIECE);
            else if (key == 27)  isRunning = false; // ESC
        }
        bool isWDown = (GetAsyncKeyState('W') & 0x8000) != 0;
        //---------------------//
        //chi can import ham nay la dc 
        testBlock.handleW(isWDown);
        //----------------------//
        //con lai la cai vi du ve cach logic hoat dong nen ko can quan tam may
        //Render
        system("cls");
        cout << "=== PRODUCTION COMPONENT TESTER ===" << endl;
        cout << "Piece: " << testBlock.getType() << " | Rotation: " << (testBlock.getRotationState() * 90) << " deg" << endl;
        cout << "Speed: " << testBlock.getVelocity() << (testBlock.getVelocity() >= 20.0f ? " [MAX]" : "") << endl;
        cout << "-----------------------------------" << endl;

        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                if (testBlock.getCell(x, y) == 1) cout << "[]";
                else cout << "  ";
            }
            cout << endl;
        }
        cout << "-----------------------------------" << endl;
        cout << "[W]: Spin  |  [1-4]: Switch Piece  |  [ESC]: Quit" << endl;

        Sleep(50);
    }
}
#endif