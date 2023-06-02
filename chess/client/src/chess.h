#ifndef CHESS_H
#define CHESS_H

typedef char board_t[8][8];
extern int piece_map[256];

// Used to differentiate between different views
// By default to board is in white notation but I
// doubt black wants to look at their pieces from
// white's perspective.
typedef enum {
	BLACK,
	WHITE
} side_t;

typedef enum {
	ALG,      // Algebraic
	LNG_ALG,  // Long algebraic
} chess_fmt_t;

typedef enum {
	INVALID_MOVE,
	LONG_CASTLE,
	SHORT_CASTLE,
	KNIGHT_MOVE,
	BISHOP_MOVE,
	ROOK_MOVE,
	QUEEN_MOVE,
	KING_MOVE,
	PAWN_MOVE
} move_type_t;

typedef struct coord {
	int x_i;
	int y_i;
	int x_f;
	int y_f;
} coord_t;

typedef enum {A,B,C,D,E,F,G,H} letter_t;

/**
 * Gets piece at letter, num value.
 */
char getPieceAt(board_t b, letter_t x, int y);

/**
 * \brief Sets piece at letter, num to value. 
 * \param a The first integer.
 * \param b The second integer.
 * \return Returns the previous value at said location
 */
char setPieceAt(board_t b, letter_t x, int y, char value);


/**
 * Sets up piece map to get move_type_t from char
 */
void _initializePieceMap();

/**
 * Sets board to default state
 * 
 * @param board Current board
 */
void resetBoard(board_t board);

/**
 * Sets board to clear state
 *
 * @param board Current board
 */
void clearBoard(board_t board);

/**
 * Move a piece to the destination
 *
 * @param board Current board
 * @param str Chess notation for the current move
 * @param check_status Assigned status check value
 * @param side WHITE of BLACK
 */
int move(board_t b, char * str, int * check_status, side_t side);


/**
 * Interface functions (Exclusive to testing)
 * Print out a pretty version of the board
 */
void printBoard(board_t b, side_t s);


// HELPER FUNCTIONS

/**
 * Remove a piece
 * Returns the piece type
 */
char _removePiece();

/**
 * Returns the type of the move and both start and end points
 * Only format checking occurs in this function. Invalid moves are
 * checke later.
 */
int _parseChessNotation(char * str, int * x_i, int * y_i, int * x_f, int * y_f, side_t side);


/**
 *
 *
 *
 */
coord_t _parseChessNotation2(char * str, side_t side, chess_fmt_t format);



/**
 * Helper move function that works with array coords
 * instead of chess notation.
 */
char _move(board_t b, int i, int j, int x, int y);

/**
 * Return piece at x, y in the board array
 */
//char _getPieceAt(board_t b, int x, int y);

/**
 * Return 1 if move is valid
 * 		  0 if move is invalid
 */
int _isValidMove(board_t b, letter_t x_i, int y_i, letter_t x_f, int y_f, move_type_t move_type, side_t side);

/**
 * Return 0 if not in check
 * Return 1 if in check
 * Return 2 if in checkmate
 */
int _getCheckStatus(board_t b, side_t side);


/**
 *
 *
 */
int _checks(board_t b, move_type_t move_type, int x, int y, side_t side);

/**
 *
 *
 */
int _inCheckMate(board_t b, side_t side);
#endif
