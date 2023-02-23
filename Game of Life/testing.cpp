#include <iostream>
#include "board.h"
using namespace std;

void printMatrix(int **boardState) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << boardState[i][j];
        }
        cout << endl;
    }
}

void results(int testNum, int **initialState, int **expectedState, int **nextState) {
    bool equal = true;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (expectedState[i][j] != nextState[i][j]){
                equal = false;
            }
        }
    }
    
    if (equal) {
        cout << "TEST " << testNum << " PASSED !!" << endl;
    }
    else {
        cout << "TEST " << testNum << " FAILED !!" << endl;
    }
    cout << "Initial State:" << endl;
        printMatrix(initialState);
        cout << "Expected State:" << endl;
        printMatrix(expectedState);
        cout << "Your State:" << endl;
        printMatrix(nextState);
}
    
void test()
{
    int **initialState = deadState(3,3);
    int **expectedState = deadState(3,3);
    int **nextState = nextBoardState(initialState,3,3);

    // TEST 1: all dead cells remain dead
    results(1,initialState,expectedState,nextState);

    // TEST 2: dead cells with exactly 3 neighbors become alive
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i == 0 && j == 2) || (i == 1 && (j == 1 || j == 2))) {
                initialState[i][j] = 1;
                expectedState[i][j] = 1;
            } else if (i == 0 && j == 1){
                expectedState[i][j] = 1;
            }
        }
    }
    nextState = nextBoardState(initialState,3,3);
    results(2,initialState,expectedState,nextState);

    // TEST 3: live cells with 1 or 0 neighbors die
    initialState = deadState(3,3);
    expectedState = deadState(3,3);
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if ((i == 0 && j == 0) || (i == 2 && j ==2)) {
                initialState[i][j] = 1;
            } else if (i == 1 && j == 1) {
                initialState[i][j] = 1;
                expectedState[i][j] = 1;
            }
        }
    }
    nextState = nextBoardState(initialState,3,3);
    results(3,initialState,expectedState,nextState);

    // TEST 4: live cells with 2 or 3 neighbors stay alive
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 2) {
                initialState[i][j] = 1;
                expectedState[i][j] = 1;
            } else if ((i == 0 && j == 1) || (i == 2 && j == 1) || (i == 2 && j ==2)){
                expectedState[i][j] = 1;
            }
        }
    }
    nextState = nextBoardState(initialState,3,3);
    results(4,initialState,expectedState,nextState);

    // TEST 5: live cells with more than 3 neighbors die
    initialState = deadState(3,3);
    expectedState = deadState(3,3);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            expectedState[i][j] = 1;

            if ((i == 0 && j == 1) || (i == 1 && (j == 0 || j == 2)) || (i == 2 && j == 1)) {
                initialState[i][j] = 1;
            } else if (i == 1 && j == 1){
                expectedState[i][j] = 0;
                initialState[i][j] = 1;
            }
        }
    }
    nextState = nextBoardState(initialState,3,3);
    results(5,initialState,expectedState,nextState);

}

int main()
{
    test();

    return 0;
}
