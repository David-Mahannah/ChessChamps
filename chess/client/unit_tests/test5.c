#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test__checks(void **state)
{
	(void) state;
	
	board_t b;
	clearBoard(b);
	int out;

	// WHITE Rook checks BLACK king
	setPieceAt(b, A, 1, 'r');
	setPieceAt(b, A, 4, 'K');
	out = _checks(b, ROOK_MOVE, 0, 7, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	// BLACK Rook checks WHITE king
	setPieceAt(b, A, 8, 'R');
	setPieceAt(b, A, 5, 'k');
	out = _checks(b, ROOK_MOVE, 0, 0, BLACK);
	assert_int_equal(out, 1);
	clearBoard(b);

	// WHITE Rook checks wrong king
	setPieceAt(b, A, 1, 'r');
	setPieceAt(b, A, 4, 'k');
	out = _checks(b, ROOK_MOVE, 0, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);

	// BLACK Rook checks wrong king
	setPieceAt(b, A, 8, 'R');
	setPieceAt(b, A, 5, 'K');
	out = _checks(b, ROOK_MOVE, 0, 0, BLACK);
	assert_int_equal(out, 0);
	clearBoard(b);

	// WHITE Rook doesnt check king at all
	setPieceAt(b, A, 1, 'r');
	setPieceAt(b, A, 3, 'p');
	setPieceAt(b, A, 4, 'K');
	out = _checks(b, ROOK_MOVE, 0, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);

	// BLACK Rook doesnt check king at all
	setPieceAt(b, A, 8, 'R');
	setPieceAt(b, A, 6, 'p');
	setPieceAt(b, A, 5, 'k');
	out = _checks(b, ROOK_MOVE, 0, 0, BLACK);
	assert_int_equal(out, 0);
	clearBoard(b);







	// Knight checks king
	setPieceAt(b, B, 1, 'n');
	setPieceAt(b, C, 3, 'K');
	out = _checks(b, KNIGHT_MOVE, 1, 7, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	// Knight checks wrong king
	setPieceAt(b, B, 1, 'n');
	setPieceAt(b, C, 3, 'k');
	out = _checks(b, KNIGHT_MOVE, 1, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);

	// Knight doesn't check king
	setPieceAt(b, B, 1, 'n');
	setPieceAt(b, C, 4, 'K');
	out = _checks(b, KNIGHT_MOVE, 1, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);



	// Bishop checks king
	setPieceAt(b, C, 1, 'b');
	setPieceAt(b, A, 3, 'K');
	out = _checks(b, BISHOP_MOVE, 2, 7, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	// Bishop checks wrong king
	setPieceAt(b, C, 1, 'b');
	setPieceAt(b, A, 3, 'k');
	out = _checks(b, BISHOP_MOVE, 2, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);

	// Bishop doesnt check king
	setPieceAt(b, C, 1, 'b');
	setPieceAt(b, B, 2, 'p');
	setPieceAt(b, A, 3, 'K');
	out = _checks(b, BISHOP_MOVE, 2, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);



	// Queen checks diagonally
	setPieceAt(b, D, 1, 'q');
	setPieceAt(b, B, 3, 'K');
	out = _checks(b, QUEEN_MOVE, 3, 7, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	// Queen checks vertically
	setPieceAt(b, D, 1, 'q');
	setPieceAt(b, D, 3, 'K');
	out = _checks(b, QUEEN_MOVE, 3, 7, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	setPieceAt(b, D, 8, 'Q');
	setPieceAt(b, D, 6, 'k');
	out = _checks(b, QUEEN_MOVE, 3, 0, BLACK);
	assert_int_equal(out, 1);
	clearBoard(b);

	// Queen doesnt check	
	setPieceAt(b, C, 1, 'b');
	setPieceAt(b, B, 2, 'p');
	setPieceAt(b, A, 3, 'K');
	out = _checks(b, ROOK_MOVE, 2, 7, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);


	// WHITE Pawn checks BLACK
	setPieceAt(b, D, 2, 'p');
	setPieceAt(b, C, 3, 'K');
	out = _checks(b, PAWN_MOVE, 3, 6, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	// BLACK Pawn checks WHITE
	setPieceAt(b, D, 7, 'P');
	setPieceAt(b, C, 6, 'k');
	out = _checks(b, PAWN_MOVE, 3, 1, BLACK);
	assert_int_equal(out, 1);
	clearBoard(b);


	// WHITE Pawn checks WHITE
	setPieceAt(b, D, 2, 'p');
	setPieceAt(b, C, 3, 'k');
	out = _checks(b, PAWN_MOVE, 3, 6, WHITE);
	assert_int_equal(out, 0);
	clearBoard(b);

	// BLACK Pawn checks BLACK
	setPieceAt(b, D, 7, 'P');
	setPieceAt(b, C, 6, 'K');
	out = _checks(b, PAWN_MOVE, 3, 1, BLACK);
	assert_int_equal(out, 0);
	clearBoard(b);
}
