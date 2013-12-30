/*
 * Noise.cpp
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#include "Noise.h"
#include <stdlib.h>
#include <time.h>

Noise::Noise() {
	//seed
	srand(time(NULL));
	max = 1.0;
	min = -1.0;
}

Noise::Noise(double min, double max) {
	//seed
	srand(time(NULL));
	this->max = max;
	this->min = min;
}

Noise::~Noise() {
}

void Noise::getOutput(double *signal, int length) {
	for (int i = 0; i < length; i++)
		signal[i] = ((double) rand() / (double) RAND_MAX) * (max - min) + min;
}
