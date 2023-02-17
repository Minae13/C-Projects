#include <cstdlib>
#include <time.h>

//  Generate an empty board using width and height parameters
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

//  Generate random integer and then turn it into 0 or 1
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

//  Initialise the pregenerated board with the random 0 and 1 using the previous function
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

//  Pretty type the board changing the 0 to empty spaces and the 1 to #
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