#include <vector>

using namespace std;

struct board {
    int xStart, yStart, xEnd, yEnd, player;
};

struct Player {
    int type, score, moves, turn, won;
};

void drawBoard(int xStart, int yStart, int xEnd, int yEnd, int dimensiune, board gameBoard[8][8]);

void borderGameBoard(int xStart, int yStart, int xEnd, int yEnd, int dimensiune);

bool inArea(int x, int y, int xStart, int yStart, int xEnd, int yEnd);

bool interior(int x, int y);

bool clickOnTable(int x, int y, board gameBoard[][8]);

bool findClick(int x, int y, board gameBoard[][8], Player player);

bool hasNoNeighbours(int i, int j, board gameBoard[][8]);

void movePawn(int xStart, int yStart, int xEnd, int yEnd, Player player);

void move(board gameBoard[][8], int x, int y, Player & player);

void simulateMove(board gameBoard[][8], int init_i, int init_j, int next_i, int next_j, Player player);

void clickListener(board gameBoard[][8], Player & player);

void moveAiEasy(board gameBoard[][8], Player & player);

void drawValidMove(board gameBoard[][8], int i, int j);

void clearCell(int xStart, int yStart, int xEnd, int yEnd);

void clearPreviousValidMoves(board gameBoard[][8]);

void showPawnClicked(board gameBoard[][8], int x, int y, Player player);

void clearHighlightedPawns(board gameBoard[][8], int x, int y, Player player);

void checkForRemoval(board gameBoard[][8], Player player1, Player & player2);

void setPlayerScoreAndMoves(int x, int y, int textSize, Player player);

void placeCurrenPlayerLabel(int xStart, int yStart, int xEnd, int yEnd, Player player);

void playWinAnimation(int xStart, int yStart, int xEnd, int yEnd, int dimensiune, board gameBoard[][8], Player player);

