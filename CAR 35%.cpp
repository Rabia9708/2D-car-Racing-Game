//rabia parts
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <windows.h>
using namespace std;

const int TRACK_ROWS = 20;               // length of the road
const int NUM_LANES = 3;                // 3 lanes as left, middle, right
const int CAR_ROW = TRACK_ROWS - 2;
//NOOR PART
void moveCursortotop()
{
    COORD topLeft = { 0, 0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), topLeft);
}
// RABIA PART
int updateHighScore(int score, int highScore)
{
    if (score > highScore)
        highScore = score;

    return highScore;
}
// areej part 
void showStartScreen(int highScore)
{
    system("cls");
    cout << "\n   ===== 2D CAR RACING GAME =====\n\n";
    cout << "   Avoid the obstacles (XXX).\n";
    cout << "   Controls  : A / D or Left / Right arrows\n";
    cout << "   Best score so far: " << highScore << "\n\n";
    cout << "   Press ENTER to hit the road...\n";
    int k = 0;
    while (k != 13)
    {
        k = _getch();
    }
}
// NOOR PART
bool asktoPlayAgain(int score, int highScore)
{
    system("cls");
    cout << "\n  ==== GAME OVER ====\n" << endl;
    cout << " Your Score:" << score << endl;
    cout << " Press R or ENTER to restart" << endl;
    cout << "Press Q or ESC to quit" << endl;

    while (true) {

        char k = _getch();

        if (k == 'r' || k == 'R' || k == 13) {
            return true;
        }
        if (k == 'q' || k == 'Q' || k == 27) {
            return false;
        }
    }
}
//AREEJ PART
bool checkCollision(const int track[], int carLane)
{
    return track[CAR_ROW] == carLane;
}//NOOR PART
    {
        while (_kbhit())
        {
            int k = _getch(); //reads the key which is pressed


            if (k == 0 || k == 224)
            {
                int arrow = _getch(); //reads which arrow is pressed

                if (arrow == 75 && carLane > 0)
                {
                    carLane--; //it moves car one lane left
                }
                else if (arrow == 77 && carLane < NUM_LANES - 1)
                {
                    carLane++; //moves car one lane right
                }
            }
            else if ((k == 'a' || k == 'A') && carLane > 0)
            {
                carLane--; //moves car one lane left
            }
            else if ((k == 'd' || k == 'D') && carLane < NUM_LANES - 1)
            {
                carLane++; //moves car one lane right
            }
        }
    }

