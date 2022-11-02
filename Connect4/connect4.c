#include <stdlib.h>
#include <stdio.h>
#define max(x, y) (((x) > (y)) ? (x) : (y))
#define min(x, y) (((x) < (y)) ? (x) : (y))
//#define NK_IMPLEMENTATION
//#include "nuklear.h"
const RedTeam = 1;
const YellowTeam = 2;
struct gameState
{
    char **board;
    char currentPlayer;
    char winner;
    int x; //total width
    int y; //total height 
    //int lastMove[2];
}; 
struct gameState createGameState(int x, int y)
{
    struct gameState newGameState;
    newGameState.board = malloc((x) * sizeof(char*));
    
    //for (int i = 0; i < 5 * 5; i++)
    //    test.board[i] = i + 1;

    for (int i = 0; i < x; i++) {
        newGameState.board[i] = malloc((y) * sizeof(char));
        printf("\n");
        for (int j = 0; j < y; j++)
        {
            newGameState.board[i][j] = 0;
            printf("%d", newGameState.board[i][j]);
        }
    }
    newGameState.winner = 0;
    newGameState.currentPlayer = RedTeam;
    newGameState.x = x;
    newGameState.y = y;
    //newGameState.lastMove[0] = -1;
    //newGameState.lastMove[1] = -1;
    return newGameState;
};
int* GetMoves(struct gameState state)
{
    int* moves = malloc((state.x) * sizeof(int));
    for(int i; i < state.x; i++)
    {
        for(int j; j < state.y; j++)
        {
            if(state.board[i][j] == 0)
            {
                moves[i] = j;
                break;
            }
            moves[i] = -1;
        }
    }
    return moves;
}
/*
Make a move 
returns 0 for a failed move
returns 1 for a successful move
returns 2 for a winning move 
*/
char MakeMove(struct gameState state,int x,int y)
{
    if(x < 0 || y < 0 || state.board[x][y] != 0){
        return 0;
    }
    if(y > 0 && (state.board[x][y-1] == 0 ) )
    {
        return 0;
    }
    if(y >= state.y || x >= state.x)
    {
        return 0;
    }
    state.board[x][y] = state.currentPlayer;
    if(moveDoesWin(x,y,state))
    {
        state.winner = state.currentPlayer;
        return 2;
    }
    return 1;
};
/*
returns 0 for does not win
returns 1 for wins
*/
int moveDoesWin(int x, int y, struct gameState state)
{
    int requirement = 4;
    int num; //How many unbroken
    //Does this win up/down

    int* column = state.board[x];
    int start = max(y - requirement, 0);
    int end = min(state.y, y + requirement);
    for(int i = start ; i < end; i++)
    {
        if(column[i] == state.currentPlayer)
        {
            num++;
            if(num >= requirement)
                return 1;
        } else{
            num = 0;
        }
    }
    //Does win left/right
    num = 0;
    start = max(x - requirement, 0);
    end = min(state.x, x + requirement);
    for(int i = max(x - requirement, 0); i < min(state.x, x + requirement); i++)
    {
        if(state.board[i][y] == state.currentPlayer)
        {
            num++;
            if(num >= requirement)
                return 1;
        } else{
            num = 0;
        }
    }
    //Does win up-right diag
    num = 0;
    int Smaller = min(x, min(y, requirement));
    int offsetX = x-Smaller;
    int offsetY = y-Smaller;


    int Upper = Smaller + min(state.x - x, state.y - y);
    for(int i = 0; i < Upper ; i++)
    {
        if(state.board[offsetX+i][offsetY+i] == state.currentPlayer)
        {
            num++;
            if(num >= requirement)
                return 1;
        } else{
            num = 0;
        }
    }

    //Does win up-left diag
    num = 0;
    Smaller = min(x, min(y, requirement));
    offsetX = x-Smaller;
    offsetY = y-Smaller;


    Upper = Smaller + min(state.x - x, state.y - y);
    for(int i = 0; i < Upper ; i++)
    {
        if(state.board[state.x - (offsetX+i)][offsetY+i] == state.currentPlayer)
        {
            num++;
            if(num >= requirement)
                return 1;
        } else{
            num = 0;
        }
    }

    return 0;

}
int main(int argc, char *argv[])
{
    int x = 5;
    int y = 5;
    char *xchar;
    char *ychar;

    if(argc > 1)
    {  
        char *xChar = argv[1];
        x = atoi(xChar);
        printf("%d\n", x);
    }
    else{
        printf("Enter X size ");
        scanf("%d", &x);
    }
    if(argc > 2)
    {
        char *yChar = argv[2];
        y = atoi(yChar);
        printf("%d\n", y);
    }
    else
    {
        printf("Enter Y size");
        scanf("%d", &y);
    };
    struct gameState game = createGameState(x, y);



    printf("hi");
    printf("%d\n", game.board[1][1]);
};