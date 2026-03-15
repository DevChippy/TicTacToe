#include <iostream>
#include <time.h>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

const int x = 3;
const int y = 3;

bool debugOn = false;

int currentPlayerTurn = 1;
int gameList[x][y] = {{0}}; // 1 = X, 2 = O, 0 == " "

void dashes()
{
    printf("\n  ");
    for(int i = 0; i < y * 4.2; i++)
    {
        printf("-");
    }
    printf("\n");
}

void showGame()
{
    printf("    ");
    for(int i = 0; i < y; i++)
    {
        if(i < 10) printf("%i   ", i);
        else printf("%i  ", i);
    }

    printf(" < X");
    dashes();

    for(int i = 0; i < x; i++)
    {
        if(i >= 10) printf("%i|", i);
        else printf("%i |", i);

        for(int j = 0; j < y; j++)
        {
            int boxState = gameList[i][j];

            if(boxState == 1) printf(" X |");
            else if(boxState == 2) printf(" O |");
            else if(boxState == 0) printf("   |");
            else if(boxState == 3) printf(" - |");
        }

        dashes();
    }

    printf("^");
    printf("");
    printf("\nY");
}

bool outOfBound(int xInput, int yInput)
{
    if(xInput + 1 > x || xInput < 0)
    {
        if(debugOn) printf("Entered X is out of bound");
        return true;
    }
    else if(yInput + 1 > y || yInput < 0)
    {
        if(debugOn) printf("Entered Y is out of bound");
        return true;
    }
    return false;
}

int checkIfChecked()
{
    if(debugOn) printf("Checking..");

    int counter = 0;
    int foundCheck = 0;

    int positions[x*y] = {};
    int positionsCounter = 0;

    // check rows
    for(int j = 0; j < y; j++)
    {
        foundCheck = 1;

        for(int i = 0; i < x; i++)
        {
            int boxState = gameList[j][i];

            if(boxState != currentPlayerTurn)
            {
                foundCheck = 0;
                positionsCounter = 0;
                break;
            }

            positions[positionsCounter] = j;
            positionsCounter++;
            positions[positionsCounter] = i;
            positionsCounter++;
        }

        if(foundCheck) break;
    }

    // check columns
    if(foundCheck == 0)
    {
        for(int i = 0; i < x; i++)
        {
            foundCheck = 1;

            for(int j = 0; j < y; j++)
            {
                int boxState = gameList[j][i];

                if(boxState != currentPlayerTurn)
                {
                    foundCheck = 0;
                    positionsCounter = 0;
                    break;
                }

                positions[positionsCounter] = j;
                positionsCounter++;
                positions[positionsCounter] = i;
                positionsCounter++;
            }

            if(foundCheck) break;
        }
    }

    // main diagonal
    if(foundCheck == 0)
    {
        foundCheck = 1;

        for(int i = 0; i < x; i++)
        {
            if(gameList[i][i] != currentPlayerTurn)
            {
                foundCheck = 0;
                positionsCounter = 0;
                break;
            }

            positions[positionsCounter] = i;
            positionsCounter++;
            positions[positionsCounter] = i;
            positionsCounter++;
        }
    }

    // other diagonal
    if(foundCheck == 0)
    {
        foundCheck = 1;

        for(int i = 0; i < x; i++)
        {
            if(gameList[i][x - 1 - i] != currentPlayerTurn)
            {
                foundCheck = 0;
                positionsCounter = 0;
                break;
            }

            positions[positionsCounter] = i;
            positionsCounter++;
            positions[positionsCounter] = x - 1 - i;
            positionsCounter++;
        }
    }

    if(foundCheck == 0)
    {
        bool boardFull = true;

        for(int i = 0; i < x; i++)
        {
            for(int j = 0; j < y; j++)
            {
                int boxState = gameList[j][i];
                if(boxState == 0) boardFull = false;
            }
        }

        if(boardFull) foundCheck = 2;
    }

    if(foundCheck)
    {
        for(int i = 0; i < positionsCounter; i += 2)
        {
            int xCordPos = positions[i];
            int yCordPos = positions[i + 1];
            gameList[xCordPos][yCordPos] = 3;
        }
    }

    if(debugOn) printf("\nFound check returned with: %i\n", foundCheck);

    if(currentPlayerTurn == 1) currentPlayerTurn = 2;
    else currentPlayerTurn = 1;

    return foundCheck;
}

int checkIfOnlyNumbers(int x, int y)
{
    while(x > 0)
    {
        int digit = x % 10;
        if(digit < 0 || digit > 9) return 0;
        x /= 10;
    }

    while(y > 0)
    {
        int digit = y % 10;
        if(digit < 0 || digit > 9) return 0;
        y /= 10;
    }

    return 1;
}

void inputMove(int player)
{
    int xInput, yInput;
    bool entered = false;

    while(entered == false)
    {
        printf("\n\nIt's player's %i turn!\nEnter coordinates (X,Y) where you want to put symbol ", currentPlayerTurn);

        if(player == 1) printf("X\n");
        else printf("O\n");

        int result = scanf("%d %d", &yInput, &xInput);

        if(result != 2)
        {
            printf("Invalid input. Please enter two numbers for coordinates (Y, X).\n");
            while(getchar() != '\n');
            continue;
        }

        if(outOfBound(xInput, yInput))
        {
            printf("Please enter a point that is not out of range\n");
        }
        else
        {
            int statusOnInputedPoint = gameList[xInput][yInput];

            if(statusOnInputedPoint == 0)
            {
                entered = true;
                gameList[xInput][yInput] = player;
            }
            else
            {
                printf("Please enter a point that is not already used!\n");
            }
        }
    }
}

void delay(int number_of_seconds)
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();

    while(clock() < start_time + milli_seconds);
}

int main()
{
    if(x > 30 || y > 30)
    {
        printf("X and Y can't be above 30!");
        return 0;
    }

    printf("--------------------------\n");
    printf("Welcome to Tic Tak Toe!\nThis was just a side project so I hope you enjoy it!\nShort info, player 1 is X and player 2 is O\nMade by DevChips in C++ :=)\n\n");
    printf("--------------------------\n\n\n");

    int randomChar;

    delay(1);

    printf("Ready? Click enter to start! :)\n");
    scanf("%c", &randomChar);

    bool gameEnded = false;
    int checkFound = 0;
    int currentPlayer = currentPlayerTurn;

    while(!gameEnded)
    {
        showGame();
        inputMove(currentPlayerTurn);
        checkFound = checkIfChecked();
        currentPlayer = currentPlayerTurn;

        if(checkFound) gameEnded = true;
    }

    printf("\n--------------------------\n");
    showGame();

    if(checkFound == 1)
    {
        printf("\nPlayer %i won!", currentPlayer);
    }
    else if(checkFound == 2)
    {
        printf("\nBoard is full! It's a draw!");
    }

    return 0;
}
