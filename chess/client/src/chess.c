#include "chess.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>

int piece_map[256] = {0};

void _initializePieceMap() {
	for (int i = 0; i < 256; i++)
	{
		piece_map[i] = INVALID_MOVE;
	}
	piece_map['R'] = ROOK_MOVE;
	piece_map['r'] = ROOK_MOVE;
	piece_map['B'] = BISHOP_MOVE;
	piece_map['b'] = BISHOP_MOVE;
	piece_map['Q'] = QUEEN_MOVE;
	piece_map['q'] = QUEEN_MOVE;
	piece_map['K'] = KING_MOVE;
	piece_map['k'] = KING_MOVE;
	piece_map['B'] = BISHOP_MOVE;
	piece_map['b'] = BISHOP_MOVE;
	piece_map['N'] = KNIGHT_MOVE;
	piece_map['n'] = KNIGHT_MOVE;
	piece_map['P'] = PAWN_MOVE;
	piece_map['p'] = PAWN_MOVE;
}

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


void clearBoard(board_t board)
{
    // Set up the empty squares
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
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
    	        if (board[7-i][j] == ' ') {
    	            printf(". ");
    	        } else {
    	            printf("%c ", board[7-i][j]);
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
	char temp = b[7-y][x];
	b[7-y][x] = b[7-j][i];
	b[7-j][i] = ' ';
	return temp;
}

char _removePiece(board_t b, int i, int j)
{
	if (b[7-j][i] == '.')
	{
		return '.';
	}
	char temp = b[7-j][i];
	b[7-j][i] = ' ';
	return temp;
}

char getPieceAt(board_t b, letter_t x, int y)
{
	int adjusted_y = 8-y;
	return b[adjusted_y][x];
}

char setPieceAt(board_t b, letter_t x, int y, char value)
{
	int adjusted_y = 8-y;
	char ret_val = b[adjusted_y][x];
	b[adjusted_y][x] = value;
	return  ret_val;
}

int _isValidMove(board_t b, letter_t x_i, int y_i, letter_t x_f, int y_f, move_type_t move_type, side_t side)
{
	// Out of bounds?
	if (x_i < 0 || x_i > 7 || 
		y_i < 0 || y_i > 7 ||
		x_f < 0 || x_f > 7 ||
		y_f < 0 || y_f > 7)
	{
		return 0;
	}

	if ((isupper(b[7-y_f][x_f]) && isupper(b[7-y_i][x_i])) || (islower(b[7-y_f][x_f]) && islower(b[7-y_i][x_i]))) {
		return 0;
	}

	if ((side == WHITE && isupper(b[7-y_i][x_i])) || (side == BLACK && islower(b[7-y_i][x_i]))) {
		return 0;
	}

	// Individual piece checks
	if (move_type == LONG_CASTLE) {
		if (side == WHITE) {
			if (b[7-0][3] != '.' ||
				b[7-0][2] != '.' ||
				b[7-0][1] != '.' ||
				b[7-0][0] != 'r') {
				return 1;
			}
		} else {
			if (b[7-7][3] != '.' ||
				b[7-7][2] != '.' ||
				b[7-7][1] != '.' ||
				b[7-7][0] != 'R') {
				return 1;
			}
		}
	} 
	else if (move_type == SHORT_CASTLE) {
		if (side == WHITE) {
			if (b[7-0][6] != '.' ||
				b[7-0][5] != '.' ||
				b[7-0][7] != 'r') {
				return 1;
			}
		} else {
			if (b[7-7][6] != '.' ||
				b[7-7][5] != '.' ||
				b[7-7][7] != 'R') {
				return 1;
			}
		}
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
			(x_f == (x_i + 1) && y_f == (y_i - 2))) {
			if ((b[7-y_i][x_i] == 'n' && side == WHITE) ||
				(b[7-y_i][x_i] == 'N' && side == BLACK)) {
				return 1;
			}
		}
		return 0;
	}
	else if (move_type == BISHOP_MOVE)
	{
		if ((b[7-y_i][x_i] == 'B' && side == WHITE) ||
			(b[7-y_i][x_i] == 'b' && side == BLACK))
		{
			return 0;
		}
		if (abs(x_f - x_i) == abs(y_f - y_i))
		{
			int dx = (x_f > x_i) ? 1 : -1;
			int dy = (y_f > y_i) ? 1 : -1;

			x_i += dx;
			y_i += dy;
			
			do {
				if (b[7-y_i][x_i] != ' ') {
					return 0;
				}
				x_i += dx;
				y_i += dy;
			}
			while (x_i != x_f && y_i != y_f);
			return 1;
		}
		return 0;
	} 
	else if (move_type == ROOK_MOVE)
	{
		if (abs(x_f - x_i) == 0 || abs(y_f - y_i) == 0) {
			int dx, dy;
			if (x_f == x_i) {
				dy = (y_f > y_i) ? 1 : -1;
				dx = 0;
			} else if (y_f == y_i) {	
				dx = (x_f > x_i) ? 1 : -1;			
				dy = 0;
			}

			do {
				x_i += dx;
				y_i += dy;
				if (b[7-y_i][x_i] != ' ') {
					return 0;
				}
			}
			while (x_i != x_f && y_i != y_f);

			return 1;
		}
		return 0;
	}
	else if (move_type == QUEEN_MOVE) 
	{
		int dx, dy;
		int temp_x_i = x_i;
		int temp_y_i = y_i;
		if (abs(x_f - x_i) == 0 || abs(y_f - y_i) == 0)
		{
			// Rook-like move
			if (x_f == x_i)
			{
				dy = (y_f > y_i) ? 1 : -1;
				dx = 0;
			} else if (y_f == y_i) {	
				dx = (x_f > x_i) ? 1 : -1;			
				dy = 0;
			}

			do {
				x_i += dx;
				y_i += dy;
				if (b[7-y_i][x_i] != ' ')
				{
					return 0;
				}
			}
			while (x_i != x_f && y_i != y_f);
		}
		
		x_i = temp_x_i;
		y_i = temp_y_i;

		if (abs(x_f - x_i) == abs(y_f - y_i))
		{
			// Bishop-like move
			dx = (x_f > x_i) ? 1 : -1;
			dy = (y_f > y_i) ? 1 : -1;
			
			do {
				x_i += dx;
				y_i += dy;
				
				if (b[7-y_i][x_i] != ' ')
				{
					return 0;
				}
			}
			while (x_i != x_f && y_i != y_f);
		}

		return 1;
	}
	else if (move_type == KING_MOVE)
	{
		// Currently king moves are all moves are valid
		return 1;
	}
	else if (move_type == PAWN_MOVE)
	{
		if (side == WHITE)
		{
			if (y_f <= y_i || 			// Moves backwards?
				b[7-y_i][x_i] != 'p')	// Not your pawn
			{
				return 0;
			}

			// Move up one. Always allowed unless a piece is there...
			if ((y_f == y_i+1 &&      // Moves up 1 and...
				(x_f - x_i) == 0) &&  // Doesnt move left or right
				b[7-y_f][x_f] == ' ') // no piece in the way
			{
				return 1;
			}
			
			// Move up two. Only allowed if no other moves
			if ((y_f == y_i+2 &&
				(x_f - x_i) == 0) &&
				(b[7-y_f-1][x_f] == ' ') &&
				(b[7-y_f][x_f] == ' '))
			{
				return 1;
			}
			
			// Moves diagonal right
			if ((y_f == y_i+1 &&
				(x_f - x_i) == 1) &&
				(b[7-y_f][x_f] != ' ') &&
				(isupper(b[7-y_f][x_f])))
			{
				return 1;
			}
			// Moves diagonal left
			if ((y_f == y_i+1 &&
				(x_f - x_i) == -1) &&
				(b[7-y_f][x_f] != ' ') &&
				(isupper(b[7-y_f][x_f])))
			{
				return 1;
			}
			return 0;
		} 
		else if (side == BLACK) {
			if (y_i <= y_f ||  b[7-y_i][x_i] != 'P') {
				return 0;
			}

			// Move up one. Always allowed unless a piece is there...
			if ((y_f == y_i - 1) &&      // Moves up 1 and...
				((x_f - x_i) == 0) &&  // Doesnt move left or right
				(b[7-y_f][x_f] == ' ')) // no piece in the way
			{
				return 1;
			}
			
			// Move up two. Only allowed if no other moves
			if ((y_f == y_i - 2) &&
				((x_f - x_i) == 0) &&
				((b[7-y_f-1][x_f]) == ' ') &&
				(b[7-y_f][x_f] == ' '))
			{
				return 1;
			}
			
			// Moves diagonal right
			if ((y_f == y_i - 1) &&
				((x_f - x_i) == 1) &&
				(b[7-y_f][x_f] != ' ') &&
				(islower(b[7-y_f][x_f])))
			{
				return 1;
			}
			// Moves diagonal left
			if ((y_f == y_i - 1) &&
				((x_f - x_i) == -1) &&
				(b[7-y_f][x_f] != ' ') &&
				(islower(b[7-y_f][x_f]))) {
				return 1;
			}
			return 0;
		}
	}
	return 1;
}


int _parseChessNotation(char * str, int * x_i, int * y_i, int * x_f, int * y_f, side_t side)
{
	// Parse string for indicees to move
	int out;

	*x_i = str[1] - 'a';
	*y_i = str[2] - '1';
	*x_f = str[3] - 'a';
	*y_f = str[4] - '1';

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
	} else if (strncmp(str, "0-0-0", 5) == 0) {
		out = LONG_CASTLE;
		if (side == WHITE)
		{
			*x_i = 4;
			*y_i = 0;
			*x_f = 2;
			*y_f = 0;
		} else {
			*x_i = 4;
			*y_i = 7;
			*x_f = 2;
			*y_f = 7;
		}

	} else if (strncmp(str, "0-0", 3) == 0) {
		out = SHORT_CASTLE;
		if (side == WHITE)
		{
			*x_i = 4;
			*y_i = 0;
			*x_f = 6;
			*y_f = 0;
		} else {
			*x_i = 4;
			*y_i = 7;
			*x_f = 6;
			*y_f = 7;
		}
	} else {
		printf("Pawn move\n");
		*x_i = str[0] - 'a';
		*y_i = str[1] - '1';
		*x_f = str[2] - 'a';
		*y_f = str[3] - '1';
		printf("%d, %d, %d, %d\n", *x_i, *y_i, *x_f, *y_f);
		out = PAWN_MOVE;
	}	
	return out;
}


int inBounds(int x, int y)
{
	if (x < 8 && x >= 0 && y < 8 && y >= 0)
	{
		return 1;
	}
	return 0;
}


int _checks(board_t b, move_type_t move_type, int x, int y, side_t side)
{
	char expected_king;
	if (side == WHITE)
	{
		expected_king = 'K'; // Looking for black king 
	} else {
		expected_king = 'k'; // Looking for white king
	}

	if (move_type == KNIGHT_MOVE)
	{
		if (
			((b[y-1][x+2] == expected_king) && inBounds(x+2,y-1)) ||
			((b[y+1][x+2] == expected_king) && inBounds(x+2,y+1)) ||
			((b[y-1][x-2] == expected_king) && inBounds(x-2,y-1)) ||
			((b[y+1][x-2] == expected_king) && inBounds(x-2,y+1)) ||
			((b[y+2][x-1] == expected_king) && inBounds(x-1,y+2)) ||
			((b[y-2][x-1] == expected_king) && inBounds(x-1,y-2)) ||
			((b[y+2][x+1] == expected_king) && inBounds(x+1,y+2)) ||
			((b[y-2][x+1] == expected_king) && inBounds(x+1,y-2))
			)
		{
			return 1;
		}
		return 0;
	} 
	else if (move_type == BISHOP_MOVE)
	{
		int dx, dy;
		int curr_x = x;
		int curr_y = y;

		int directions_x[4] = {-1, 1,-1, 1};
		int directions_y[4] = {-1,-1, 1, 1};
		for (int i = 0; i < 4; i++)
		{
			// Up left
			dy = directions_y[i];
			dx = directions_x[i];
			do {
				curr_x += dx;
				curr_y += dy;

				if (b[curr_y][curr_x] == expected_king)
				{
					return 1;
				}
				if (b[curr_y][curr_x] != ' ')
				{
					break;
				}
			} while (inBounds(curr_x, curr_y));
		}
		return 0;
	}
	else if (move_type == ROOK_MOVE)
	{
		// Up
		for (int i = y-1; i > 0; i--)
		{
			if (b[i][x] == expected_king)
			{
				return 1;
			}
			if (b[i][x] != ' ')
			{
				break;
			}
		}
		
		// Down
		for (int i = y+1; i < 8; i++)
		{
			if (b[i][x] == expected_king)
			{
				return 1;
			}
			if (b[i][x] != ' ')
			{
				break;
			}
		}

		// Left
		for (int i = x-1; i > 0; i--)
		{
			if (b[y][i] == expected_king)
			{
				return 1;
			}
			if (b[y][i] != ' ')
			{
				break;
			}
		}

		// Right
		for (int i = x+1; i < 8; i++)
		{
			if (b[y][i] == expected_king)
			{
				return 1;
			}
			if (b[y][i] != ' ')
			{
				break;
			}
		}
		// no king found => no check
		return 0;
	} else if (move_type == QUEEN_MOVE) {
		int dx, dy;
		int curr_x = x;
		int curr_y = y;

		int directions_x[4] = {-1, 1,-1, 1};
		int directions_y[4] = {-1,-1, 1, 1};
		for (int i = 0; i < 4; i++)
		{
			// Up left
			dy = directions_y[i];
			dx = directions_x[i];
			do {
				curr_x += dx;
				curr_y += dy;

				if (b[curr_y][curr_x] == expected_king)
				{
					return 1;
				}
				if (b[curr_y][curr_x] != ' ')
				{
					break;
				}
			} while (inBounds(curr_x, curr_y));
		}
		
		// Up
		for (int i = y-1; i > 0; i--)
		{
			if (b[i][x] == expected_king)
			{
				return 1;
			}
			if (b[i][x] != ' ')
			{
				break;
			}
		}
		
		// Down
		for (int i = y+1; i < 8; i++)
		{
			if (b[i][x] == expected_king)
			{
				return 1;
			}
			if (b[i][x] != ' ')
			{
				break;
			}
		}

		// Left
		for (int i = x-1; i > 0; i--)
		{
			if (b[y][i] == expected_king)
			{
				return 1;
			}
			if (b[y][i] != ' ')
			{
				break;
			}
		}

		// Right
		for (int i = x+1; i < 8; i++)
		{
			if (b[y][i] == expected_king)
			{
				return 1;
			}
			if (b[y][i] != ' ')
			{
				break;
			}
		}
		// no king found => no check
		return 0;

	} else if (move_type == PAWN_MOVE) {
		if (side == WHITE)
		{
			if ((b[y-1][x-1] == 'K') ||
				(b[y-1][x+1] == 'K'))
			{
				return 1;
			}
		}
		else if (side == BLACK)
		{
			if ((b[y+1][x-1] == 'k') ||
				(b[y+1][x+1] == 'k'))
			{
				return 1;
			}
		} else {
			printf("Invalid color\n");
			return -1; 
		}	
	} else {
		printf("Invalid move type\n");
		return -1;
	}
	return 0;
}



int _getCheckStatus(board_t b, side_t side)
{
	_initializePieceMap();

	side_t other_side;

	if (side == WHITE)
	{
		other_side = BLACK;
	} else if (side == BLACK) {
		other_side = WHITE;
	} else {
		printf("Invalid side\n");
		return -1;
	}

	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			move_type_t move_type = piece_map[b[y][x]];
			if (move_type != INVALID_MOVE)
			{
				//side_t side = isupper(b[y][x]) ? BLACK : WHITE;
				if (side == WHITE && isupper(b[y][x]) ||
					side == BLACK && islower(b[y][x]))
				{
					if (_checks(b, move_type, x, y, other_side) == 1)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

int _inCheckMate(board_t b, side_t side)
{
	int y = 0;
	int x = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((b[i][j] == 'k' && side == WHITE) ||
				(b[i][j] == 'K' && side == BLACK))
				{
					y = i;
					x = j;
				}
		}
	}

	int x_s[8] = {-1, 0, 1,-1, 1,-1, 0, 1};
	int y_s[8] = {-1,-1,-1, 0, 0, 1, 1, 1};

	for (int i = 0; i < 8; i++)
	{
		if (_isValidMove(b, x, y+7, x+x_s[i], y+y_s[i]+7, KING_MOVE, side))
		{
			char prev = _move(b, x, y+7, x+x_s[i], y+y_s[i]+7); // Try move
			if (_getCheckStatus(b, side) == 0)
			{
				// King has an exit route
				_move(b, x+x_s[i], y+y_s[i]+7, x, y+7); // Move back
				b[y+y_s[i]][x+x_s[i]] = prev;
				return 0;
			}
			_move(b, x+x_s[i], y+y_s[i]+7, x, y+7); // Move back
			b[y+y_s[i]+7][x+x_s[i]] = prev;
		}
	}
	if (_getCheckStatus(b, side))
	{
		return 2; // Checkmate
	}
	return 1; // Stalemate
}

int move(board_t b, char * str, int * check_status, side_t side)
{
	int x_i, y_i, x_f, y_f;

	int parsed_move = _parseChessNotation(str, &x_i, &y_i, &x_f, &y_f, side);	
	if (_isValidMove(b, x_i, y_i, x_f, y_f, parsed_move, side) == 0)
	{
		printf("invalid move\n"); 
		return (char) 0;
	}

	side_t other_side;
	if (side == WHITE) {
		other_side = BLACK;
	} else if (side == BLACK) {
		other_side = WHITE;
	}
	char taken = _removePiece(b, x_f, y_f);

	printf("removed peice: %c\n", taken);
	printf("Moving piece to %d, %d, %d, %d\n", x_i, y_i, x_f, y_f);
	
	int check_stat = _getCheckStatus(b, side);
	
	if (parsed_move == SHORT_CASTLE)
	{
		if (side == WHITE)
		{
			_move(b, 7, 0, 5, 0);
		} else {
			_move(b, 7, 7, 5, 7);
		}
	}

	if (parsed_move == LONG_CASTLE)
	{
		if (side == WHITE)
		{
			_move(b, 0, 0, 3, 0);
		} else {
			_move(b, 0, 7, 3, 7);
		}
	}

	_move(b, x_i, y_i, x_f, y_f);
	// If after the move were still in check then its invalid
	// This handles 2 cases:
	// 	Still in check after last turn
	//	Moved into check
	if (_getCheckStatus(b, side) == 1)
	{
		_move(b, x_f, y_f, x_i, x_f);
		return (char) 0;
	}

	check_stat = _getCheckStatus(b, other_side);
	*check_status = check_stat;
	return taken;
}
