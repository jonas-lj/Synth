/*
 * Noise.h
 *
 *  Created on: Dec 29, 2013
 *      Author: jonas
 */

#ifndef NOISE_H_
#define NOISE_H_

#include "Module.h"

class Noise: public Module {
public:
	Noise();
	Noise(double min, double max);
	virtual ~Noise();

public:
	virtual void getOutput(double *signal, int length);

private:
	double min, max;
};

#endif /* NOISE_H_ */
