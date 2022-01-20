#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <string>
#include <climits>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"

using namespace std;

board gameBoard[8][8];
int playerA_wins, playerB_wins, nrOfMoves;
Player player1, player2;
bool startRuleApplied, animationPlayed;

//Stefan Vulpe
void setBackground(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("fundal.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void startGame()
{
    //player 1 incepe intotdeauna primul
    player1.type = 1, player1.score = 0, player1.moves = 0, player1.turn = 1, player1.won = 0;

    player2.type = 2, player2.score = 0, player2.moves = 0, player2.turn = 0, player2.won = 0;

    startRuleApplied = false;

    animationPlayed = false;

    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    setBackground(0, 0, screenResolution.WIDTH, screenResolution.HEIGHT);

    if(selectedFolder == 0)
    {
        placeTopLabel(screenResolution.WIDTH / 2,
                (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 4,
                screenResolution.TOP_LABEL_TEXT_SIZE, (char *)" Make 4 moves / player ");
    }
    else
    {
        placeTopLabel(screenResolution.WIDTH / 2,
                (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 4,
                screenResolution.TOP_LABEL_TEXT_SIZE, (char *)" Efectuati 4 mutari / jucator ");
    }

    setPlayerScoreAndMoves((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 4,
                    screenResolution.HEIGHT / 2,
                    screenResolution.PlayerA_TEXT_SIZE, player1);

    setPlayerScoreAndMoves(screenResolution.WIDTH - (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 4,
                    screenResolution.HEIGHT / 2,
                    screenResolution.PlayerB_TEXT_SIZE, player2);

    delay(100);

    drawBoard((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
            (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
            (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
            screenResolution.GameBoard_CELL_SIZE, gameBoard);

    borderGameBoard((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_BORDER_WIDTH);
    if(gameMode == 0)
    {
        do
        {
            placeRestartButton(screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

            placeHomeButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

            PvP();
        } while(1);
    }
    else if(gameMode == 1)
    {
        do
        {
            placeRestartButton(screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

            placeHomeButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

            PvcEasy();
        } while(1);
    }
}

//Stefan Vulpe
void roundedRectangle(int xStart, int yStart, int xEnd, int yEnd, int color, int grosime)
{
    int r = (yEnd - yStart) / 2 + grosime;

    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    rectangle(xStart, yStart - grosime, xEnd, yEnd + grosime);

    floodfill((xStart + xEnd) / 2, (yStart + yEnd) / 2, color);

    circle(xStart, (yStart + yEnd) / 2, r);
    circle(xEnd, (yStart + yEnd) / 2, r);

    fillellipse(xStart, (yStart + yEnd) / 2, r, r);
    fillellipse(xEnd, (yStart + yEnd) / 2, r, r);
}

//Stefan Vulpe
void roundedRectangle2(int xStart, int yStart, int xEnd, int yEnd, int color, int grosime)
{
    int r = (xEnd - xStart) / 2 + grosime;

    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    rectangle(xStart, yStart - grosime, xEnd, yEnd + grosime);

    floodfill((xStart + xEnd) / 2, (yStart + yEnd) / 2, color);

    circle((xStart + xEnd) / 2, yStart, r);
    circle((xStart + xEnd) / 2, yEnd, r);

    fillellipse((xStart + xEnd) / 2, yStart, r, r);
    fillellipse((xStart + xEnd) / 2, yEnd, r, r);
}

//Stefan Vulpe
void reborderGameBoard()
{
    borderGameBoard((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_BORDER_WIDTH);
}

//Stefan Vulpe
void placeTopLabel(int x, int y, int textSize, char text[])
{
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, textSize);

    int width = textwidth(text);
    int height = textheight(text);

    roundedRectangle(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2), WHITE, (height / 4));

    setcolor(BLACK);
    setbkcolor(WHITE);
    outtextxy(x - (width / 2), y - (height / 2), text);
}

//Stefan Vulpe
void placeRestartButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex();
    int y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("restart_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("restart_button.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Stefan Vulpe
void placeHomeButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("home_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("home_button.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Stefan Vulpe
void scoreTextArea(int xStart, int yStart, int xEnd, int yEnd, int color, char text[])
{
    int r = (yEnd - yStart) / 2 ;

    setcolor(color);
    setfillstyle(SOLID_FILL, color);

    rectangle(xStart, yStart, xEnd, yEnd);

    floodfill((xStart + xEnd) / 2, (yStart + yEnd) / 2, color);

    circle(xStart, (yStart + yEnd) / 2, r);
    circle(xEnd, (yStart + yEnd) / 2, r);

    fillellipse(xStart, (yStart + yEnd) / 2, r, r);
    fillellipse(xEnd, (yStart + yEnd) / 2, r, r);
}

//Stefan Vulpe
void updateTopLabel()
{
    if(startRuleApplied)
    {
        int mutari_ramase = 100 - (player1.moves + player2.moves);

        string str;

        if(selectedFolder == 0)
            str = "  Moves available: " + to_string(mutari_ramase) + "  ";
        else 
            str = "  Mutari disponibile: " + to_string(mutari_ramase) + "  ";
        char * text = new char[str.size() + 1];

        copy(str.begin(), str.end(), text);

        text[str.size()] = '\0';

        placeTopLabel(screenResolution.WIDTH / 2,
                (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 4,
                screenResolution.TOP_LABEL_TEXT_SIZE, text);
    }
}

//Stefan Vulpe
void updateScore()
{
    setPlayerScoreAndMoves((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 4,
                    screenResolution.HEIGHT / 2,
                    screenResolution.PlayerA_TEXT_SIZE, player1);

    setPlayerScoreAndMoves(screenResolution.WIDTH - (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 4,
                    screenResolution.HEIGHT / 2,
                    screenResolution.PlayerB_TEXT_SIZE, player2);
}

//Stefan Vulpe
void changeTurn()
{
    if(isSoundOn)
        PlaySoundW(L"res/pawn_sound.wav", NULL, SND_ASYNC);

    if(player1.turn == 1)
    {
        player1.turn = 0;

        if(startRuleApplied)
        {
            checkForRemoval(gameBoard, player2, player1);
            checkForRemoval(gameBoard, player1, player2);
        }
        else if(player1.moves == 4 && !startRuleApplied)
        {
            checkForRemoval(gameBoard, player1, player2);
            player1.moves = 0;
        }

        updateScore();

        player2.turn = 1;
    }
    else if(player2.turn == 1)
    {
        player2.turn = 0;

        if(startRuleApplied)
        {
            checkForRemoval(gameBoard, player1, player2);
            checkForRemoval(gameBoard, player2, player1);
        }
        else if(player2.moves == 4 && !startRuleApplied)
        {
            startRuleApplied = true;
            checkForRemoval(gameBoard, player1, player2);
            checkForRemoval(gameBoard, player2, player1);
            player2.moves = 0;
            updateTopLabel();
        }

        updateScore();

        player1.turn = 1;
    }
}

//Stefan Vulpe
bool hasGameEnded()
{
    if(player1.score == 8)
    {
        player1.won = 1;
        return true;
    }
    else if(player2.score == 8)
    {
        player2.won = 1;
        return true;
    }
    else
    {
        int mutari_ramase = 50 - (player1.moves + player2.moves);

        if(mutari_ramase == 0)
        {
            if(player1.score > player2.score)
            {
                player1.won = 1;
                return true;
            }
            else if(player2.score > player1.score)
            {
                player2.won = 1;
                return true;
            }
            else
                return true;
        }
    }

    return false;
}

//Stefan Vulpe
bool restartButtonClicked(int x, int y)
{
    if(inArea(x, y, screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN))
    {
        return true;
    }

    return false;
}

//Stefan Vulpe
bool homeButtonClicked(int x, int y)
{
    if(inArea(x, y, screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN))
    {
        return true;
    }

    return false;
}

//Stefan Vulpe
void PvP()
{
    if(!hasGameEnded())
    {
        if(player1.turn == 1)
        {
            placeCurrenPlayerLabel((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT, player1);
            clickListener(gameBoard, player1);
        }
        else if(player2.turn == 1)
        {
            placeCurrenPlayerLabel((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT, player2);
            clickListener(gameBoard, player2);
        }
    }
    else
    {
        if(!animationPlayed)
        {
            if(isSoundOn)
                PlaySoundW(L"res/game_over.wav", NULL, SND_ASYNC);

            if(player1.won)
            {
                playerA_wins ++;
                nrOfMoves = min(player1.moves, nrOfMoves);

                readImageFromFolder("playerA_win.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, player1);

                animationPlayed = true;
            }
            else if(player2.won)
            {
                playerB_wins ++;
                nrOfMoves = min(player2.moves, nrOfMoves);
                readImageFromFolder("playerB_win.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, player2);

                animationPlayed = true;
            }
            else
            {
                readImageFromFolder("remiza.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, {-1, 0, 0, 0, 0});

                animationPlayed = true;
            }
        }
        clickListener(gameBoard, player1);
    }
}

//Stefan Vulpe
void PvcEasy()
{
    if(!hasGameEnded())
    {
        if(player1.turn == 1)
        {
            placeCurrenPlayerLabel((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT, player1);
            clickListener(gameBoard, player1);
        }
        else if(player2.turn == 1)
        {
            placeCurrenPlayerLabel((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                            (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT, player2);
            moveAiEasy(gameBoard, player2);
        }
    }
    else
    {
        if(!animationPlayed)
        {
            if(isSoundOn)
                PlaySoundW(L"res/game_over.wav", NULL, SND_ASYNC);

            if(player1.won)
            {
                playerA_wins ++;
                nrOfMoves = min(player1.moves, nrOfMoves);
                readImageFromFolder("playerA_win.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, player1);

                animationPlayed = true;
            }
            else if(player2.won)
            {
                playerB_wins ++;
                nrOfMoves = min(player2.moves, nrOfMoves);
                readImageFromFolder("playerB_win.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, player2);

                animationPlayed = true;
            }
            else
            {
                readImageFromFolder("remiza.jpg",
                        (screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2 - screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH,
                        (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2 + screenResolution.GameBoard_BORDER_WIDTH + screenResolution.BOTTOM_LABEL_HEIGHT);

                playWinAnimation((screenResolution.WIDTH - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT - screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.WIDTH + screenResolution.GameBoard_SIZE) / 2,
                    (screenResolution.HEIGHT + screenResolution.GameBoard_SIZE) / 2,
                    screenResolution.GameBoard_CELL_SIZE, gameBoard, {-1, 0, 0, 0, 0});

                animationPlayed = true;
            }
        }
        clickListener(gameBoard, player1);
    }
}
