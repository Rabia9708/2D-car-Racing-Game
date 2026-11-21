void moveObstacles(int track[], int& gapCounter, int& scroll){
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