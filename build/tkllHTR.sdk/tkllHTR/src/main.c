#include <stdlib.h>
#include "xil_printf.h"
#include "xuartps.h"
#include "xparameters.h"
#include "sleep.h"
#include "mlp.h"
#include "matrix.h"

#define INPUT_SIZE			2
#define BUFFER_SIZE 		(INPUT_SIZE + 1)	// +1 for '\0' character
#define IDLE_STATE 			1
#define EXECUTION_STATE 	2
#define RESULT_STATE 		3

XUartPs Uart; // Instance of the UART Device

static u8 SendBuffer[BUFFER_SIZE];	// Buffer for Sending Data
static u8 RecvBuffer[BUFFER_SIZE];	// Buffer for Receiving Data

int main(){
	int state = IDLE_STATE;
	int result = -1;
	Matrix input = new_matrix(1, 784);
	// Lookup configuration for the UART
	XUartPs_Config* Config = XUartPs_LookupConfig(XPAR_XUARTPS_0_DEVICE_ID);

	// Initialize UART with the above configuration
	XUartPs_CfgInitialize(&Uart, Config, Config->BaseAddress);

	// Set receive timeout to detect an idle connection
	XUartPs_SetRecvTimeout(&Uart, 8);

	// Initialize send and receive buffer
	memset(SendBuffer, 0, BUFFER_SIZE);
	memset(RecvBuffer, 0, BUFFER_SIZE);

	while (1) {
		switch (state) {
			case IDLE_STATE:
				// Wait until there is incoming data
				while (!XUartPs_IsReceiveData(XPAR_XUARTPS_0_BASEADDR));

				// Short delay to ensure the UART receive properly
				usleep(500);

				// Receive data from UART
				XUartPs_Recv(&Uart, RecvBuffer, BUFFER_SIZE);

				// Transfer RecvBuffer to input matrix
				for (int i = 0 ; i < BUFFER_SIZE ; ++i)
					input.at[0][i] = RecvBuffer[i];

				// Clear buffer
				memset(RecvBuffer, 0, BUFFER_SIZE);
				state = EXECUTION_STATE;
				break;

			case EXECUTION_STATE:
				//result = MLP(input);
				result = input.at[0][0];
				state = RESULT_STATE;
				break;

			case RESULT_STATE:
				SendBuffer[0] = result;
				XUartPs_Send(&Uart, SendBuffer, BUFFER_SIZE);
				state = IDLE_STATE;
				break;
		}
	}
	return 0;
}
