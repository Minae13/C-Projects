#include <Windows.h>
#include <random>
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

//  Generate an empty board using width and height parameters
int **deadState(int width, int height)
{
    // Allocate memory for the array of pointers
    int **boardState = new int *[height];
    for (int i = 0; i < height; i++)
    {
        // Allocate memory for each row
        boardState[i] = new int[width];
        for (int j = 0; j < width; j++)
        {
            boardState[i][j] = 0;
        }
    }
    return boardState;
}

//  Generate random integer and then turn it into 0 or 1
int randomInt()
{
    // Create a random device to seed the generator
    std::random_device rd;
    // Create a Mersenne Twister engine
    std::mt19937 gen(rd());
    // Create a uniform distribution that produces either 0 or 1
    std::uniform_int_distribution<> dis(0, 1);

    // Generate a random number using the distribution and return it
    return dis(gen);
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

    for (int i = 0; i < height; i++)
    {
        delete[] state[i];
    }
    delete[] state;
}

int countNeighbors(int **board, int row, int col, int width, int height)
{
    int count = 0;
    // check top (unless cell in top row)
    if (row > 0 && board[row - 1][col])
        count++;

    // check bottom (unless cell in bottom row)
    if (row < height - 1 && board[row + 1][col])
        count++;

    // check left (unless cell in left column)
    if (col > 0 && board[row][col - 1])
        count++;

    // check right (unless cell in right column)
    if (col < width - 1 && board[row][col + 1])
        count++;

    // check top left (unless cell in top-left corner)
    if (row > 0 && col > 0 && board[row - 1][col - 1])
        count++;

    // check top right (unless cell in top-right corner)
    if (row > 0 && col < width - 1 && board[row - 1][col + 1])
        count++;

    // check bottom left (unless cell in bottom-left corner)
    if (row < height - 1 && col > 0 && board[row + 1][col - 1])
        count++;

    // check bottom right (unless cell in bottom-right corner)
    if (row < height - 1 && col < width - 1 && board[row + 1][col + 1])
        count++;

    return count;
}

//  Calculate the next state of the board using Life's rules
int **nextBoardState(int **initialState, int width, int height)
{
    int **nextState = deadState(width, height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int liveNeighbors = countNeighbors(initialState, i, j, width, height);

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
        renderedState[i] = new char[width + 1]; // add 1 for the null terminator
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
        renderedState[i][width] = '\0'; // null terminate the string
    }

    return renderedState;
}

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

        // Calculate the next state of the board
        int **nextState = nextBoardState(boardState, width, height);
        // Free memory for the current state of the board
        for (int i = 0; i < height; i++)
        {
            delete[] boardState[i];
        }
        delete[] boardState;

        // Set the next state as the current state
        boardState = nextState;
        // Render the new state of the board
        renderedBoard = render(boardState, width, height);

        // Wait for one second before rendering the next frame
        std::this_thread::sleep_for(std::chrono::milliseconds(90));
    }
}

void getWindowSize(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}