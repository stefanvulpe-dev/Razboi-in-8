#include <graphics.h>
#include <winbgim.h>
#include <time.h>
#include <iostream>
#include <climits>
#include <vector>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"

using namespace std;

int dx[4] = {-1, -1, 1, 1};
int dy[4] = {-1, 1, 1, -1};
int i_move, j_move;
bool moved;

//Stefan Vulpe
void drawBoard(int xStart, int yStart, int xEnd, int yEnd, int dimensiune, board gameBoard[][8])
{
    for(int y = yStart, i = 0; y < yEnd; y += dimensiune, ++ i)
    {
        for(int x = xStart, j = 0; x < xEnd; x += dimensiune, ++ j)
        {
            gameBoard[i][j].xStart = x;
            gameBoard[i][j].yStart = y;
            gameBoard[i][j].xEnd = x + dimensiune;
            gameBoard[i][j].yEnd = y + dimensiune;

            gameBoard[i][j].player = -1;

            if((i + j) % 2)
            {
                setcolor(LIGHTBLUE);
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                rectangle(x, y, x + dimensiune, y + dimensiune);
                floodfill(x + (dimensiune / 2), y + (dimensiune / 2), LIGHTBLUE);
            }
            else
            {
                setcolor(WHITE);
                setfillstyle(SOLID_FILL, WHITE);
                rectangle(x, y, x + dimensiune, y + dimensiune);
                floodfill(x + (dimensiune / 2), y + (dimensiune / 2), WHITE);
            }

            //punem pionii pe tabla, player 1 first
            if(i == 0 && j % 2)
            {
                gameBoard[0][j].player = 1;
                movePawn(gameBoard[0][j].xStart,
                        gameBoard[0][j].yStart,
                        gameBoard[0][j].xEnd,
                        gameBoard[0][j].yEnd, {1, 0, 0, 0, 0});
            }
            else if(i == 1 && j % 2)
            {
                gameBoard[1][j - 1].player = 1;
                movePawn(gameBoard[1][j - 1].xStart,
                        gameBoard[1][j - 1].yStart,
                        gameBoard[1][j - 1].xEnd,
                        gameBoard[1][j - 1].yEnd, {1, 0, 0, 0, 0});
            }
            //player 2
            else if(i == 6 && j % 2)
            {
                gameBoard[6][j].player = 2;
                movePawn(gameBoard[6][j].xStart,
                        gameBoard[6][j].yStart,
                        gameBoard[6][j].xEnd,
                        gameBoard[6][j].yEnd, {2, 0, 0, 0, 0});
            }
            else if(i == 7 && j % 2)
            {
                gameBoard[7][j - 1].player = 2;
                movePawn(gameBoard[7][j - 1].xStart,
                        gameBoard[7][j - 1].yStart,
                        gameBoard[7][j - 1].xEnd,
                        gameBoard[7][j - 1].yEnd, {2, 0, 0, 0, 0});
            }

            //setam patratelele pe care putem plasa playerii
            if(i != 0 && i != 1 && i != 6 && i != 7)
            {
                if(i % 2 == 0 && j % 2)
                    gameBoard[i][j].player = 0;
                if(i % 2 == 1 && j % 2 == 0)
                {
                    gameBoard[i][j].player = 0;
                }
            }
        }
    }
}

//Stefan Vulpe
void borderGameBoard(int xStart, int yStart, int xEnd, int yEnd, int dimensiune)
{
    //sus
    roundedRectangle(xStart - dimensiune / 2, yStart - dimensiune, xEnd + dimensiune / 2, yStart, BLACK, 0);

    //stanga
    roundedRectangle2(xStart - dimensiune, yStart - dimensiune / 2, xStart, yEnd + dimensiune / 2, BLACK, 0);

    //jos
    roundedRectangle(xStart - dimensiune / 2, yEnd, xEnd + dimensiune / 2, yEnd + dimensiune, BLACK, 0);

    //dreapta
    roundedRectangle2(xEnd, yStart - dimensiune / 2, xEnd + dimensiune, yEnd + dimensiune / 2, BLACK, 0);
}

//Stefan Vulpe
bool inArea(int x, int y, int xStart, int yStart, int xEnd, int yEnd)
{
    return ((x >= xStart && x <= xEnd) && (y >= yStart && y <= yEnd));
}

//Stefan Vulpe
bool interior(int x, int y)
{
    return ((x >= 0 && x < 8) && (y >= 0 && y < 8));
}

//Stefan Vulpe
bool clickOnTable(int x, int y, board gameBoard[][8])
{
    return inArea(x, y, gameBoard[0][0].xStart, gameBoard[0][0].yStart,
                gameBoard[7][7].xEnd, gameBoard[7][7].yEnd);
}

//Stefan Vulpe
bool findClick(int x, int y, board gameBoard[][8], Player player)
{
    for(int i = 0; i < 8; ++ i)
    {
        for(int j = 0; j < 8; ++ j)
        {
            if(gameBoard[i][j].player == player.type &&  inArea(x, y, gameBoard[i][j].xStart, gameBoard[i][j].yStart,
                    gameBoard[i][j].xEnd, gameBoard[i][j].yEnd))
            {
                clearPreviousValidMoves(gameBoard);
                clearHighlightedPawns(gameBoard, i_move, j_move, player);
                drawValidMove(gameBoard, i, j);
                showPawnClicked(gameBoard, i, j, player);
                i_move = i;
                j_move = j;
                return true;
            }
        }
    }
    return false;
}

//Stefan Vulpe
bool hasNoNeighbours(int i, int j, board gameBoard[][8])
{
    int x, y;

    for(int k = 0; k < 4; ++ k)
    {
        x = i + dx[k];
        y = j + dy[k];

        if(interior(x, y) && gameBoard[x][y].player == 0)
            return false;
    }
    return true;
}

//Stefan Vulpe
void movePawn(int xStart, int yStart, int xEnd, int yEnd, Player player)
{
    if(player.type == 1)
        readImageFromFolder("pion_player_A.jpg", xStart + 10, yStart + 10, xEnd - 10, yEnd - 10);
    else if(player.type == 2)
        readImageFromFolder("pion_player_B.jpg", xStart + 10, yStart + 10, xEnd - 10, yEnd - 10);
}

//Stefan Vulpe
void move(board gameBoard[][8], int x, int y, Player & player)
{
    int x_neighbour, y_neighbour;

    for(int k = 0; k < 4; ++ k)
    {
        x_neighbour = i_move + dx[k];
        y_neighbour = j_move + dy[k];

        if(interior(x_neighbour, y_neighbour) && gameBoard[x_neighbour][y_neighbour].player == 0 && inArea(x, y,
                                gameBoard[x_neighbour][y_neighbour].xStart, gameBoard[x_neighbour][y_neighbour].yStart,
                                gameBoard[x_neighbour][y_neighbour].xEnd, gameBoard[x_neighbour][y_neighbour].yEnd))
        {
            gameBoard[i_move][j_move].player = 0;

            clearPreviousValidMoves(gameBoard);

            gameBoard[x_neighbour][y_neighbour].player = player.type;

            movePawn(gameBoard[x_neighbour][y_neighbour].xStart, gameBoard[x_neighbour][y_neighbour].yStart,
                                                        gameBoard[x_neighbour][y_neighbour].xEnd, gameBoard[x_neighbour][y_neighbour].yEnd, player);

            player.moves ++;

            updateTopLabel();

            changeTurn();

            moved = true;
        }
    }
}

//Stefan Vulpe
void clickListener(board gameBoard[][8], Player & player)
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x, y;

        getmouseclick(WM_LBUTTONDOWN, x, y);

        //daca click-ul este pe tabla
        if(clickOnTable(x, y, gameBoard) && !hasGameEnded())
        {
            i_move = -1, j_move = -1;

            moved = false;

            if(findClick(x, y, gameBoard, player))
            {

                while(!moved)
                {

                    while(!ismouseclick(WM_LBUTTONDOWN))
                    {
                        //wait
                    }

                    getmouseclick(WM_LBUTTONDOWN, x, y);

                    if(findClick(x, y, gameBoard, player))
                    {
                        moved = false;
                    }
                    else
                        move(gameBoard, x, y, player);
                }
            }
        }
        else if(restartButtonClicked(x, y))
        {
            //restart game
            closegraph();

            delay(100);

            startGame();
        }
        else if(homeButtonClicked(x, y))
        {
            atHome = 1;

            if(isSoundOn)
                PlaySoundW(L"res/muzica.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

            closegraph();

            delay(100);

            meniu();
        }
    }
}

//Stefan Vulpe
void moveAiEasy(board gameBoard[][8], Player & player)
{
    bool foundMove = false;
    int x, y, x_neighbour, y_neighbour;
    srand(time(0));

    while(!foundMove)
    {
        x = rand() % 8;
        y = rand() % 8;

        if(gameBoard[x][y].player == player.type)
        {
            for(int i = 0; i < 4 && !foundMove; ++ i)
            {
                x_neighbour = x + dx[i];
                y_neighbour = y + dy[i];

                if(interior(x_neighbour, y_neighbour) && gameBoard[x_neighbour][y_neighbour].player == 0)
                {
                    gameBoard[x][y].player = 0;
                    clearCell(gameBoard[x][y].xStart, gameBoard[x][y].yStart, gameBoard[x][y].xEnd, gameBoard[x][y].yEnd);
                    foundMove = true;
                }
            }
        }
    }

    gameBoard[x_neighbour][y_neighbour].player = player.type;

    movePawn(gameBoard[x_neighbour][y_neighbour].xStart, gameBoard[x_neighbour][y_neighbour].yStart, gameBoard[x_neighbour][y_neighbour].xEnd, gameBoard[x_neighbour][y_neighbour].yEnd, player);

    player.moves ++;

    updateTopLabel();

    delay(150);

    changeTurn();
}

//Stefan Vulpe
void drawValidMove(board gameBoard[][8], int i, int j)
{
    int x, y;

    for(int k = 0; k < 4; ++ k)
    {
        x = i + dx[k];
        y = j + dy[k];
        if(interior(x, y) && gameBoard[x][y].player == 0)
        {
            setcolor(LIGHTGREEN);
            setfillstyle(SOLID_FILL, LIGHTGREEN);
            rectangle(gameBoard[x][y].xStart, gameBoard[x][y].yStart, gameBoard[x][y].xEnd, gameBoard[x][y].yEnd);
            floodfill((gameBoard[x][y].xStart + gameBoard[x][y].xEnd) / 2, (gameBoard[x][y].yStart + gameBoard[x][y].yEnd) / 2, LIGHTGREEN);
        }
    }
}

//Stefan Vulpe
void clearCell(int xStart, int yStart, int xEnd, int yEnd)
{
    setcolor(LIGHTBLUE);
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    rectangle(xStart, yStart, xEnd, yEnd);
    floodfill((xStart + xEnd) / 2, (yStart + yEnd) / 2, LIGHTBLUE);
}

//Stefan Vulpe
void clearPreviousValidMoves(board gameBoard[][8])
{
    for(int i = 0; i < 8; ++ i)
    {
        for(int j = 0; j < 8; ++ j)
        {
            if(gameBoard[i][j].player == 0)
            {
                clearCell(gameBoard[i][j].xStart, gameBoard[i][j].yStart, gameBoard[i][j].xEnd, gameBoard[i][j].yEnd);
            }
        }
    }
    reborderGameBoard();
}

//Stefan Vulpe
void showPawnClicked(board gameBoard[][8], int x, int y, Player player)
{
    if(player.type == 1)
        readImageFromFolder("pion_player_A_click.jpg", gameBoard[x][y].xStart + 10, gameBoard[x][y].yStart + 10,
                    gameBoard[x][y].xEnd - 10, gameBoard[x][y].yEnd - 10);
    if(player.type == 2)
        readImageFromFolder("pion_player_B_click.jpg", gameBoard[x][y].xStart + 10, gameBoard[x][y].yStart + 10,
                    gameBoard[x][y].xEnd - 10, gameBoard[x][y].yEnd - 10);
}

//Stefan Vulpe
void clearHighlightedPawns(board gameBoard[][8], int i, int j, Player player)
{
    if(i_move != -1 && j_move != -1)
        movePawn(gameBoard[i][j].xStart, gameBoard[i][j].yStart,
                    gameBoard[i][j].xEnd, gameBoard[i][j].yEnd, player);
}

//Stefan Vulpe
void checkForRemoval(board gameBoard[][8], Player player1, Player & player2)
{
    for(int i = 0; i < 8; ++ i)
    {
        for(int j = 0; j < 8; ++ j)
        {
            if(gameBoard[i][j].player == player1.type &&  hasNoNeighbours(i, j, gameBoard))
            {
                clearCell(gameBoard[i][j].xStart, gameBoard[i][j].yStart, gameBoard[i][j].xEnd, gameBoard[i][j].yEnd);
                gameBoard[i][j].player = 0;
                player2.score ++;
            }
        }
    }
}

//Stefan Vulpe
void setPlayerScoreAndMoves(int x, int y, int textSize, Player player)
{
    string str1, str2;
    char * text1, * text2;

    settextstyle(SIMPLEX_FONT, HORIZ_DIR, textSize);

    if(player.type == 1)
    {
        if(selectedFolder == 1)
        {
            str1 = "  Scor jucator A: " + to_string(player.score) + " ";
            str2 = " Mutari A: " + to_string(player.moves) + " ";
        }
        else 
        {
            str1 = "  Player A score: " + to_string(player.score) + " ";
            str2 = " A moves: " + to_string(player.moves) + " ";
        }
    }
    else if(player.type == 2)
    {
        if(selectedFolder == 1)
        {
            str1 = "  Scor jucator B: " + to_string(player.score) + " ";
            str2 = " Mutari B: " + to_string(player.moves) + " ";
        }
        else 
        {
            str1 = "  Player B score: " + to_string(player.score) + " ";
            str2 = " B moves: " + to_string(player.moves) + " ";
        }
    }

    text1 = new char[str1.size() + 1];
    text2 = new char[str2.size() + 1];

    copy(str1.begin(), str1.end(), text1);
    copy(str2.begin(), str2.end(), text2);

    text1[str1.size()] = '\0';
    text2[str2.size()] = '\0';

    int width = textwidth(text1);
    int width2 = textwidth(text2);
    int height = textheight(text1);
    int r = (5 * height) / 8 - 2;

    roundedRectangle(x - (width / 2), y - height, x + (width / 2), y, WHITE, (height / 4));

    bar(x - (width / 2) - r - 4,  y - height + r, x + (width / 2) + r + 4, y - r + height);

    roundedRectangle(x - (width / 2), y - 2 * r + height, x + (width / 2), y + height, WHITE, (height / 4));

    setcolor(BLACK);
    setbkcolor(WHITE);

    outtextxy(x - (width / 2), y - height, text1);
    outtextxy(x - (width2 / 2), y - 2 * r + height, text2);

    delete text1, text2;
}

//Stefan Vulpe
void placeCurrenPlayerLabel(int xStart, int yStart, int xEnd, int yEnd, Player player)
{
    if(player.type == 1)
        readImageFromFolder("playerA_muta.jpg", xStart, yStart, xEnd, yEnd);
    else if(player.type == 2)
        readImageFromFolder("playerB_muta.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void playWinAnimation(int xStart, int yStart, int xEnd, int yEnd, int dimensiune, board gameBoard[][8], Player player)
{
    for(int y = yStart, i = 0; y < yEnd; y += dimensiune, ++ i)
    {
        for(int x = xStart, j = 0; x < xEnd; x += dimensiune, ++ j)
        {
            gameBoard[i][j].xStart = x;
            gameBoard[i][j].yStart = y;
            gameBoard[i][j].xEnd = x + dimensiune;
            gameBoard[i][j].yEnd = y + dimensiune;

            gameBoard[i][j].player = -1;

            if((i + j) % 2)
            {
                setcolor(LIGHTBLUE);
                setfillstyle(SOLID_FILL, LIGHTBLUE);
                rectangle(x, y, x + dimensiune, y + dimensiune);
                floodfill(x + (dimensiune / 2), y + (dimensiune / 2), LIGHTBLUE);
            }
            else
            {
                setcolor(WHITE);
                setfillstyle(SOLID_FILL, WHITE);
                rectangle(x, y, x + dimensiune, y + dimensiune);
                floodfill(x + (dimensiune / 2), y + (dimensiune / 2), WHITE);
            }

            //punem pionii pe tabla
            if(player.type == 1)
            {
                movePawn(gameBoard[i][j].xStart,
                        gameBoard[i][j].yStart,
                        gameBoard[i][j].xEnd,
                        gameBoard[i][j].yEnd, {1, 0, 0, 0, 0});
            }
            else if(player.type == 2)
            {
                movePawn(gameBoard[i][j].xStart,
                        gameBoard[i][j].yStart,
                        gameBoard[i][j].xEnd,
                        gameBoard[i][j].yEnd, {2, 0, 0, 0, 0});
            }
            else if(player.type == -1)
            {
                if(i < 4)
                {
                    movePawn(gameBoard[i][j].xStart,
                        gameBoard[i][j].yStart,
                        gameBoard[i][j].xEnd,
                        gameBoard[i][j].yEnd, {1, 0, 0, 0, 0});
                }
                else
                {
                    movePawn(gameBoard[i][j].xStart,
                        gameBoard[i][j].yStart,
                        gameBoard[i][j].xEnd,
                        gameBoard[i][j].yEnd, {2, 0, 0, 0, 0});
                }
            }
        }
        delay(100);
    }
}
