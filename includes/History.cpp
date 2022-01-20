#include <graphics.h>
#include <winbgim.h>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"

//Stefan Vulpe
void placeGameHistoryTitle(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("gameHistoryTitle.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placePlayerAWins(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("playerA_wins.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placePlayerBWins(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("playerB_wins.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placeNrOfMoves(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("nr_of_moves.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placeText(int x, int y, int textSize, int player)
{
    settextstyle(SIMPLEX_FONT, HORIZ_DIR, textSize);

    string str;

    if(player == 1)
        str = to_string(playerA_wins);
    else if(player == 2)
        str = to_string(playerB_wins);
    else
    {
        if(playerA_wins == 0 && playerB_wins == 0)
            str = to_string(0);
        else
            str = to_string(nrOfMoves);
    }
    char * text = new char[str.size() + 1];

    copy(str.begin(), str.end(), text);

    text[str.size()] = '\0';

    int width = textwidth(text);
    int height = textheight(text);

    roundedRectangle(x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2), WHITE, (height / 4));

    setcolor(BLACK);
    setbkcolor(WHITE);
    outtextxy(x - (width / 2), y - (height / 2), text);
}

//Stefan Vulpe
void openHistoryWindow()
{
    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    setBackground(0, 0, screenResolution.WIDTH, screenResolution.HEIGHT);

    placeGameHistoryTitle(screenResolution.WIDTH / 3, screenResolution.BUTTON_MARGIN, 2 * screenResolution.WIDTH / 3, 
                        screenResolution.BUTTON_MARGIN + screenResolution.UTILITY_BUTTON_HEIGHT);

    if(isSoundOn == 0)
    {
        PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
    }

    placeText(screenResolution.WIDTH / 4,
            screenResolution.HEIGHT / 2 + screenResolution.BUTTON_SIZE / 2, 4, 1);

    placeText(screenResolution.WIDTH / 2, 
            screenResolution.HEIGHT / 2 + screenResolution.BUTTON_SIZE / 2, 4, 2);

    placeText(screenResolution.WIDTH - screenResolution.WIDTH / 4,
            screenResolution.HEIGHT / 2 + screenResolution.BUTTON_SIZE / 2, 4, 0);

    do
    {
        placePlayerAWins(screenResolution.WIDTH / 4 - screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT / 2 - screenResolution.BUTTON_SIZE,
                        screenResolution.WIDTH / 4 + screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT / 2);

        placePlayerBWins(screenResolution.WIDTH / 2 - screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT / 2 - screenResolution.BUTTON_SIZE,
                        screenResolution.WIDTH / 2 + screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT / 2);

        placeNrOfMoves(screenResolution.WIDTH - (screenResolution.WIDTH / 4 + screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT / 2 - screenResolution.BUTTON_SIZE,
                    screenResolution.WIDTH - (screenResolution.WIDTH / 4 - screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT / 2);

        placeHomeButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);


        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(inArea(x, y, screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                        screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                        screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN))
            {
                atHome = 1;

                closegraph();

                delay(100);

                meniu();
            }
        }
    } while (1);

}
