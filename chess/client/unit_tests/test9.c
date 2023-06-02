#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test__inCheckMate(void **state)
{
	(void) state;
	
	board_t b;
	clearBoard(b);
	int out;

	// WHITE king in checkmate
	setPieceAt(b, B, 3, 'B');
	setPieceAt(b, F, 3, 'P');
	setPieceAt(b, E, 4, 'P');
	setPieceAt(b, D, 5, 'k');
	setPieceAt(b, G, 5, 'R');
	setPieceAt(b, C, 7, 'R');
	setPieceAt(b, D, 7, 'Q');
	out = _inCheckMate(b, WHITE);
	assert_int_equal(out, 2);
	clearBoard(b);

	// WHITE king in stalemate
	setPieceAt(b, E, 3, 'P');
	setPieceAt(b, D, 5, 'k');
	setPieceAt(b, C, 7, 'R');
	setPieceAt(b, E, 7, 'Q');
	out = _inCheckMate(b, WHITE);
	assert_int_equal(out, 1);
	clearBoard(b);

	
	// WHITE king not in stalemate but in checkmate
	setPieceAt(b, E, 3, 'P');
	setPieceAt(b, D, 5, 'k');
	setPieceAt(b, C, 7, 'R');
	setPieceAt(b, D, 8, 'R');
	setPieceAt(b, E, 7, 'Q');
	out = _inCheckMate(b, WHITE);
	assert_int_equal(out, 2);
	clearBoard(b);
}
