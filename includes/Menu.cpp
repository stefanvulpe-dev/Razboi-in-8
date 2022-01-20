#include <winbgim.h>
#include <graphics.h>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"
#include "Tutorial.h"
#include "History.h"
bool isSoundOn, atHome, gameMode, selectedFolder;

//Tudor Iftene
void readImageFromFolder(const char* fileName, int x1, int y1, int x2, int y2)
 {
    char a[200]={0};
    if(selectedFolder==1)
        strcat(a, "res/");
    else 
        strcat(a, "rese/");
    strcat(a, fileName);
    readimagefile(a, x1, y1, x2, y2);
 }

//Stefan Vulpe
void placeTitle(int xStart, int yStart, int xEnd, int yEnd)
{
    readImageFromFolder("title.jpg", xStart, yStart, xEnd, yEnd);
}

//Tudor Iftene
void placeCreditsButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("credits_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("credits.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Tudor Iftene
void placeInstructionsButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("instructions_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("instructions.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Stefan Vulpe
void placeStartButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("start_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("start_button.jpg", xStart, yStart, xEnd, yEnd);

}

//Stefan Vulpe
void placeHistoryButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("history_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("history_button.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placeExitButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("exit_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("exit_button.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Stefan Vulpe
void placeSettingsButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
    {
        readImageFromFolder("settings_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    }
    else
    {
        readImageFromFolder("settings_button.jpg", xStart, yStart, xEnd, yEnd);
    }
}

//Tudor Iftene
bool creditsButtonClicked(int x, int y)
{
    if(inArea(x, y, screenResolution.BUTTON_MARGIN,
              screenResolution.BUTTON_MARGIN,
              screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
              screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE))
    {
        return true;
    }

    return false;
}

//Tudor Iftene
bool instructionsButtonClicked(int x, int y)
{
    if(inArea(x, y, screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                                screenResolution.BUTTON_MARGIN,
                                screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE))
    {
        return true;
    }

    return false;
}

//Stefan Vulpe
bool startButtonClicked(int x, int y)
{
    if(inArea(x, y, (screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    (screenResolution.HEIGHT - screenResolution.UTILITY_BUTTON_HEIGHT * 2) / 2,
                    (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    screenResolution.HEIGHT / 2))
    {
        return true;
    }

    return false;
}

//Stefan Vulpe
bool historyButtonClicked(int x, int y)
{
    if(inArea(x, y, (screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2,
                            (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2 + screenResolution.UTILITY_BUTTON_HEIGHT))
    {
        return true;
    }

    return false;
}

//Tudor Iftene
bool exitButtonClicked(int x, int y)
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

//Tudor Iftene
bool settingsButtonClicked(int x, int y)
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
void clickListener()
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        int x, y;

        getmouseclick(WM_LBUTTONDOWN, x, y);

        if(instructionsButtonClicked(x, y))
        {
            closegraph();

            delay(100);

            tutorial();
        }

        if(creditsButtonClicked(x, y))
        {
            closegraph();

            delay(100);

            openCreditsWindow();
        }

        if(startButtonClicked(x, y) && atHome)
        {
            atHome = 0;

            closegraph();

            delay(100);

            preStartWindow();
        }

        else if(startButtonClicked(x, y))
        {
            gameMode = 0;

            closegraph();

            PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

            delay(100);

            startGame();
        }

        if(historyButtonClicked(x, y) && atHome)
        {
            atHome = 0;

            closegraph();

            delay(100);

            openHistoryWindow();
        }

        else if(historyButtonClicked(x, y))
        {
            gameMode = 1;

            closegraph();

            PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

            delay(100);

            startGame();
        }

        if(exitButtonClicked(x, y) && atHome)
        {
            fseek(fptr, -1, SEEK_CUR);
            fprintf(fptr, "%d", isSoundOn);
            exit(0);
        }

        else if(exitButtonClicked(x, y))
        {
            atHome = 1;

            closegraph();

            delay(100);

            meniu();
        }


        if(settingsButtonClicked(x, y))
        {
            closegraph();

            delay(100);

            setari();
        }
    }
}

//Tudor Iftene
void meniu()
{
    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    setBackground(0, 0, screenResolution.WIDTH, screenResolution.HEIGHT);

    placeTitle((screenResolution.WIDTH - screenResolution.TITLE_WIDTH) / 2,
                screenResolution.BUTTON_MARGIN,
                (screenResolution.WIDTH + screenResolution.TITLE_WIDTH) / 2,
                screenResolution.BUTTON_MARGIN + screenResolution.TITLE_HEIGHT);

    if(isSoundOn == 0)
        PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

    do
    {
        placeCreditsButton(screenResolution.BUTTON_MARGIN,
              screenResolution.BUTTON_MARGIN,
              screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
              screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE);

        placeInstructionsButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                                screenResolution.BUTTON_MARGIN,
                                screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE);

        placeStartButton((screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    (screenResolution.HEIGHT - screenResolution.UTILITY_BUTTON_HEIGHT * 2) / 2,
                    (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    screenResolution.HEIGHT / 2);

        placeHistoryButton((screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2,
                            (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2 + screenResolution.UTILITY_BUTTON_HEIGHT);

        placeExitButton(screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

        placeSettingsButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

        clickListener();
    }
    while (1);

}
