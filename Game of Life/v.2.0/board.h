#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

// Represents the game board
class Board
{
private:
    int width;
    int height;
    vector<vector<int>> boardState; 

public:
    // Constructor
    Board(int w, int h)
    {
        width = w;
        height = h;
        boardState = vector<vector<int>>(height, vector<int>(width, 0));
    }

    // Initialise board with live and dead cells
    void randomize()
    {
        random_device rd;
        mt19937 eng(rd());
        uniform_int_distribution<> distr(0, 1);

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                boardState[i][j] = distr(eng);
            }
        }
    }

    // Calculate next board state
    void updateBoard()
    {
        vector<vector<int>> newBoardState = vector<vector<int>>(height, vector<int>(width, 0));

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int count = countNeighbors(i, j);
                if (boardState[i][j] == 1)
                {
                    if (count == 2 || count == 3)
                    {
                        newBoardState[i][j] = 1;
                    }
                }
                else
                {
                    if (count == 3)
                    {
                        newBoardState[i][j] = 1;
                    }
                }
            }
        }

        boardState = newBoardState;
    }

    // Count live neighbors of given cells
    int countNeighbors(int row, int col)
    {
        int count = 0;
        // check top
        if (row > 0 && boardState[row - 1][col])
            count++;
        // check bottom
        if (row < height - 1 && boardState[row + 1][col])
            count++;
        // check left
        if (col > 0 && boardState[row][col - 1])
            count++;
        // check right
        if (col < width - 1 && boardState[row][col + 1])
            count++;
        // check top left
        if (row > 0 && col > 0 && boardState[row - 1][col - 1])
            count++;
        // check top right
        if (row > 0 && col < width - 1 && boardState[row - 1][col + 1])
            count++;
        // check bottom left
        if (row < height - 1 && col > 0 && boardState[row + 1][col - 1])
            count++;
        // check bottom right
        if (row < height - 1 && col < width - 1 && boardState[row + 1][col + 1])
            count++;
        return count;
    }

    // Render board to console
    void render()
    {
        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (boardState[i][j] == 1)
                {
                    cout << "#";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    // Run game infinitely
    void run()
    {
        while (true)
        {
            render();
            updateBoard();
            std::this_thread::sleep_for(std::chrono::milliseconds(90));
        }
    }
};

// Get window size
void getWindowSize(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}