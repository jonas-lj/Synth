//
//  Constant.h
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 12/24/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#include "Module.h"

class Constant : public Module {
    
public:
    Constant(double value);

public:
    // Implements Module
    virtual void getOutput(double* buffer, int length);
  
private:
    double value;
};
