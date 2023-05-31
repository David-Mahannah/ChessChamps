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
	
	int result = -1;

	board_t b;
	resetBoard(b);
	/*
		** WHITE **
		Nb1c3 -> [1,0]->[2,2] : Valid
		Ng8f6 -> [6,7]->[5,5] : Invalid
		Nb1?? -> [1,0]->[-1,-1] : Invalid (Out of bounds)
		Nb1c3 -> [1,0]->[2,2] : Invalid (Invalid knight move)
		Nb1d2 -> [1,0]->[3,1] : Invalid (Move on top of other)
		Nd4b3 -> [3,3]->[1,2] : Invalid (Piece at x_i, y_i is not a knight) 
		** BLACK **
		Nb1c3 -> [1,0]->[2,2] : Invalid
		Ng8f6 -> [6,7]->[5,5] : Valid
		Nb1?? -> [1,0]->[-1,-1] : Invalid (Out of bounds)
		Nb1c3 -> [1,0]->[2,2] : Invalid (Invalid knight move)
		Nb1d2 -> [1,0]->[3,1] : Invalid (Move on top of other)
		Nd4b3 -> [3,3]->[1,2] : Invalid (Piece at x_i, y_i is not a knight) 


	*/
	/* Knight Move */
	int knight_coordinates[6][4] = {};

	int white_knight_expected_outputs[6] = {};
	int black_knight_expected_outputs[6] = {};
	for (int i = 0; i < 6; i++)
	{
		result = _isValidMove(b, knight_coordinates[i][0],
						knight_coordinates[i][1],
						knight_coordinates[i][2],
						knight_coordinates[i][3],
						KNIGHT_MOVE, WHITE);

		assert_int_equal(result, white_knight_expected_outputs[i]);

		
		result = _isValidMove(b, knight_coordinates[i][0],
						knight_coordinates[i][1],
						knight_coordinates[i][2],
						knight_coordinates[i][3],
						KNIGHT_MOVE, BLACK);

		assert_int_equal(result, black_knight_expected_outputs[i]);
	}
	
	/* Bishop Move */	
	/*
		** WHITE **
		b2b3  -> [1,1]->[1,2] : Valid Pawn move
		Bc1a3 -> [2,0]->[0,2] : Valid bishop
		
		Bc1a3 -> [2,0]->[0,2] : Invalid (Moves through pawn)
		Bc1?? -> [2,0]->[1,-1] : Invalid (bishop move)
		Ba3b4 -> [0,2]->[1,3]  : Invalid (Piece at x_i, y_i is not a knight)
		
		b7b6  -> [1,6]->[1,5] : Valid Pawn move
		Bc8a6 -> [2,7]->[0,5] : Valid bishop
		RESET
		Bc1a3 -> [2,7]->[0,5] : Invalid (Moves through pawn)
		Bc1?? -> [2,0]->[1,-1] : Invalid (bishop move)
		Ba3b4 -> [0,2]->[1,3]  : Invalid (Piece at x_i, y_i is not a knight)
		** BLACK **

	*/

	int bishop_coordinates[10][4] = {};
	int white_bishop_expected_outputs[10] = {};
	int black_bishop_expected_outputs[10] = {};

	board_t black_board;
	board_t white_board;

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 10; i++)
	{
		int move;
		if (i == 0 || i == 5)
		{
			move = PAWN_MOVE;
		} else {
			move = BISHOP_MOVE;
		}

		result = _isValidMove(white_board, bishop_coordinates[i][0],
						bishop_coordinates[i][1],
						bishop_coordinates[i][2],
						bishop_coordinates[i][3],
						move, WHITE);

		if (result == 1)
		{
			_move(white_board, bishop_coordinates[i][0],
					 bishop_coordinates[i][1],
					 bishop_coordinates[i][2],
					 bishop_coordinates[i][3]);
		}

		assert_int_equal(result, white_bishop_expected_outputs[i]);


		result = _isValidMove(black_board, bishop_coordinates[i][0],
						bishop_coordinates[i][1],
						bishop_coordinates[i][2],
						bishop_coordinates[i][3],
						move, BLACK);
		if (result == 1)
		{
			_move(black_board, bishop_coordinates[i][0],
				 			   bishop_coordinates[i][1],
				 			   bishop_coordinates[i][2],
				 			   bishop_coordinates[i][3]);
		}
		assert_int_equal(result, black_bishop_expected_outputs[i]);
	}



	/* Rook Move */	
	int rook_coordinates[10][4] = {};
	int white_rook_expected_outputs[4] = {};
	int black_rook_expected_outputs[4] = {};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 4; i++)
	{
		if (i == 1)
		{
			// Remove A2 pawn
			black_board[6][0] = ' ';
			white_board[6][0] = ' ';
		}

		if (i == 3)
		{
			// Remove H7 pawn
			black_board[1][7] = ' ';
			white_board[1][7] = ' ';
		}

		int move;
		result = _isValidMove(white_board, rook_coordinates[i][0],
						rook_coordinates[i][1],
						rook_coordinates[i][2],
						rook_coordinates[i][3],
						ROOK_MOVE, WHITE);

		assert_int_equal(result, white_rook_expected_outputs[i]);

		result = _isValidMove(black_board, rook_coordinates[i][0],
						rook_coordinates[i][1],
						rook_coordinates[i][2],
						rook_coordinates[i][3],
						ROOK_MOVE, BLACK);

		assert_int_equal(result, black_rook_expected_outputs[i]);
	}

	/* Queen Move */

	int queen_coordinates[20][4] = {};

	int white_queen_expected_outputs[20] = {};
	int black_queen_expected_outputs[20] = {};

	resetBoard(black_board);
	resetBoard(white_board);

	int move;

	for (int i = 0; i < 20; i++)
	{
		move = QUEEN_MOVE;
		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			move = PAWN_MOVE;
		}
	
		if (i == 10)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		result = _isValidMove(white_board, queen_coordinates[i][0],
										   queen_coordinates[i][1],
										   queen_coordinates[i][2],
										   queen_coordinates[i][3],
										   move, WHITE);

		assert_int_equal(result, white_queen_expected_outputs[i]);

		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			_move(white_board, queen_coordinates[i][0],
					 		   queen_coordinates[i][1],
					 		   queen_coordinates[i][2],
					 		   queen_coordinates[i][3]);
		}


		result = _isValidMove(black_board, queen_coordinates[i][0],
										   queen_coordinates[i][1],
										   queen_coordinates[i][2],
										   queen_coordinates[i][3],
										   move, BLACK);

		assert_int_equal(result, black_queen_expected_outputs[i]);
		
		if (i == 2 || i == 7 || i == 12 || i == 17)
		{
			_move(black_board, queen_coordinates[i][0],
					 queen_coordinates[i][1],
					 queen_coordinates[i][2],
					 queen_coordinates[i][3]);
		}
	}

	
	/* King Move */	
	int king_coordinates[8][4] = {};
	int white_king_expected_outputs[8] = {0,0,1,1,0,0,0,0};
	int black_king_expected_outputs[8] = {0,0,0,0,0,0,1,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 8; i++)
	{
		if (i == 2)
		{
			white_board[6][4] = ' ';
		}

		if (i == 4)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 6)
		{
			black_board[1][4] = ' ';
		}

		result = _isValidMove(white_board, king_coordinates[i][0],
						king_coordinates[i][1],
						king_coordinates[i][2],
						king_coordinates[i][3],
						KING_MOVE, WHITE);

		assert_int_equal(result, white_king_expected_outputs[i]);

		result = _isValidMove(black_board, king_coordinates[i][0],
						king_coordinates[i][1],
						king_coordinates[i][2],
						king_coordinates[i][3],
						KING_MOVE, BLACK);

		assert_int_equal(result, black_king_expected_outputs[i]);
	}


	/* Long Castle */
	int long_castle_coordinates[4][4] = {};
	int white_long_castle_expected_outputs[8] = {0,1,0,0};
	int black_long_castle_expected_outputs[8] = {0,0,0,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 4; i++)
	{
		if (i == 1)
		{
			white_board[7][1] = ' ';
			white_board[7][2] = ' ';
			white_board[7][3] = ' ';
		}

		if (i == 2)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 3)
		{
			black_board[0][1] = ' ';
			black_board[0][2] = ' ';
			black_board[0][3] = ' ';
		}

		result = _isValidMove(white_board, long_castle_coordinates[i][0],
						long_castle_coordinates[i][1],
						long_castle_coordinates[i][2],
						long_castle_coordinates[i][3],
						LONG_CASTLE, WHITE);

		assert_int_equal(result, white_long_castle_expected_outputs[i]);

		result = _isValidMove(black_board, long_castle_coordinates[i][0],
						long_castle_coordinates[i][1],
						long_castle_coordinates[i][2],
						long_castle_coordinates[i][3],
						LONG_CASTLE, BLACK);

		assert_int_equal(result, black_long_castle_expected_outputs[i]);
	}

	/* Short Castle */	
	int short_castle_coordinates[4][4] = {};
	int white_short_castle_expected_outputs[8] = {0,1,0,0};
	int black_short_castle_expected_outputs[8] = {0,0,0,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 8; i++)
	{
		if (i == 1)
		{
			white_board[7][5] = ' ';
			white_board[7][6] = ' ';
		}

		if (i == 2)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}

		if (i == 3)
		{
			black_board[0][5] = ' ';
			black_board[0][6] = ' ';
		}

		result = _isValidMove(white_board, short_castle_coordinates[i][0],
						short_castle_coordinates[i][1],
						short_castle_coordinates[i][2],
						short_castle_coordinates[i][3],
						SHORT_CASTLE, WHITE);

		assert_int_equal(result, white_short_castle_expected_outputs[i]);

		result = _isValidMove(black_board, short_castle_coordinates[i][0],
						short_castle_coordinates[i][1],
						short_castle_coordinates[i][2],
						short_castle_coordinates[i][3],
						SHORT_CASTLE, BLACK);

		assert_int_equal(result, black_short_castle_expected_outputs[i]);
	}


	/* Pawn move */
	int pawn_coordinates[12][4] = {};

	int white_pawn_expected_outputs[16] = {1,1,0,0,1,1,0,0,0,0,0,0};
	int black_pawn_expected_outputs[16] = {0,0,0,0,0,0,1,1,0,0,1,1};

	resetBoard(black_board);
	resetBoard(white_board);

	for (int i = 0; i < 16; i++)
	{
		if (i == 6)
		{
			resetBoard(black_board);
			resetBoard(white_board);
		}
		
		result = _isValidMove(white_board, pawn_coordinates[i][0],
						pawn_coordinates[i][1],
						pawn_coordinates[i][2],
						pawn_coordinates[i][3],
						PAWN_MOVE, WHITE);

		assert_int_equal(result, white_pawn_expected_outputs[i]);
		if (result == 1)
		{
			_move(white_board, pawn_coordinates[i][0],
					 pawn_coordinates[i][1],
					 pawn_coordinates[i][2],
					 pawn_coordinates[i][3]);
		}

		result = _isValidMove(black_board, pawn_coordinates[i][0],
						pawn_coordinates[i][1],
						pawn_coordinates[i][2],
						pawn_coordinates[i][3],
						PAWN_MOVE, BLACK);

		assert_int_equal(result, black_pawn_expected_outputs[i]);

		if (result == 1)
		{
			_move(black_board, pawn_coordinates[i][0],
					 pawn_coordinates[i][1],
					 pawn_coordinates[i][2],
					 pawn_coordinates[i][3]);
		}
	}
}
