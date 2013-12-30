/*
 * FrequencyTable.cpp
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#include "FrequencyTable.h"
#include <math.h>

#define NOTES 88

FrequencyTable::FrequencyTable() {
	frequencies = new double[NOTES];
	for (int i = 0; i < 88; i++)
		frequencies[i] = pow(2.0, (i-45.0)/12.0) * 440.0;
}

FrequencyTable::~FrequencyTable() {
	delete[] frequencies;
}

double FrequencyTable::getFrequency(int note) {
	return frequencies[note];
}
