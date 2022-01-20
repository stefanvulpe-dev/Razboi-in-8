#include <graphics.h>
#include <winbgim.h>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"

FILE * fptr;

settings screenResolution, STANDARD_SIZE, INTERMEDIATE_SIZE, FULL_SCREEN;;
int screenWidth, screenHeight, dim = 8, buttonHeight = 10, buttonWidth = 10;
float boardSizeRatio = 1.50, buttonWidthRatio = 3.5, buttonHeightRatio = 7.5;

//Stefan Vulpe
void findOptimalSize()
{
    while((float)screenHeight / (dim * 8) > boardSizeRatio)
    {
        dim += 8;
    }

    while((float)screenWidth / buttonWidth > buttonWidthRatio)
    {
        buttonWidth += 10;
    }

    while((float)screenHeight / buttonHeight > buttonHeightRatio)
    {
        buttonHeight += 10;
    }
}

//Stefan Vulpe
void initializeSizes()
{
    //Rezolutia standard 1024x768
    STANDARD_SIZE.WIDTH = 1024;
    STANDARD_SIZE.HEIGHT = 768;
    STANDARD_SIZE.GameBoard_SIZE = 520;
    STANDARD_SIZE.GameBoard_CELL_SIZE = 65;
    STANDARD_SIZE.GameBoard_BORDER_WIDTH = 6;
    STANDARD_SIZE.BUTTON_SIZE = 100;
    STANDARD_SIZE.BUTTON_MARGIN = 25;
    STANDARD_SIZE.PlayerA_TEXT_SIZE = 1;
    STANDARD_SIZE.PlayerB_TEXT_SIZE = 1;
    STANDARD_SIZE.TOP_LABEL_TEXT_SIZE = 4;
    STANDARD_SIZE.BOTTOM_LABEL_HEIGHT = 75;
    STANDARD_SIZE.UTILITY_BUTTON_WIDTH = 300;
    STANDARD_SIZE.UTILITY_BUTTON_HEIGHT = 100;
    STANDARD_SIZE.TITLE_WIDTH = 500;
    STANDARD_SIZE.TITLE_HEIGHT = 100;

    //Intermediate size
    INTERMEDIATE_SIZE.WIDTH = 1600;
    INTERMEDIATE_SIZE.HEIGHT = 900;
    INTERMEDIATE_SIZE.GameBoard_SIZE = 576;
    INTERMEDIATE_SIZE.GameBoard_CELL_SIZE = 72;
    INTERMEDIATE_SIZE.GameBoard_BORDER_WIDTH = 8;
    INTERMEDIATE_SIZE.BUTTON_SIZE = 120;
    INTERMEDIATE_SIZE.BUTTON_MARGIN = 25;
    INTERMEDIATE_SIZE.PlayerA_TEXT_SIZE = 3;
    INTERMEDIATE_SIZE.PlayerB_TEXT_SIZE = 3;
    INTERMEDIATE_SIZE.TOP_LABEL_TEXT_SIZE = 5;
    INTERMEDIATE_SIZE.BOTTOM_LABEL_HEIGHT = 80;
    INTERMEDIATE_SIZE.UTILITY_BUTTON_WIDTH = 400;
    INTERMEDIATE_SIZE.UTILITY_BUTTON_HEIGHT = 100;
    INTERMEDIATE_SIZE.TITLE_WIDTH = 600;
    INTERMEDIATE_SIZE.TITLE_HEIGHT = 120;

    //Full Screen
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);

    findOptimalSize();

    FULL_SCREEN.WIDTH = screenWidth;
    FULL_SCREEN.HEIGHT = screenHeight;
    FULL_SCREEN.GameBoard_SIZE = dim * 8;
    FULL_SCREEN.GameBoard_CELL_SIZE = dim;
    FULL_SCREEN.GameBoard_BORDER_WIDTH = dim / 10;
    FULL_SCREEN.BUTTON_SIZE = 120;
    FULL_SCREEN.BUTTON_MARGIN = 30;
    FULL_SCREEN.PlayerA_TEXT_SIZE = 3;
    FULL_SCREEN.PlayerB_TEXT_SIZE = 3;
    FULL_SCREEN.TOP_LABEL_TEXT_SIZE = 5;
    FULL_SCREEN.BOTTOM_LABEL_HEIGHT = 80;
    FULL_SCREEN.UTILITY_BUTTON_WIDTH = buttonWidth;
    FULL_SCREEN.UTILITY_BUTTON_HEIGHT = buttonHeight;
    FULL_SCREEN.TITLE_WIDTH = buttonWidth + 100;
    FULL_SCREEN.TITLE_HEIGHT = buttonHeight + 20;
}

//Stefan Vulpe
void writeAndReadSettings()
{
    fptr = fopen("settings.txt", "r+");

    if(fptr == NULL)
    {
        fptr = fopen("settings.txt", "w+");
        //standard size
        fprintf(fptr, "%d\n", STANDARD_SIZE.WIDTH);
        fprintf(fptr, "%d\n", STANDARD_SIZE.HEIGHT);
        fprintf(fptr, "%d\n", STANDARD_SIZE.GameBoard_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.GameBoard_CELL_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.GameBoard_BORDER_WIDTH);
        fprintf(fptr, "%d\n", STANDARD_SIZE.BUTTON_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.BUTTON_MARGIN);
        fprintf(fptr, "%d\n", STANDARD_SIZE.PlayerA_TEXT_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.PlayerB_TEXT_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.TOP_LABEL_TEXT_SIZE);
        fprintf(fptr, "%d\n", STANDARD_SIZE.BOTTOM_LABEL_HEIGHT);
        fprintf(fptr, "%d\n", STANDARD_SIZE.UTILITY_BUTTON_WIDTH);
        fprintf(fptr, "%d\n", STANDARD_SIZE.UTILITY_BUTTON_HEIGHT);
        fprintf(fptr, "%d\n", STANDARD_SIZE.TITLE_WIDTH);
        fprintf(fptr, "%d\n", STANDARD_SIZE.TITLE_HEIGHT);
        fprintf(fptr, "%d", 1);
        screenResolution = STANDARD_SIZE;
    }
    else
    {
        fscanf(fptr, "%d", & screenResolution.WIDTH);
        fscanf(fptr, "%d", & screenResolution.HEIGHT);
        fscanf(fptr, "%d", & screenResolution.GameBoard_SIZE);
        fscanf(fptr, "%d", & screenResolution.GameBoard_CELL_SIZE);
        fscanf(fptr, "%d", & screenResolution.GameBoard_BORDER_WIDTH);
        fscanf(fptr, "%d", & screenResolution.BUTTON_SIZE);
        fscanf(fptr, "%d", & screenResolution.BUTTON_MARGIN);
        fscanf(fptr, "%d", & screenResolution.PlayerA_TEXT_SIZE);
        fscanf(fptr, "%d", & screenResolution.PlayerB_TEXT_SIZE);
        fscanf(fptr, "%d", & screenResolution.TOP_LABEL_TEXT_SIZE);
        fscanf(fptr, "%d", & screenResolution.BOTTOM_LABEL_HEIGHT);
        fscanf(fptr, "%d", & screenResolution.UTILITY_BUTTON_WIDTH);
        fscanf(fptr, "%d", & screenResolution.UTILITY_BUTTON_HEIGHT);
        fscanf(fptr, "%d", & screenResolution.TITLE_WIDTH);
        fscanf(fptr, "%d", & screenResolution.TITLE_HEIGHT);
        fscanf(fptr, "%d", & isSoundOn);
    }
}

//Stefan Vulpe
void saveSettings()
{
    fseek(fptr, 0, SEEK_SET);
    fprintf(fptr, "%d\n", screenResolution.WIDTH);
    fprintf(fptr, "%d\n", screenResolution.HEIGHT);
    fprintf(fptr, "%d\n", screenResolution.GameBoard_SIZE);
    fprintf(fptr, "%d\n", screenResolution.GameBoard_CELL_SIZE);
    fprintf(fptr, "%d\n", screenResolution.GameBoard_BORDER_WIDTH);
    fprintf(fptr, "%d\n", screenResolution.BUTTON_SIZE);
    fprintf(fptr, "%d\n", screenResolution.BUTTON_MARGIN);
    fprintf(fptr, "%d\n", screenResolution.PlayerA_TEXT_SIZE);
    fprintf(fptr, "%d\n", screenResolution.PlayerB_TEXT_SIZE);
    fprintf(fptr, "%d\n", screenResolution.TOP_LABEL_TEXT_SIZE);
    fprintf(fptr, "%d\n", screenResolution.BOTTOM_LABEL_HEIGHT);
    fprintf(fptr, "%d\n", screenResolution.UTILITY_BUTTON_WIDTH);
    fprintf(fptr, "%d\n", screenResolution.UTILITY_BUTTON_HEIGHT);
    fprintf(fptr, "%d\n", screenResolution.TITLE_WIDTH);
    fprintf(fptr, "%d\n", screenResolution.TITLE_HEIGHT);
    fprintf(fptr, "%d", isSoundOn);
}

//Tudor Iftene
void placestandardButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("standardrez_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("standardrez.jpg", xStart, yStart, xEnd, yEnd);

}

//Tudor Iftene
void placeintermediateButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("intermediaterez_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("intermediaterez.jpg", xStart, yStart, xEnd, yEnd);

}

//Tudor Iftene
void placefullscreenButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("fullscreenrez_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("fullscreenrez.jpg", xStart, yStart, xEnd, yEnd);

}

//Tudor Iftene
bool soundButtonClicked(int x, int y)
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
bool languageButtonClicked(int x, int y)
{
    if(inArea(x, y, screenResolution.WIDTH/2,
                            screenResolution.HEIGHT/ 2+screenResolution.BOTTOM_LABEL_HEIGHT,
                            screenResolution.WIDTH-(screenResolution.WIDTH/4-screenResolution.BUTTON_SIZE),
                            screenResolution.HEIGHT/ 2+ 2*screenResolution.BOTTOM_LABEL_HEIGHT))
    {
        return true;
    }
}

//Tudor Iftene
void placeLanguageButton (int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();
        if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        {
            readImageFromFolder("romana_hover.jpg", xStart, yStart, xEnd, yEnd);
        }
        else
        {
            readImageFromFolder("romana.jpg", xStart, yStart, xEnd, yEnd);
        }

}

//Stefan Vulpe
void placeSoundButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    switch(isSoundOn)
    {
        case 0:
        if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        {
            readImageFromFolder("sound_off_hover.jpg", xStart, yStart, xEnd, yEnd);
        }
        else
        {
            readImageFromFolder("sound_off.jpg", xStart, yStart, xEnd, yEnd);
        }
        break;

        case 1:
        if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        {
            readImageFromFolder("sound_on_hover.jpg", xStart, yStart, xEnd, yEnd);
        }
        else
        {
            readImageFromFolder("sound_on.jpg", xStart, yStart, xEnd, yEnd);
        }
        break;
    }
}

//Tudor Iftene
void setari()
{
    if(isSoundOn == 0)
        PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    readImageFromFolder("fundal.jpg", 0, 0, screenResolution.WIDTH, screenResolution.HEIGHT );

    readImageFromFolder("schimbarerezolutie.jpg", screenResolution.WIDTH/2 - screenResolution.UTILITY_BUTTON_WIDTH,
                        screenResolution.UTILITY_BUTTON_HEIGHT/2,
                        screenResolution.WIDTH/2 + screenResolution.UTILITY_BUTTON_WIDTH,
                        (screenResolution.UTILITY_BUTTON_HEIGHT*3)/2);

    readImageFromFolder("schimbarelimba.jpg", screenResolution.WIDTH / 4 - screenResolution.BUTTON_SIZE,
                        screenResolution.HEIGHT/ 2+screenResolution.BOTTOM_LABEL_HEIGHT ,
                        screenResolution.WIDTH/2,
                        screenResolution.HEIGHT/ 2+ 2*screenResolution.BOTTOM_LABEL_HEIGHT);
    do
    {

        placeSoundButton(screenResolution.BUTTON_MARGIN,
                screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);


        placestandardButton(screenResolution.WIDTH / 4 - screenResolution.BUTTON_SIZE,
                            (screenResolution.HEIGHT / 2 - screenResolution.BUTTON_MARGIN)/2,
                            screenResolution.WIDTH / 4 + screenResolution.BUTTON_SIZE,
                            screenResolution.HEIGHT/ 2);

        placeintermediateButton(screenResolution.WIDTH/2 - screenResolution.BUTTON_SIZE,
                                (screenResolution.HEIGHT/2 - screenResolution.BUTTON_MARGIN)/2,
                                screenResolution.WIDTH/2 + screenResolution.BUTTON_SIZE,
                                screenResolution.HEIGHT/2);

        placefullscreenButton(screenResolution.WIDTH-(screenResolution.WIDTH/4+screenResolution.BUTTON_SIZE),
                                (screenResolution.HEIGHT/2 - screenResolution.BUTTON_MARGIN)/2,
                                screenResolution.WIDTH-(screenResolution.WIDTH/4-screenResolution.BUTTON_SIZE),
                                screenResolution.HEIGHT/2);

        placeLanguageButton(screenResolution.WIDTH/2,
                        screenResolution.HEIGHT/ 2+screenResolution.BOTTOM_LABEL_HEIGHT,
                        screenResolution.WIDTH-(screenResolution.WIDTH/4-screenResolution.BUTTON_SIZE),
                        screenResolution.HEIGHT/ 2+ 2*screenResolution.BOTTOM_LABEL_HEIGHT);

        placeHomeButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int x, y;
            getmouseclick(WM_LBUTTONDOWN, x, y);

            if(languageButtonClicked(x, y))
            {
                atHome = 1; 
                
                if(selectedFolder == 1)
                {
                    selectedFolder = 0;

                    closegraph();

                    delay(100);

                    meniu();
                }
                else
                {
                    selectedFolder = 1;

                    closegraph();

                    delay(100);

                    meniu();
                }
            }

            if(soundButtonClicked(x, y))
            {
                if(isSoundOn == 1)
                {
                    isSoundOn = 0;
                    PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
                }
                else
                {
                    isSoundOn = 1;
                    PlaySoundW(L"res/muzica.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
                }
            }

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

            if(inArea(x, y, screenResolution.WIDTH / 4 - screenResolution.BUTTON_SIZE,
                            (screenResolution.HEIGHT / 2 - screenResolution.BUTTON_MARGIN)/2,
                            screenResolution.WIDTH / 4 + screenResolution.BUTTON_SIZE,
                            screenResolution.HEIGHT/ 2))
            {

                screenResolution = STANDARD_SIZE;

                saveSettings();

                closegraph();

                delay(100);

                meniu();
            }

            if(inArea(x, y, screenResolution.WIDTH/2 - screenResolution.BUTTON_SIZE,
                                (screenResolution.HEIGHT/2 - screenResolution.BUTTON_MARGIN)/2,
                                screenResolution.WIDTH/2 + screenResolution.BUTTON_SIZE,
                                screenResolution.HEIGHT/2))
            {
                screenResolution = INTERMEDIATE_SIZE;

                saveSettings();

                closegraph();

                delay(100);

                meniu();
            }


            if(inArea(x, y, screenResolution.WIDTH-(screenResolution.WIDTH/4+screenResolution.BUTTON_SIZE),
                                (screenResolution.HEIGHT/2 - screenResolution.BUTTON_MARGIN)/2,
                                screenResolution.WIDTH-(screenResolution.WIDTH/4-screenResolution.BUTTON_SIZE),
                                screenResolution.HEIGHT/2))
            {
                screenResolution = FULL_SCREEN;

                saveSettings();

                closegraph();

                delay(100);

                meniu();
            }
        }
    }
    while(1);

}

