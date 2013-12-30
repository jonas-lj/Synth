/*
 * FrequencyMultiplier.h
 *
 *  Created on: Dec 30, 2013
 *      Author: jonas
 */

#ifndef FREQUENCYMULTIPLIER_H_
#define FREQUENCYMULTIPLIER_H_

#include "Module.h"

class Multiplier : public Module {
public:
	Multiplier(Module *input, double multiplier);
	virtual ~Multiplier();

public:
	virtual void getOutput(double *signal, int length);

private:
	Module *input;
	double multiplier;
};

#endif /* FREQUENCYMULTIPLIER_H_ */
