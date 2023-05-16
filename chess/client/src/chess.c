#include "chess.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

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

void printBoard(board_t board, side_t side)
{
	if (side == WHITE)
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
	} else if (side == BLACK) {	
    	printf("  +-----------------+\n");
    	for (int i = 0; i < 8; i++) {
    	    printf("%d | ", i + 1);
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
    	printf("    g f e d c b a h\n");
	} else {
		printf("Invalid side\n");
	}
}


char _move(board_t b, int i, int j, int x, int y)
{
	char temp = b[8-y][x];
	b[8-y][x] = b[8-j][i];
	b[8-j][i] = '.';
	return temp;
}



char _removePiece()
{
	return 'a';
}

char _getPieceAt(board_t b, int x, int y)
{
	return b[x - 8][y];
}


int _isValidMove(board_t b, int x_i, int y_i, int x_f, int y_f, int move_type)
{
	// Out of bounds?
	if (x_i < 0 || x_i > 7 || 
		y_i < 0 || y_i > 7 ||
		x_f < 0 || x_f > 7 ||
		y_f < 0 || y_f > 7)
	{
		return 0;
	}

	// Individual piece checks
	if (move_type == LONG_CASTLE)
	{
		return 1;
	} 
	else if (move_type == SHORT_CASTLE)
	{
		return 1;
	} 
	else if (move_type == KNIGHT_MOVE) 
	{
		if ((x_f == (x_i + 2) && y_f == (y_i - 1)) ||
			(x_f == (x_i + 2) && y_f == (y_i + 1)) ||
			(x_f == (x_i - 2) && y_f == (y_i - 1)) ||
			(x_f == (x_i - 2) && y_f == (y_i + 1)) ||
			(x_f == (x_i - 1) && y_f == (y_i + 2)) ||
			(x_f == (x_i - 1) && y_f == (y_i - 2)) ||
			(x_f == (x_i + 1) && y_f == (y_i + 2)) ||
			(x_f == (x_i + 1) && y_f == (y_i - 2)))
		{
			return 1;
		}
		return 0;
	}
	else if (move_type == BISHOP_MOVE)
	{
		if (abs(x_f - x_i) == abs(y_f - y_i))
		{
			return 1;
		}
		return 0;
	} 
	else if (move_type == ROOK_MOVE)
	{
		if (abs(x_f - x_i) == 0 || abs(y_f - y_i) == 0)
		{
			return 1;
		}
		return 0;
	}
	else if (move_type == QUEEN_MOVE) 
	{
		return 1;
	}
	else if (move_type == KING_MOVE)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int _parseChessNotation(char * str, int * x_i, int * y_i, int * x_f, int * y_f, side_t side)
{
	// Parse string for indicees to move
	int out;

	*x_i = str[1] - 'a';
	*y_i = str[2] - '0';
	*x_f = str[4] - 'a';
	*y_f = str[5] - '0';

	if (str[0] == 'N') {
		out = KNIGHT_MOVE;
	} else if (str[0] == 'B') {
		out = BISHOP_MOVE;
	} else if (str[0] == 'R') {
		out = ROOK_MOVE;
	} else if (str[0] == 'Q') {
		out = QUEEN_MOVE;
	} else if (str[0] == 'K') {
		out = KING_MOVE;
	} else if (strcmp(str, "O-O") == 0) {
		out = LONG_CASTLE;
	} else if (strcmp(str, "O-O-O") == 0) {
		out = SHORT_CASTLE;
	} else {
		*x_i = str[0] - 'a';
		*y_i = str[1] - '1';
		*x_f = str[2] - 'a';
		*y_f = str[3] - '1';
		out = PAWN_MOVE;
	}	
	return out;
}

int _getCheckStatus(board_t b)
{
	return -1;
}

int move(board_t b, char * str, int * checkstatus, side_t side)
{
	int x_i, y_i, x_f, y_f;

	int parsed_move = _parseChessNotation(str, &x_i, &y_i, &x_f, &y_f, side);	
	if (_isValidMove(b, x_i, y_i, x_f, y_f, parsed_move) == 0)
	{
		return (char) 0;
	}

	char taken = _removePiece(x_f, y_f);
	_move(b, x_i, y_i, x_f, y_f);
	
	int check_stat = _getCheckStatus(b);
	
	return taken;
}
