#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int **deadState(int width, int height)
{
    int **boardState = new int *[height];
    for (int i = 0; i < height; i++)
    {
        boardState[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            boardState[i][j] = '0';
        }
    }
    return boardState;
}

int randomInt()
{
    int randomValue = rand();
    if (randomValue % 2 == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int **randomState(int width, int height)
{
    srand(time(0));
    int **state = deadState(width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            state[i][j] = randomInt();
        }
    }

    return state;
}

char** render(int** state, int width, int height) 
{
    char** renderedState = new char*[height];
    for (int i = 0; i < height; i++){
        renderedState[i] = new char[width];
        for (int j = 0; j < width; j++){
            if (state[i][j] == 1) {
                renderedState[i][j] = '#';
            } else {
                renderedState[i][j] = ' ';
            }
        }
    }

    return renderedState;
}

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
