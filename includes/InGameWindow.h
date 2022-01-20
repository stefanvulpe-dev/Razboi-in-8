extern int playerA_wins, playerB_wins, nrOfMoves;

void startGame();

void setBackground(int xStart, int yStart, int xEnd, int yEnd);

void roundedRectangle(int xStart, int yStart, int xEnd, int yEnd, int color, int grosime);

void roundedRectangle2(int xStart, int yStart, int xEnd, int yEnd, int color, int grosime);

void reborderGameBoard();

void placeHomeButton(int xStart, int yStart, int xEnd, int yEnd);

void placeRestartButton(int xStart, int yStart, int xEnd, int yEnd);

void placeTopLabel(int x, int y, int textSize, char text[]);

void scoreTextArea(int xStart, int yStart, int xEnd, int yEnd, int color, char text[]);

void changeTurn();

//void moveAiHard();

void updateTopLabel();

void updateScore();

bool hasGameEnded();

bool restartButtonClicked(int x, int y);

bool homeButtonClicked(int x, int y);

void PvP();

void PvcEasy();

//void PvcHard();
