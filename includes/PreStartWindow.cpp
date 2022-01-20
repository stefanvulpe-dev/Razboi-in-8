#include <graphics.h>
#include <winbgim.h>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "Settings.h"

//Stefan Vulpe
void placeTitle()
{
    readImageFromFolder("title2.jpg", (screenResolution.WIDTH - screenResolution.TITLE_WIDTH) / 2,
                    100,
                    (screenResolution.WIDTH + screenResolution.TITLE_WIDTH) / 2,
                    100 + screenResolution.TITLE_HEIGHT);
}

//Stefan Vulpe
void placePvpButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("pvp_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("pvp_button.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void placePvcButton(int xStart, int yStart, int xEnd, int yEnd)
{
    int x = mousex(), y = mousey();

    if(inArea(x, y, xStart, yStart, xEnd, yEnd))
        readImageFromFolder("pvc_button_hover.jpg", xStart, yStart, xEnd, yEnd);
    else
        readImageFromFolder("pvc_button.jpg", xStart, yStart, xEnd, yEnd);
}

//Stefan Vulpe
void preStartWindow()
{
    if(isSoundOn == 0)
    {
        PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );
    }

    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    setBackground(0, 0, screenResolution.WIDTH, screenResolution.HEIGHT);

    placeTitle();

    do {

        placeCreditsButton(screenResolution.BUTTON_MARGIN,
                screenResolution.BUTTON_MARGIN,
                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE);

        placeInstructionsButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                                screenResolution.BUTTON_MARGIN,
                                screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                                screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE);

        placePvpButton((screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    (screenResolution.HEIGHT - screenResolution.UTILITY_BUTTON_HEIGHT * 2) / 2,
                    (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                    screenResolution.HEIGHT / 2);

        placePvcButton((screenResolution.WIDTH - screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2,
                            (screenResolution.WIDTH + screenResolution.UTILITY_BUTTON_WIDTH) / 2,
                            screenResolution.HEIGHT / 2 + screenResolution.UTILITY_BUTTON_HEIGHT);

        placeHomeButton(screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

        placeSettingsButton(screenResolution.WIDTH - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.HEIGHT - (screenResolution.BUTTON_MARGIN + screenResolution.BUTTON_SIZE),
                    screenResolution.WIDTH - screenResolution.BUTTON_MARGIN,
                    screenResolution.HEIGHT - screenResolution.BUTTON_MARGIN);

        clickListener();
    } while(1);
}
