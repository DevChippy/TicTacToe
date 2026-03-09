#include <iostream>
#include <cstring>

using namespace std;

const int x = 3;
const int y = 3;

bool debugOn = false;

int currentPlayerTurn = 1;
int gameList[x][y] =
{
    {0,0,0},
    {0,0,0},
    {0,0,0}
}; // 1 = X, 2 = O, 0 == " "

void showGame()
{
    printf("    ");
    for(int i = 0; i<x; i++)
    {
        printf("%i   ",i);
    }
    printf(" < Y");
    printf("\n  -------------\n");
    for(int i=0; i<x; i++)
    {
        printf("%i |",i);
        for(int j=0; j<y; j++)
        {
            int boxState = gameList[i][j];
            if(boxState == 1)
            {
                printf(" X |");
            }
            else if (boxState == 2)
            {
                printf(" O |");
            }
            else if (boxState == 0)
            {
                printf("   |");
            }
        }
        printf("\n  -------------\n");
    }

    printf("^");
    printf("");
    printf("\nX");
}

bool outOfBound(int xInput,int yInput)
{
    if(xInput + 1 > x || xInput  < 0)
    {
        if(debugOn)
            printf("Entered X is out of bound");
        return true;
    }
    else if (yInput + 1 > y || yInput < 0)
    {

        if(debugOn)
            printf("Entered Y is out of bound");
        return true;
    }
    return false;
}

int checkIfChecked()
{
    if(debugOn)
        printf("Checking..");
    // check rows
    int counter = 0;
    int foundCheck = 0;

    for(int j=0; j<y; j++)
    {
        foundCheck = 1;

        for(int i = 0; i<x; i++)
        {
            int boxState = gameList[j][i];
            if(boxState != currentPlayerTurn)
            {
                foundCheck = 0;
                break;
            }
        }

        if(foundCheck)
        {
            break;
        }
    }

    // check columns
    if(foundCheck == 0)
    {
        for(int i=0; i<x; i++)
        {
            foundCheck = 1;

            for(int j = 0; j<y; j++)
            {
                int boxState = gameList[j][i];
                if(boxState != currentPlayerTurn)
                {
                    foundCheck = 0;
                    break;
                }
            }

            if(foundCheck)
            {
                break;
            }
        }
    }

    // main diagonal (0,0 -> 2,2)
    if(foundCheck == 0)
    {
        foundCheck = 1;

        for(int i = 0; i < x; i++)
        {
            if(gameList[i][i] != currentPlayerTurn)
            {
                foundCheck = 0;
                break;
            }
        }
    }

    // other diagonal (0,2 -> 2,0)
    if(foundCheck == 0)
    {
        foundCheck = 1;

        for(int i = 0; i < x; i++)
        {
            if(gameList[i][x-1-i] != currentPlayerTurn)
            {
                foundCheck = 0;
                break;
            }
        }
    }

    if(foundCheck == 0)
    {
        bool boardFull = true;
        for(int i = 0; i<x; i++)
        {
            for(int j=0; j<y; j++)
            {
                int boxState = gameList[j][i];
                if(boxState == 0)
                {
                    boardFull = false;
                }
            }
        }
        if(boardFull) foundCheck = 2;
    }


    if(debugOn)
        printf("\nFound check returned with: %i\n",foundCheck);


    if(currentPlayerTurn == 1) currentPlayerTurn = 2;
    else currentPlayerTurn = 1;

    return foundCheck;
}

void inputMove(int player)
{
    int xInput;
    int yInput;
    bool entered = false;

    while(entered == false)
    {
        printf("\nIt's player's %i turn!\nEnter coordinates (Y,X) where you want to put symbol ",currentPlayerTurn);
        if(player == 1)
        {
            printf("X\n");
        }
        else
        {
            printf("O\n");
        }
        scanf("%i",&xInput);
        scanf("%i",&yInput);

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

};

int main()
{
    printf("--------------------------\n");
    printf("Welcome to Tic Tak Toe!\nThis was just a side project so I hope you enjoy it!\nShort info, player 1 is X and player 2 is O\nMade by DevChips in C++ :=)\n\n");
    printf("--------------------------\n\n\n");
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

    printf("--------------------------");
    showGame();
    if(checkFound == 1)
    {
        printf("Player %i won!",currentPlayer);
    }

    if(checkFound == 0)
    {
        printf("");
    }
    else if (checkFound == 2)
    {
        printf("Board is full! It's a draw!");
    }

    return 0;
}
