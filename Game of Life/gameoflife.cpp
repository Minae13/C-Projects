#include <iostream>
#include <wtypes.h>
#include <windows.h>
#include "board.h"
using namespace std;

int main()
{
    int horizontal = 0;
    int vertical = 0;
    getWindowSize(vertical,horizontal);
    infinite(horizontal,vertical);

    return 0;
}
