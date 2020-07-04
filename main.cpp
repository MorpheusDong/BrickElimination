#include "BrickElimination.h"

int main()
{
    GameBrickElimination NewGame;

    NewGame.game_start();
    NewGame.game_run();
    NewGame.game_over();

    return 0;
}