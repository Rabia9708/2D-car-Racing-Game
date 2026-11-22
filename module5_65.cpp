int playGame(int highScore){
    int track[TRACK_ROWS];
    int carLane, score, scroll, gapCounter;
    bool crashed = false;

    resetRound(track, carLane, score, scroll, gapCounter);
    system("cls");

    while (!crashed){
        handleInput(carLane);

        // the player may have steered straight into an obstacle
        if (checkCollision(track, carLane)) {
            crashed = true;
        }else {
            moveObstacles(track, gapCounter, scroll);

            // or the road may have moved an obstacle onto us
            if (checkCollision(track, carLane)) {
                crashed = true;
            }else {
                score++;   // survived this step
            }
        }

        drawGame(track, carLane, score, highScore, scroll, crashed);
        Sleep(120);   // game speed
    }

    Sleep(900);   // let the player see the BOOM
    return score;
}
