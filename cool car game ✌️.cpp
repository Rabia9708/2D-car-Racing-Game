//rabia parts💀
#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "raylib.h"   // the raylib library 
using namespace std;

const int TRACK_ROWS = 20;               // length of the road
const int NUM_LANES = 3;                // 3 lanes as left, middle, right
const int CAR_ROW = TRACK_ROWS - 2;

// noor🥀
const int ROW_H = 32;                              // height of one road row in pixels
const int LANE_W = 110;                            // width of one lane in pixels
const int KERB_W = 10;                             // width of the red and white edge of the road
const int HUD_H = 60;                              // height of the score bar at the top
const int SCREEN_W = 800;                          // window width
const int SCREEN_H = HUD_H + TRACK_ROWS * ROW_H;   // window height
const int ROAD_W = NUM_LANES * LANE_W;             // width of the grey road
const int ROAD_X = (SCREEN_W - ROAD_W) / 2;        // x position where the grey road starts
const float STEP_TIME = 0.12f;                     // seconds between road steps (game speed)

// areej💖
// draws one F1 car, cx and cy are the centre of the car in pixels
void drawF1Car(int cx, int cy, Color body, bool isPlayer)
{
    Color dark = { 30, 30, 30, 255 };
    Color wheel = { 10, 10, 10, 255 };
    Color helmet = { 240, 240, 240, 255 };    // white helmet for enemy drivers
    if (isPlayer)
    {
        helmet = { 255, 230, 0, 255 };        // yellow helmet for the player
    }

    DrawRectangle(cx - 24, cy - 22, 12, 18, wheel);    // front left wheel
    DrawRectangle(cx + 12, cy - 22, 12, 18, wheel);    // front right wheel
    DrawRectangle(cx - 26, cy + 4, 13, 22, wheel);     // rear left wheel
    DrawRectangle(cx + 13, cy + 4, 13, 22, wheel);     // rear right wheel
    DrawRectangle(cx - 12, cy - 15, 24, 3, dark);      // front axle

    DrawRectangle(cx - 4, cy - 28, 8, 16, body);       // nose
    DrawRectangle(cx - 8, cy - 14, 16, 40, body);      // main body
    DrawRectangle(cx - 13, cy - 2, 26, 22, body);      // side pods
    DrawRectangle(cx - 2, cy - 26, 4, 24, WHITE);      // white racing stripe
    DrawCircle(cx, cy + 4, 6, helmet);                 // driver helmet

    DrawRectangle(cx - 25, cy - 31, 50, 6, dark);      // front wing
    DrawRectangle(cx - 23, cy + 24, 46, 6, dark);      // rear wing
    DrawRectangle(cx - 23, cy + 22, 3, 10, body);      // rear wing end plate (left)
    DrawRectangle(cx + 20, cy + 22, 3, 10, body);      // rear wing end plate (right)
}
//rabia 💀
// enemy car, every lane gets a different colour
void drawEnemyCar(int cx, int cy, int lane)
{
    Color colours[3] = { {0,100,255,255}, {255,130,0,255}, {170,60,220,255} };   // blue, orange, purple
    drawF1Car(cx, cy, colours[lane % 3], false);
}

// the player's car is red like a Ferrari
void drawPlayerCar(int cx, int cy)
{
    drawF1Car(cx, cy, Color{ 220, 0, 0, 255 }, true);
}

// the explosion that is shown when the player crashes
void drawExplosion(int cx, int cy)
{
    DrawCircle(cx, cy, 44, ORANGE);
    DrawCircle(cx, cy, 32, YELLOW);
    DrawText("BOOOM", cx - MeasureText("BOOOM", 20) / 2, cy - 10, 20, MAROON);
}
// areej💖
// draws one strip of grass made of blocks with different shades of green
// y = top of the strip, w = position in the world (so the grass scrolls with the road)
// xStart and xEnd = where the grass begins and ends, side = 0 for left grass, 1 for right grass
void drawGrass(int y, int w, int xStart, int xEnd, int side)
{
    // 5 different shades of green
    Color shades[5] = { {34,139,34,255}, {46,160,46,255}, {0,120,0,255}, {60,179,60,255}, {20,100,20,255} };
    int b = 0;   // number of the block

    for (int x = xStart; x < xEnd; x = x + 45)
    {
        int blockW = 45;
        if (x + blockW > xEnd)
        {
            blockW = xEnd - x;
        }

        // picks a shade using the position, which gives stripes and patches of different greens
        int idx = ((w / 4) + b * 3 + side * 2 + (w / 12) * b) % 5;
        DrawRectangle(x, y, blockW, ROW_H + 1, shades[idx]);

        // once in a while a small bush is placed on the grass
        if ((w * 31 + b * 17 + side * 7) % 29 == 0)
        {
            DrawCircle(x + blockW / 2, y + ROW_H / 2, 12, Color{ 0, 80, 0, 255 });
            DrawCircle(x + blockW / 2 - 3, y + ROW_H / 2 - 3, 6, Color{ 20, 120, 20, 255 });
        }
        b++;
    }
}

// RABIA PART💀
int updateHighScore(int score, int highScore)
{
    if (score > highScore)
        highScore = score;

    return highScore;
}
// areej part 💖
void showStartScreen(int highScore)
{
    // waits here until ENTER is pressed (or the window is closed)
    while (!WindowShouldClose() && !IsKeyPressed(KEY_ENTER))
    {
        BeginDrawing();
        ClearBackground(Color{ 34, 139, 34, 255 });

        DrawText("===== 2D CAR RACING GAME =====", 130, 100, 36, WHITE);
        DrawText("Avoid the other cars.", 270, 200, 26, WHITE);
        DrawText("Controls  : A / D or Left / Right arrows", 190, 250, 26, WHITE);
        DrawText(("Best score so far: " + to_string(highScore)).c_str(), 280, 300, 26, WHITE);
        DrawText("Press ENTER to hit the road...", 235, 400, 26, YELLOW);
        drawPlayerCar(SCREEN_W / 2, 520);

        EndDrawing();
    }
}
// NOOR PART🥀
bool asktoPlayAgain(int score, int highScore)
{
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{ 20, 90, 20, 255 });

        DrawText("==== GAME OVER ====", 230, 150, 40, WHITE);
        DrawText(("Your Score: " + to_string(score)).c_str(), 300, 250, 30, WHITE);
        DrawText(("High Score: " + to_string(highScore)).c_str(), 300, 290, 30, WHITE);
        DrawText("Press R or ENTER to restart", 240, 380, 28, YELLOW);
        DrawText("Press Q or ESC to quit", 270, 420, 28, YELLOW);

        EndDrawing();

        if (IsKeyPressed(KEY_R) || IsKeyPressed(KEY_ENTER)) {
            return true;
        }
        if (IsKeyPressed(KEY_Q) || IsKeyPressed(KEY_ESCAPE)) {
            return false;
        }
    }
    return false;   // the window was closed
}
//AREEJ PART💖
bool checkCollision(const int track[], int carLane)
{
    return track[CAR_ROW] == carLane;
}
//NOOR PART🥀
void handleInput(int& carLane)
{
    // A or the left arrow key
    if ((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && carLane > 0)
    {
        carLane--; //moves car one lane left
    }
    // D or the right arrow key
    else if ((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && carLane < NUM_LANES - 1)
    {
        carLane++; //moves car one lane right
    }
}

//areej's part💖
void moveObstacles(int track[], int& gapCounter, int& scroll) {
    //shift everything down one row
    for (int r = TRACK_ROWS - 1; r > 0; r--) {
        track[r] = track[r - 1];
    }
    track[0] = -1;   // -1 means the new top row is empty for now
    gapCounter++;

    // only drop a new obstacle after a gap of 4+ rows, and even then
    // only half the time, so the road doesn't get too crowded
    if (gapCounter >= 4 && rand() % 2 == 0) {
        track[0] = rand() % NUM_LANES;
        gapCounter = 0;
    }

    scroll++;   // used to make the lane dividers look like they move
}
// rest of code (rabia)💀
// smooth = how far the road is between two steps (0.0 to 1.0), it makes the movement look smooth
void drawGame(const int track[], int carLane, int score,
    int highScore, int scroll, bool crashed, float smooth)
{
    BeginDrawing();
    ClearBackground(Color{ 34, 139, 34, 255 });

    // first the grass, the road edges, the grey road and the lane dividers are drawn
    for (int r = -1; r < TRACK_ROWS; r++)
    {
        int y = HUD_H + (int)((r + smooth) * ROW_H);   // top of this row on the screen
        int w = scroll - r + TRACK_ROWS + 5;           // position in the world, never negative

        drawGrass(y, w, 0, ROAD_X - KERB_W, 0);                          // grass on the left side of the road
        drawGrass(y, w, ROAD_X + ROAD_W + KERB_W, SCREEN_W, 1);          // grass on the right side of the road

        // red and white stripes on both edges of the road
        Color kerbColor = WHITE;
        if ((w / 2) % 2 == 0)
        {
            kerbColor = Color{ 200, 30, 30, 255 };
        }
        DrawRectangle(ROAD_X - KERB_W, y, KERB_W, ROW_H + 1, kerbColor);// this creates the left boundary of the roaad
        DrawRectangle(ROAD_X + ROAD_W, y, KERB_W, ROW_H + 1, kerbColor);// right border

        DrawRectangle(ROAD_X, y, ROAD_W, ROW_H + 1, Color{ 60, 60, 60, 255 });   // grey road

        for (int i = 1; i < NUM_LANES; i++)
        {
            if ((r + scroll) % 2 == 0)// if r+ croll is even a white dash is drawn
            {
                DrawRectangle(ROAD_X + i * LANE_W - 2, y + 5, 4, ROW_H - 10, WHITE);
            }
        }
    }

    // then the cars are drawn on top of the road
    for (int r = 0; r < TRACK_ROWS; r++)//this runs till for all the runs 
    {
        for (int i = 0; i < NUM_LANES; i++)// there are 3 lanes so it controls the lnes of game 
        {
            int cx = ROAD_X + i * LANE_W + LANE_W / 2;                       // middle of this lane
            int cy = HUD_H + (int)((r + smooth) * ROW_H) + ROW_H / 2;        // middle of this row

            if (track[r] == i)// checks the position of enemy car 
            {
                drawEnemyCar(cx, cy, i);// enemy is printed as car
            }
            if (r == CAR_ROW && i == carLane)// it chcks whetthjer the player has the same row as the enemy and the same lane as enemy
            {
                cy = HUD_H + r * ROW_H + ROW_H / 2;   // the player's car does not slide, only the road does
                if (crashed)// if crashed is true them boomis printed 
                {
                    drawExplosion(cx, cy);
                }
                else
                {
                    drawPlayerCar(cx, cy);// else the player continous toplay
                }
            }
        }
    }// noor part🥀

    // the score bar at the top
    DrawRectangle(0, 0, SCREEN_W, HUD_H, Color{ 20, 20, 20, 255 });
    string scoreText = "Score: " + to_string(score) + "   High: " + to_string(highScore);//covet the score and highscore to string and stores as score: highscore:
    DrawText(scoreText.c_str(), 20, 15, 30, WHITE);

    DrawText("Move: A / D or arrow keys", 480, 22, 20, LIGHTGRAY);// this shows the movement keys 

    EndDrawing();
}
void resetRound(int track[], int& carLane, int& score,
    int& scroll, int& gapCounter)
{
    for (int i = 0; i < TRACK_ROWS; i++)
    {
        track[i] = -1;   // empty road
    }

    carLane = NUM_LANES / 2;   // start in the middle lane
    score = 0;
    scroll = 0;
    gapCounter = 0;
}//
int playGame(int highScore) {
    int track[TRACK_ROWS];
    int carLane, score, scroll, gapCounter;
    bool crashed = false;
    float timer = 0;   // counts the time until the next road step

    resetRound(track, carLane, score, scroll, gapCounter);

    while (!crashed && !WindowShouldClose()) {
        handleInput(carLane);

        timer = timer + GetFrameTime();

        // the player may have steered straight into an obstacle
        if (checkCollision(track, carLane)) {
            crashed = true;
        }
        else if (timer >= STEP_TIME) {
            timer = timer - STEP_TIME;
            moveObstacles(track, gapCounter, scroll);

            // or the road may have moved an obstacle onto us
            if (checkCollision(track, carLane)) {
                crashed = true;
            }
            else {
                score++;   // survived this step
            }
        }

        drawGame(track, carLane, score, highScore, scroll, crashed, timer / STEP_TIME);
    }

    float wait = 0;   // let the player see the BOOM for about one second
    while (wait < 0.9f && !WindowShouldClose()) {
        wait = wait + GetFrameTime();
        drawGame(track, carLane, score, highScore, scroll, crashed, 0);
    }
    return score;
}// rabia paart
// 💀
int main()
{
    InitWindow(SCREEN_W, SCREEN_H, "2D CAR RACING GAME");// opens the game window (a real GUI window instead of the console)
    SetExitKey(KEY_NULL);// so the ESC key does not close the window by itself
    SetTargetFPS(60);// the game draws 60 frames every second

    srand(static_cast<unsigned int>(time(0)));// gets a random number .....time(0) gets corrent time ....unsigned keeps it as a wholw number static_castcovrts it to the type srand will eccept

    int highScore = 0;// high score variable is initialized at 0
    bool again = true;// again variable is initialised at true

    showStartScreen(highScore);// funtion call to show the start screen

    while (again && !WindowShouldClose())
    {
        int score = playGame(highScore);// current score is stored
        highScore = updateHighScore(score, highScore);// highscore is updated everytime
        again = asktoPlayAgain(score, highScore);//will ask to restaart thegame
    }

    float wait = 0;
    while (wait < 1.5f && !WindowShouldClose())// shows the thank you message for a moment
    {
        wait = wait + GetFrameTime();
        BeginDrawing();
        ClearBackground(Color{ 20, 90, 20, 255 });
        DrawText("THANK YOU FOR PLAYING", 190, 320, 36, WHITE);
        EndDrawing();
    }

    CloseWindow();// closes the game window

    return 0;
}