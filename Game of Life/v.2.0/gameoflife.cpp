#include <iostream>
#include <Windows.h>
#include "board.h"
using namespace std;

int main()
{
    int width, height;
    getWindowSize(width, height);
    Board game(width, height);
    game.randomize();
    game.run();

    return 0;
}
