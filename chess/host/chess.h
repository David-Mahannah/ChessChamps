#ifndef CHESS_H
#define CHESS_H


typedef char board_t[8][8];

// Sets board to default state
void resetBoard(board_t b);

// Print out a pretty version of the board
void printBoard(board_t b);

// Return 1 if move is valid
// 		  0 if move is invalid
int isValidMove(board_t b, int i, int j, int x, int y);

int move(board_t b, char * cnot);


#endif
