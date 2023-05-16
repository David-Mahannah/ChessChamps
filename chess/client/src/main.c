#include "chess.h"
#include <string.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
	board_t board;
	resetBoard(board);

	char input[100];

	if (argc < 3)
	{
		printf("Usage: ./chess <server_ip> <server_port>\n");
	}

	int check_status;
	while (1)
	{
		printBoard(board, WHITE);
		printf(">");
		fgets(input, 100, stdin); 

		if (strncmp(input, "quit", 4) == 0)
		{
			break;
		} else {
			move(board, input, &check_status, WHITE);
		}
	}

	//move(board,"Ng1-f3"); 

	//printBoard(board);

	//move(board,"Ni3-h3");
	
	//printBoard(board);
}
