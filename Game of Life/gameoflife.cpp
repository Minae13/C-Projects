#include <iostream>
#include <wtypes.h>
#include <windows.h>
#include "board.h"
using namespace std;

int main()
{
    int width, height;
    getWindowSize(width, height);
    infinite(width, height);

    return 0;
}
