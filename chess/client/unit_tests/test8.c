#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test__setPieceAt(void **state)
{
	(void) state;
	
	board_t b;
	resetBoard(b);
	
	char out;
	
	out = setPieceAt(b, A, 1, 'z');
	assert_int_equal(out, 'r');
	out = getPieceAt(b, A, 1);
	assert_int_equal(out, 'z');

	out = setPieceAt(b, B, 1, 'z');
	assert_int_equal(out, 'n');
	out = getPieceAt(b, B, 1);
	assert_int_equal(out, 'z');
	
	out = setPieceAt(b, C, 1, 'z');
	assert_int_equal(out, 'b');
	out = getPieceAt(b, C, 1);
	assert_int_equal(out, 'z');

	out = setPieceAt(b, D, 1, 'z');
	assert_int_equal(out, 'q');
	out = getPieceAt(b, D, 1);
	assert_int_equal(out, 'z');

	out = setPieceAt(b, A, 8, 'z');
	assert_int_equal(out, 'R');
	out = getPieceAt(b, A, 8);
	assert_int_equal(out, 'z');
	
	out = setPieceAt(b, B, 8, 'z');
	assert_int_equal(out, 'N');
	out = getPieceAt(b, B, 8);
	assert_int_equal(out, 'z');

	out = setPieceAt(b, C, 8, 'z');
	assert_int_equal(out, 'B');
	out = getPieceAt(b, C, 8);
	assert_int_equal(out, 'z');

	out = setPieceAt(b, D, 8, 'z');
	assert_int_equal(out, 'Q');
	out = getPieceAt(b, D, 8);
	assert_int_equal(out, 'z');
}
