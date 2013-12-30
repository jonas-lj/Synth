//
//  Output.h
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 12/24/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#ifndef __Synthesizer__Module__
#define __Synthesizer__Module__

class Module {
    
public:
	virtual ~Module() {}
    virtual void getOutput(double* signal, int length) = 0;

};

#endif /* defined(__Synthesizer__Output__) */
