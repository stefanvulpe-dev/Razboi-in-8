#include <iostream>
#include <graphics.h>
#include <winbgim.h>

#include "includes/InGameWindow.h"
#include "includes/Menu.h"
#include "includes/Settings.h"
#include "includes/History.h"

using namespace std;

int main()
{
    isSoundOn = 1;

    initializeSizes();  

    writeAndReadSettings();

    atHome = 1;

    selectedFolder = 1;

    playerA_wins = 0, playerB_wins = 0, nrOfMoves = 50;

    if(isSoundOn)
        PlaySoundW(L"res/muzica.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP );

    meniu();

    return 0;
}