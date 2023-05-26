#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include "../src/chess.h"
#include "tests.h"

void test_parseChessNotation(void **state)
{
	(void) state;
	
	int result = -1;
	int x_i, y_i, x_f, y_f;

	/* Knight Move */
	char * knight_moves[5] = {"Nb1c3", "Ng8f6", "Ne5d3", "Nd2b3", "Nf3h4"};
	int knight_expected[5][4] = {
    	{1, 0, 2, 2}, // b1 to c3
    	{6, 7, 5, 5}, // g8 to f6
    	{4, 4, 3, 2}, // e5 to d3
    	{3, 1, 1, 2}, // d2 to b3
    	{5, 2, 7, 3}  // f3 to h4
	};

	for (int i = 0; i < 5; i++)
	{
		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, KNIGHT_MOVE);
		assert_int_equal(x_i, knight_expected[i][0]);
		assert_int_equal(y_i, knight_expected[i][1]);
		assert_int_equal(x_f, knight_expected[i][2]);
		assert_int_equal(y_f, knight_expected[i][3]);
		
		result=_parseChessNotation(knight_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, KNIGHT_MOVE);
		assert_int_equal(x_i, knight_expected[i][0]);
		assert_int_equal(y_i, knight_expected[i][1]);
		assert_int_equal(x_f, knight_expected[i][2]);
		assert_int_equal(y_f, knight_expected[i][3]);
	}
	
	/* Bishop Move */	
	char * bishop_moves[5] = {"Bc1h6", "Be4a8", "Bd7h3", "Bb2g7", "Bf3c6"};
	int bishop_expected[5][4] = {
    	{2, 0, 7, 5}, // c1 to h6
    	{4, 3, 0, 7}, // e4 to a8
    	{3, 6, 7, 2}, // d7 to h3
    	{1, 1, 6, 6}, // b2 to g7
    	{5, 2, 2, 5}  // f3 to c6
	};

	for (int i = 0; i < 5; i++)
	{

		result=_parseChessNotation(bishop_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, BISHOP_MOVE);
		assert_int_equal(x_i, bishop_expected[i][0]);
		assert_int_equal(y_i, bishop_expected[i][1]);
		assert_int_equal(x_f, bishop_expected[i][2]);
		assert_int_equal(y_f, bishop_expected[i][3]);

		result=_parseChessNotation(bishop_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);

		assert_int_equal(x_i, bishop_expected[i][0]);
		assert_int_equal(y_i, bishop_expected[i][1]);
		assert_int_equal(x_f, bishop_expected[i][2]);
		assert_int_equal(y_f, bishop_expected[i][3]);
		assert_int_equal(result, BISHOP_MOVE);
	}

	/* Rook Move */	
	char * rook_moves[5] = {"Ra1a5", "Rh1h6", "Rd3d7", "Re2b2", "Rf3f7"};
	int rook_expected[5][4] = {
    	{0, 0, 0, 4}, // a1 to a5
    	{7, 0, 7, 5}, // h1 to h6
    	{3, 2, 3, 6}, // d3 to d7
    	{4, 1, 1, 1}, // e2 to b2
    	{5, 2, 5, 6}  // f3 to f7
	};	

	for (int i = 0; i < 5; i++)
	{
		result=_parseChessNotation(rook_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, ROOK_MOVE);
		assert_int_equal(x_i, rook_expected[i][0]);
		assert_int_equal(y_i, rook_expected[i][1]);
		assert_int_equal(x_f, rook_expected[i][2]);
		assert_int_equal(y_f, rook_expected[i][3]);

		result=_parseChessNotation(rook_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, ROOK_MOVE);
		assert_int_equal(x_i, rook_expected[i][0]);
		assert_int_equal(y_i, rook_expected[i][1]);
		assert_int_equal(x_f, rook_expected[i][2]);
		assert_int_equal(y_f, rook_expected[i][3]);
	}

	/* Queen Move */
	char * queen_moves[5] = {"Qd1d5", "Qh1e4", "Qb6f6", "Qe5b8", "Qf3c6"};
	int queen_expected[5][4] = {
    	{3, 0, 3, 4}, // d1 to d5
    	{7, 0, 4, 3}, // h1 to e4
    	{1, 5, 5, 5}, // b6 to f6
    	{4, 4, 1, 7}, // e5 to b8
    	{5, 2, 2, 5}  // f3 to c6
	};

	for (int i = 0; i < 5; i++)
	{
		result = _parseChessNotation(queen_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, QUEEN_MOVE);
		assert_int_equal(x_i, queen_expected[i][0]);
		assert_int_equal(y_i, queen_expected[i][1]);
		assert_int_equal(x_f, queen_expected[i][2]);
		assert_int_equal(y_f, queen_expected[i][3]);

		result = _parseChessNotation(queen_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, QUEEN_MOVE);
		assert_int_equal(x_i, queen_expected[i][0]);
		assert_int_equal(y_i, queen_expected[i][1]);
		assert_int_equal(x_f, queen_expected[i][2]);
		assert_int_equal(y_f, queen_expected[i][3]);
	}

	/* King Move */
	char * king_moves[5] = {"Ke1d2", "Ke1f2", "Ke1e2", "Ke1f1", "Ke1d1"};
	int king_expected[5][4] = {
	    {4, 0, 3, 1}, // e1 to d2
    	{4, 0, 5, 1}, // e1 to f2
    	{4, 0, 4, 1}, // e1 to e2
    	{4, 0, 5, 0}, // e1 to f1
    	{4, 0, 3, 0}  // e1 to d1
	};

	for (int i = 0; i < 5; i++)
	{
		result = _parseChessNotation(king_moves[i], &x_i, &y_i, &x_f, &y_f, WHITE);
		assert_int_equal(result, KING_MOVE);
		assert_int_equal(x_i, king_expected[i][0]);
		assert_int_equal(y_i, king_expected[i][1]);
		assert_int_equal(x_f, king_expected[i][2]);
		assert_int_equal(y_f, king_expected[i][3]);

		result = _parseChessNotation(king_moves[i], &x_i, &y_i, &x_f, &y_f, BLACK);
		assert_int_equal(result, KING_MOVE);
		assert_int_equal(x_i, king_expected[i][0]);
		assert_int_equal(y_i, king_expected[i][1]);
		assert_int_equal(x_f, king_expected[i][2]);
		assert_int_equal(y_f, king_expected[i][3]);
	}

	/* Long Castle */
	result=_parseChessNotation("0-0-0", &x_i, &y_i, &x_f, &y_f, WHITE);
	assert_int_equal(result, LONG_CASTLE);
	assert_int_equal(x_i, 4);
	assert_int_equal(y_i, 0);
	assert_int_equal(x_f, 2);
	assert_int_equal(y_f, 0);

	result=_parseChessNotation("0-0-0", &x_i, &y_i, &x_f, &y_f, BLACK);
	assert_int_equal(result, LONG_CASTLE);
	assert_int_equal(x_i, 4);
	assert_int_equal(y_i, 7);
	assert_int_equal(x_f, 2);
	assert_int_equal(y_f, 7);

	/* Short Castle */
	result=_parseChessNotation("0-0", &x_i, &y_i, &x_f, &y_f, WHITE);
	assert_int_equal(result, SHORT_CASTLE);
	assert_int_equal(x_i, 4);
	assert_int_equal(y_i, 0);
	assert_int_equal(x_f, 6);
	assert_int_equal(y_f, 0);

	result=_parseChessNotation("0-0", &x_i, &y_i, &x_f, &y_f, BLACK);
	assert_int_equal(result, SHORT_CASTLE);
	assert_int_equal(x_i, 4);
	assert_int_equal(y_i, 7);
	assert_int_equal(x_f, 6);
	assert_int_equal(y_f, 7);
}
