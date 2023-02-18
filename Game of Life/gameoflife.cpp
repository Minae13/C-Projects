#include <iostream>
#include "board.h"
using namespace std;

int main()
{
    int** state = randomState(3,3);
    char** board = render(state, 3,3);
    // print multidimensional array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
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
