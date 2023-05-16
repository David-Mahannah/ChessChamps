#ifndef CHESS_H
#define CHESS_H

#define INVALID_MOVE 0
#define LONG_CASTLE 1
#define SHORT_CASTLE 2
#define KNIGHT_MOVE 3
#define BISHOP_MOVE 4
#define ROOK_MOVE 5
#define QUEEN_MOVE 6
#define KING_MOVE 7
#define PAWN_MOVE 8

typedef char board_t[8][8];

// Used to differentiate between different views
// By default to board is in white notation but I
// doubt black wants to look at their pieces from
// white's perspective.
typedef enum {
	BLACK,
	WHITE
} side_t;


// Sets board to default state
void resetBoard(board_t b);

// Move a piece to the destination
int move(board_t b, char * str, int * checkStatus, side_t side);


/* Interface functions (Exclusive to testing) */

// Print out a pretty version of the board
void printBoard(board_t b, side_t s);

// HELPER FUNCTIONS

// Remove a piece
// Returns the piece type
char _removePiece();

// Returns the type of the move and both start and end points
// Only format checking occurs in this function. Invalid moves are
// checke later.
int _parseChessNotation(char * str, int * x_i, int * y_i, int * x_f, int * y_f, side_t side);

// Helper move function that works with array coords
// instead of chess notation.
char _move(board_t b, int i, int j, int x, int y);

// Return piece at x, y in the board array
char _getPieceAt(board_t b, int x, int y);

// Return 1 if move is valid
// 		  0 if move is invalid
int _isValidMove(board_t b, int i, int j, int x, int y, int move_type);

// Return 0 if not in check
// Return 1 if in check
// Return 2 if in checkmate
int _getCheckStatus(board_t b);

#endif
