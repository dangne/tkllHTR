/*
 * mlp.h
 *
 *  Created on: Jun 16, 2019
 *      Author: tienanh
 */

#ifndef SRC_MLP_H_
#define SRC_MLP_H_

#include "matrix.h"

// Number of units in each layer
#define UNIT_LAYER_INPUT	784
#define UNIT_LAYER_1		64
#define UNIT_LAYER_OUTPUT	10

Matrix ReLU(Matrix input);
Matrix SoftMax(Matrix input);
int MLP(Matrix input);

#endif /* SRC_MLP_H_ */