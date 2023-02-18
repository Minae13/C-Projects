#include <cstdlib>
#include <time.h>
#include <windows.h>
#include <unistd.h>
using namespace std;

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
    if (randomValue % 2 == 0 || randomValue % 3 == 0 || randomValue % 5 == 0)
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

//  Calculate the next state of the board using Life's rules
int **nextBoardState(int **initialState, int width, int height)
{
    int **nextState = initialState;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int liveNeighbors = 0;

            // Count the number of live neighbors for the current cell
            for (int p = max(0, i - 1); p <= min(i + 1, height - 1); p++)
            {
                for (int q = max(0, j - 1); q <= min(j + 1, width - 1); q++)
                {
                    if (p != i || q != j)
                    {
                        liveNeighbors += initialState[p][q];
                    }
                }
            }

            // Apply the rules of the game to determine the new state of the cell
            if (initialState[i][j] == 0)
            {
                if (liveNeighbors == 3)
                {
                    nextState[i][j] = 1;
                }
            }
            else
            {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                {
                    nextState[i][j] = 0;
                }
                else
                {
                    nextState[i][j] = 1;
                }
            }
        }
    }

    return nextState;
}

//  Pretty type the board changing the 0 to empty spaces and the 1 to #
char **render(int **state, int width, int height)
{
    char **renderedState = new char *[height];
    for (int i = 0; i < height; i++)
    {
        renderedState[i] = new char[width];
        for (int j = 0; j < width; j++)
        {
            if (state[i][j] == 1)
            {
                renderedState[i][j] = '#';
            }
            else
            {
                renderedState[i][j] = ' ';
            }
        }
    }

    return renderedState;
}

//  Infinite loop
void infinite(int width, int height)
{
    int **boardState = randomState(width, height);
    char **renderedBoard = render(boardState, width, height);
    while (true)
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                cout << renderedBoard[i][j];
            }
            cout << endl;
        }
        
        boardState = nextBoardState(boardState, width, height);
        renderedBoard = render(boardState, width, height);
        sleep(0.999);
    }
}