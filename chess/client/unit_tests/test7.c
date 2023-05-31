#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test__getPieceAt(void **state)
{
	(void) state;
	
	int result = -1;

	board_t b;
	resetBoard(b);
	
	char out;

	out = _getPieceAt(b, A, 1);
	assert_int_equal(out, 'r');

	out = _getPieceAt(b, B, 1);
	assert_int_equal(out, 'n');
	
	out = _getPieceAt(b, C, 1);
	assert_int_equal(out, 'b');

	out = _getPieceAt(b, D, 1);
	assert_int_equal(out, 'q');

	out = _getPieceAt(b, A, 8);
	assert_int_equal(out, 'R');
	
	out = _getPieceAt(b, B, 8);
	assert_int_equal(out, 'N');

	out = _getPieceAt(b, C, 8);
	assert_int_equal(out, 'B');

	out = _getPieceAt(b, D, 8);
	assert_int_equal(out, 'Q');
}
