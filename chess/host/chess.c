#include "chess.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void resetBoard(board_t board)
{
// Set up the white pieces
    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';
    for (int i = 0; i < 8; i++) {
        board[1][i] = 'P';
    }
    
    // Set up the empty squares
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
    
    // Set up the black pieces
    for (int i = 0; i < 8; i++) {
        board[6][i] = 'p';
    }
    board[7][0] = 'r';
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'q';
    board[7][4] = 'k';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';
}

void printBoard(board_t board)
{
    printf("  +-----------------+\n");
    for (int i = 0; i < 8; i++) {
        printf("%d | ", 8 - i);
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == ' ') {
                printf(". ");
            } else {
                printf("%c ", board[i][j]);
            }
        }
        printf("|\n");
    }
    printf("  +-----------------+\n");
    printf("    a b c d e f g h\n");
}

int isValidMove(board_t b, int i, int j, int x, int y)
{
	return 1;
}



int _move(board_t b, int i, int j, int x, int y)
{
	b[8-y][x] = b[8-j][i];
	b[8-j][i] = '.';
	return 1;
}


char at(board_t b, int x, int y)
{
	return b[x - 8][y];
}

int move(board_t b, char * str)
{
	// Parse string for indicees to move
	int x_i;
	int y_i;
	int x_f;
	int y_f;
	
	if (str[0] == 'N' || 
		str[0] == 'B' || 
		str[0] == 'R' || 
		str[0] == 'Q' || 
		str[0] == 'K') 
	{
		x_i = str[1] - 'a';
		y_i = str[2] - '0';
		x_f = str[4] - 'a';
		y_f = str[5] - '0';

		if (x_i < 0 || x_i > 7 || 
			y_i < 0 || y_i > 7 ||
			x_f < 0 || x_f > 7 ||
			y_f < 0 || y_f > 7)
		{
			printf("Out of bounds >:(\n");
			return -1;
		}

		printf("Standard move from %d,%d to %d,%d!\n", x_i, y_i, x_f, y_f);

		// Check if move piece matches the piece at that location

		if (str[0] == 'N') {
			// Valid options
			if ((x_f == (x_i + 2) && y_f == (y_i - 1)) ||
				(x_f == (x_i + 2) && y_f == (y_i + 1)) ||
				(x_f == (x_i - 2) && y_f == (y_i - 1)) ||
				(x_f == (x_i - 2) && y_f == (y_i + 1)) ||
				(x_f == (x_i - 1) && y_f == (y_i + 2)) ||
				(x_f == (x_i - 1) && y_f == (y_i - 2)) ||
				(x_f == (x_i + 1) && y_f == (y_i + 2)) ||
				(x_f == (x_i + 1) && y_f == (y_i - 2)))
			{
				printf("Valid!\n");
			} else {
				printf("Invalid\n");
				return -1;
			}
		} else if (str[0] == 'B') {
			if (abs(x_f - x_i) == abs(y_f - y_i))
			{
				printf("Valid!\n");
			} else {
				printf("Invalid bishop move");
				return -1;
			}
		} else if (str[0] == 'R') {
			if (abs(x_f - x_i) == 0 || abs(y_f - y_i) == 0)
			{
				printf("Valid");
			} else {
				printf("Invalid rook move");
				return -1;
			}
		} else if (str[0] == 'Q') {

		} else if (str[0] == 'K') {

		}

		_move(b, x_i, y_i, x_f, y_f);

		// Check if this is a valid move

	}
	else if (strcmp(str, "O-O") == 0)
	{
		printf("Short castle!\n");
	}
	else if (strcmp(str, "O-O-O") == 0)
	{
		printf("Long castle!\n");
	} 
	else // Pawn move
	{
		printf("Pawn move!\n");
		
		x_i = str[0] - 'a';
		y_i = str[1] - '0';
		x_f = str[3] - 'a';
		y_f = str[4] - '0';

		if (x_i < 0 || x_i > 7 || 
			y_i < 0 || y_i > 7 ||
			x_f < 0 || x_f > 7 ||
			y_f < 0 || y_f > 7)
		{
			printf("Out of bounds >:(\n");
			return -1;
		}
		_move(b, x_i, y_i, x_f, y_f);
	}
	
	// Check if it's a valid move
	//if (isValidMove(b, i, j, x, y))
	//{
	//	_move(b, i, j, x, y);
	//	return 0;
	//}
	return -1;
}


