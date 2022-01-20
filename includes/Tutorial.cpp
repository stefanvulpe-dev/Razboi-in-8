#include <graphics.h>
#include <winbgim.h>
#include <cstdio>

#include "Menu.h"
#include "InGameWindow.h"
#include "Board.h"
#include "PreStartWindow.h"
#include "Settings.h"

//Tudor Iftene
void tutorial()
{
    if(isSoundOn == 0)
        PlaySoundW(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

    initwindow(screenResolution.WIDTH, screenResolution.HEIGHT, (char *)"Razboi in 8");

    readImageFromFolder("Instructiuni.jpg", 0, 0, screenResolution.WIDTH, screenResolution.HEIGHT);

    do
    {
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
    }
    while(1);
}
