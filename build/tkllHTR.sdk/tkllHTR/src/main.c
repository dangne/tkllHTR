#include <stdio.h>
#include <stdlib.h>
#include "xil_printf.h"
#include "sleep.h"
#include "mlp.h"
#include "matrix.h"

#define INPUT_SIZE			10
#define BUFFER_SIZE 		(INPUT_SIZE*3 + INPUT_SIZE)
#define IDLE_STATE 			1
#define EXECUTION_STATE 	2
#define RESULT_STATE 		3

int main(){
	char buffer[BUFFER_SIZE];
	char* token;
	int state = IDLE_STATE;
	int result = -1;
	int cnt;
	Matrix input = new_matrix(1, INPUT_SIZE);

	while (1) {
		switch (state) {
			case IDLE_STATE:
				gets(buffer);
				xil_printf("Input: %s\n",buffer);
				state = EXECUTION_STATE;
				break;
				
			case EXECUTION_STATE:
				token = strtok(buffer, ",\n");
				int i = 0;
				cnt = 0;
				while (token != NULL){
					cnt++;
					input.at[0][i] = 0;
					for (int j = 0 ; j < strlen(token) ; ++j)
						input.at[0][i] = input.at[0][i]*10 + token[j] - '0';
					token = strtok(NULL, ",\n");
					i++;
				}
				/*
				// Normalize input to 0-1
				for (int i = 0 ; i < INPUT_SIZE ; ++i)
					input.at[0][i] /= 255.0;
				*/
				//result = MLP(input);
				state = RESULT_STATE;
				break;

			case RESULT_STATE:
				xil_printf("Number of numbers: %d\n", cnt);
				xil_printf("Output: ");
				for (int i = 0 ; i < cnt ; ++i){
					if (i != 0) xil_printf(",");
					xil_printf("%d", (int)input.at[0][i]);
				}
				xil_printf("\n");
				state = IDLE_STATE;
				break;

			default:
				state = IDLE_STATE;
				break;
		}
	}
	return 0;
}