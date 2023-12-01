/*
Author: Barbara Emke
Date:   October 21, 2022

Allows user to play a tic tac toe game with a computer that
randomly chooses it's coordinates on CLI
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char board[5][11];

//Checks if coordinates have been played yet or not
//Gets new input if invalid
void updateBoard(char *update){
        int updated = 0;
        int x, y;

        while(!updated){
                //Seperates x and y coordinates
                char *xCoord = strtok(update,",");
                sscanf(xCoord, "%d", &x);
                char *yCoord = strtok(NULL, ",");
                sscanf(yCoord, "%d", &y);

                //Prompts re-entry if spot already taken
                if(!(board[2*(y-1)][1+(4*(x-1))] == ' ') | !(x<4 & x>0) | !(y<4 & y>0)){
                        printf("Invalid entry please re-enter X,Y coordinates: ");
                        scanf("%s", update);
                }
                else{updated = 1;}
        }
        //Updates board with entry
        board[2*(y-1)][1+(4*(x-1))] = 'X';
}

//Prints board
void printBoard(){
        printf("\n");
        for(int i=0; i < 5; i++){
                for(int j=0; j<11; j++){
                        printf("%c", board[i][j]);
                }
        printf("\n");
        }
        printf("\n\n");
}


//Checks for every possible  win condition including a tie
int checkWin(){

        //Tests Columns for winning Line
        int win = 0;
        for(int x = 1;x<4;x++){
                char test = board[0][1+(4*(x-1))];
                if(test == ' '){
                        win = 0;
                        continue;
                }
                for(int y= 2; y<4;y++){
                        if(!(board[2*(y-1)][1+(4*(x-1))] == test)){
                                win=0;
                                break;
                        }
                        win++;
                        if(win == 2){
                        printBoard();
                        return win;}
                }
        }

        //Tests rows for winning line
        win = 0;
        for(int y = 1;y<4;y++){
                char test = board[2*(y-1)][1];
                if(test == ' '){
                        win = 0;
                        continue;
                }
                for(int x= 2; x<4;x++){
                        if(!(board[2*(y-1)][1+(4*(x-1))] == test)){
                                win=0;
                                break;
                        }
                        win++;
                        if(win == 2){
                        printBoard();
                        return win;}
                }
        }

        //Checks for right diagonal win
        win = 0;
        for(int i = 1;i<3;i++){
                if(board[2*(i-1)][1+(4*(i-1))] == ' '){break;}
                if(board[2*(i-1)][1+(4*(i-1))] == board[2*((i+1)-1)][1+(4*((i+1)-1))]){win++;}
                else{win=0;}
                if(win == 2){
                printBoard();
                return win;}
        }

        //Checks for left diagonal win
        win=0;
        if(!(board[0][9] == ' ')){
                if(board[0][9] == board[2][5] & board[2][5] == board[4][1]){win=2;}
                else{win=0;}
                if(win == 2){
                printBoard();
                return win;}
        }
		//Checks to see if there are any more moves left to play
        for(int x = 1;x<4;x++){
                for(int y= 2; y<4;y++){
                        if((board[2*(y-1)][1+(4*(x-1))] == ' ')){
                                return 0;
                        }
                }
        }

        //Executes only if a tie occurs
        printBoard();
        return -1;
}

//Grabs user coordinate info and calls updates board with move
//calls function to check win status
int playerTurn(){
        char userMove[10];
        printf("Your turn, enter X,Y coordinates for your move: ");
        scanf("%s", userMove);
        updateBoard(userMove);
        return checkWin();
}

//Randomly generates coordinates until a valid move is found
//Places O on its coordinates
//Checks to see win status
int computerTurn(){
        int x, y = 0;
        int valid = 0;
        while(!valid){
                x = (rand() %
                (3 - 1 + 1)) + 1;
                y = (rand() %
                (3 - 1 + 1)) + 1;
                if(board[2*(y-1)][1+(4*(x-1))] == ' '){
                        board[2*(y-1)][1+(4*(x-1))] = 'O';
                        valid=1;
                        return checkWin();
                }
        }
}

//Initializes 2D array with tic tac toe board layout
void initializeBoard(){
        for(int i=0;i<11;i++){
                board[0][i] = ' ';
                board[1][i] = '-';
                board[2][i] = ' ';
                board[3][i] = '-';
                board[4][i] = ' ';
        }
        for(int i = 0;i<5;i++){
                board[i][3] = '|';
                board[i][7] = '|';
        }
        printBoard();
}

int main() {
        char userName[15];
        int playerWinner = 0;
        int computerWinner = 0;

        //Game introduction
        printf("\n\n\n\n\n");
        printf("********************************************\n");
        printf("Tic Tac Toe\n");
        printf("COMP 2131 - Fall 2022\n");
        printf("You Vs. Computer\n");
        printf("********************************************\n\n\n");

        //Get User name
        printf("What is your name?\n\n");
        scanf("%[^\n]", userName);

        //Initiates Game
        printf("\nHello %s let's play a game!!\n\n", userName);
        printf("Be sure to enter coordinates in correct format.\n\n");
        printf("You = X     Computer = O\n");

        initializeBoard();

        //Loops turns until win or tie condidtion met
        while(!playerWinner & !computerWinner){
                playerWinner = playerTurn(); //player's turn

                //If player won
                if(playerWinner > 0){
                        printf("You win!\n\n");
                        break;
                }

                //if tied
                else if(playerWinner < 0){
                        printf("It's a tie!\n\n");
                        break;
                }
				
                //if computer won
                computerWinner = computerTurn(); //computer's turn
                if(computerWinner > 0){
                        printf("Computer wins!\n\n");
                        break;
                }

                //if tied
                else if(computerWinner < 0){
                        printf("It's a tie!\n\n");
                        break;
                }
                printBoard();
        }
	return 0;
}