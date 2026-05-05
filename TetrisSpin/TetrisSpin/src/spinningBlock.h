#pragma once
#include<iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
using namespace std;
#define ENABLE_INTERACTIVE_TESTER
enum PieceType { I_PIECE = 0, L_PIECE, T_PIECE, Z_PIECE, COUNT };
class spinningBlock
{
private:
    int rotationState;
    PieceType BlockType;
    float currentVelocity;
    const float MIN_SPEED = 2.0f;
    const float MAX_SPEED = 20.0f;
    const double RESET_THRESHOLD = 3.0f;
    std::chrono::steady_clock::time_point lastPressTime;
    static const int SHAPES[4][4][4][4];
    bool wasWDownLastFrame;
public:
    spinningBlock();

    //Core logic
    void rotate();
    void updateVelocity(bool isHoldingW);
    void setPiece(PieceType newType);

    // Getter
    int getRotationState() const { return rotationState; }
    float getVelocity() const { return currentVelocity; }
    PieceType getType() const { return BlockType; }
    int getCell(int, int) const;

    //package function for w
    void handleW(bool);

    // spin tester
#ifdef ENABLE_INTERACTIVE_TESTER
    static void runInteractiveTest();
#endif
};

