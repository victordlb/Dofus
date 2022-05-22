#include <stdio.h>
#include <stdlib.h>
#include <allegro.h>
#include "header.h"
#include <time.h>

/// juste le main ;)
int main()
{
    initialisation();
    BITMAP* fond;
    t_cases** tabcases;
    tabcases = chargement_map(3);
    fond = charger_map(tabcases,3);
    while(!key[KEY_ESC])
    {
        blit(fond, screen,0,0,0,0,SCREEN_W, SCREEN_H);
    }
    //lancement();
    return 0;
}END_OF_MAIN();

