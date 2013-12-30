//
//  Constant.cpp
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 12/24/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#include "Constant.h"
#include <stdlib.h>
#include <string.h>

Constant::Constant(double value) {
    this->value = value;
}

void Constant::getOutput(double *signal, int length) {
	for (int i = 0; i < length; i++)
		signal[i] = value;
}
