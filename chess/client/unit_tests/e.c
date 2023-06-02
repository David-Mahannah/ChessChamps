#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../src/chess.h"

char * convertChessNotation(board_t board, char * str)
{
	if (islower(str[0]))
	{
		if (str[1] == 'x')
		{

		}
	} else {
		if (str[0] == 'Q')
		{
			
		} 
		else if (str[0] == 'K')
		{
			
		}
		else if (str[0] == 'B')
		{
			
		}
		else if (str[0] == 'N')
		{
			
		}
		else if (str[0] == 'R')
		{
			
		}
		else if (str[0] == 'Q')
		{
			
		}
	}
}

int main()
{
    FILE* file = fopen("Comedy1Soda_vs_No_Marci_2023.01.13.pgn", "r");
    if (file == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    // Find the start of the moves
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] >= '1' && line[0] <= '9') {
            break;  // We've found the line with the moves
        }
    }

    // Read and print the first line of moves
    char* token = strtok(line, " ");
    while (token != NULL) {
        if (token[0] >= '1' && token[0] <= '9') {
            // Skip the move number
            token = strtok(NULL, " ");
            continue;
        }

        // Print the move
        printf("Move: %s\n", token);

        // Go to the next token
        token = strtok(NULL, " ");
    }

    // Continue reading and printing moves from the remaining lines
    while (fgets(line, sizeof(line), file)) {
        token = strtok(line, " ");
        while (token != NULL) {
            if (token[0] >= '1' && token[0] <= '9') {
                // Skip the move number
                token = strtok(NULL, " ");
                continue;
            }

            // Print the move
            printf("Move: %s\n", token);

            // Go to the next token
            token = strtok(NULL, " ");
        }
    }

    fclose(file);
    return 0;
}
