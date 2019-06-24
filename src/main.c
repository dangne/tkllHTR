/*
 * main.c
 *
 *  Created on: Jun 16, 2019
 *      Author: dangn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "xil_printf.h"
#include "sleep.h"
#include "mlp.h"
#include "matrix.h"

#define INPUT_SIZE			784
#define BUFFER_SIZE 		(INPUT_SIZE*3 + INPUT_SIZE)
#define IDLE_STATE 			1
#define EXECUTION_STATE 	2
#define RESULT_STATE 		3

int main(){
	char buffer[BUFFER_SIZE];
	int state = IDLE_STATE;
	int result = -1;
    double input[1][INPUT_SIZE];
    char* token;

	while (1) {
		switch (state) {
			case IDLE_STATE:
				gets(buffer);
				state = EXECUTION_STATE;
				break;
				
			case EXECUTION_STATE:
				token = strtok(buffer, ",");
				int i = 0;
				while (token != NULL){
					input[0][i] = 0;
					for (int j = 0 ; j < strlen(token) ; ++j)
						input[0][i] = input[0][i]*10 + token[j] - '0';
					token = strtok(NULL, ",");
					i++;
				}

				// Normalize input to 0-1
				for (int i = 0 ; i < INPUT_SIZE ; ++i)
					input[0][i] /= 255.0;

				xil_printf("Begin MLP\n");
				MLP(input);
				xil_printf("End MLP\n");
				state = RESULT_STATE;
				break;

			case RESULT_STATE:
				xil_printf("Result: %d\n", result);
				state = IDLE_STATE;
				break;

			default:
				state = IDLE_STATE;
				break;
		}
	}
	return 0;
}