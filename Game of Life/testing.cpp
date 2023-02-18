#include <iostream>
#include "board.h"
using namespace std;

void test(int **initialState, int height, int width, int **nextState)
{
    int **expectedState = new int *[height];
    for (int i = 0; i < height; i++)
    {
        expectedState[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            expectedState[i][j] = 0;
        }
    }

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
                    expectedState[i][j] = 1;
                }
            }
            else
            {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                {
                    expectedState[i][j] = 0;
                }
                else
                {
                    expectedState[i][j] = 1;
                }
            }
        }
    }

    bool equal = false;
    //  check if passed
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (expectedState[i][j] == nextState[i][j])
            {
                equal = true;
            }
            else
            {
                equal = false;
            }
        }
    }

    if (equal)
    {
        cout << "SUCCESS!!!" << endl;
    }
    else
    {
        cout << "FAIL!!!" << endl
             << "Expected Board:" << endl;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << expectedState[i][j] << " ";
            }
            cout << endl;
        }
        cout << "Your results:";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << nextState[i][j] << " ";
            }
            cout << endl;
        }
    }
}

int main()
{
    int width = 3;
    int height = 3;

    int **initialState = randomState(width,height);
    int **nextState = nextBoardState(initialState,width,height);
    test(initialState, width,height, nextState);

    // free memory
    for (int i = 0; i < 3; i++)
    {
        delete[] initialState[i];
        delete[] nextState[i];
    }
    delete[] initialState;
    delete[] nextState;

    return 0;
}
