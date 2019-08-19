#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define SIZE 3

typedef struct State {
    int board[SIZE][SIZE];
    int steps;
} state;

int findPath(int startx, int starty, int destx, int desty, state gameState);


void printBoard(state * gameState) {
    int i,j;
    for(i = 0; i < SIZE; i++)  {
        for(j = 0; j < SIZE; j++) {
            if(gameState->board[i][j] > 0) {
                printf(" %d ", gameState->board[i][j]);
            }
            else {
                printf("%d ", gameState->board[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));
    
    int destX = rand() % SIZE;
    int destY = rand() % SIZE;
    
    state theGame;
    int i,j;
    for( i = 0; i < SIZE; i++)
        for(j = 0; j < SIZE; j++)
            theGame.board[i][j] = 0;
            
    theGame.steps = 0;
    
    
    int obsX = rand() % SIZE;
    int obxY = rand() % SIZE;
    theGame.board[obsX][obxY] = -1;
    theGame.board[0][0] = 0;
    theGame.board[destX][destY] = -2;    
    printf("Displaying the board before the game starts:\n");
    printBoard(&theGame);
    printf("\n");   
    //Set the obstacles  
    printf("MINIMUM NUMBER OF STEPS : %d", findPath(0,0, destX, destY, theGame));
}

int canMove(int x, int y, state * check) {
    if( x >= SIZE || x < 0) {
        return 0;
    }
    if(y >= SIZE || y < 0 ) {
        return 0;
    }
    if(check->board[x][y] == -1) {
        return 0;
    }
    if(check->board[x][y] == 0 || check->board[x][y] == -2) {
        return 1;
    }   
    //Check for obstacles
    return 0;
    
}

int findPath(int startx, int starty, int destx, int desty, state gameState) {
    static int minimum = 100000;
    //Moved to this step
    gameState.steps++;
    gameState.board[startx][starty] = gameState.steps;  
    if(startx == destx && starty == desty) {
        // PRINT OUT BOARD HERE
        // 
        if(gameState.steps < minimum) {
            minimum = gameState.steps;
        }
        printf("Printing the board!\n");
        printBoard(&gameState);
        printf("\n");
        return -1;      
    }   
    if(canMove(startx + 1, starty, &gameState)) {
        //Move
        
        findPath(startx + 1, starty, destx, desty, gameState);
    }
    
    if(canMove(startx - 1, starty, &gameState)) {
        //Move
        findPath(startx - 1, starty, destx, desty, gameState);
    }
    if(canMove(startx, starty + 1, &gameState)) {
          findPath(startx , starty + 1, destx, desty, gameState);
    }
    if(canMove(startx, starty -1, &gameState)) {
        
        //Move
          findPath(startx , starty - 1, destx, desty, gameState);
    }
    
    return minimum;

}
