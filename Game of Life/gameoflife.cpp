#include <iostream>
#include "board.h"
using namespace std;

int main()
{
    int** state = randomState(30,50);
    char** board = render(state, 30,50);
    // print multidimensional array
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 30; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // free memory
    for (int i = 0; i < 3; i++)
    {
        delete[] state[i];
        delete[] board[i];
    }
    delete[] state;
    delete[] board;

    return 0;
}
