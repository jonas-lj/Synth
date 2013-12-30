//
//  main.cpp
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 11/11/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#include <stdio.h>
#include "Synthesizer.h"
#include "Modules/Mixer.h"
#include "Modules/Envelope.h"
#include "Modules/Constant.h"
#include "Modules/Oscilator.h"
#include "Modules/Noise.h"
#include "Modules/Delay.h"
#include "Modules/MonoController.h"
#include "Misc/FrequencyTable.h"
#include "Modules/Multiplier.h"
#include "Triggers/TriggerMixer.h"

#define BUFFER_SIZE 512

int main(int argc, const char * argv[])
{
	Oscilator* o1 = new Oscilator(BUFFER_SIZE, 440.0, 1.0);
	o1->setWaveform(SQUARE);

	Oscilator* o2 = new Oscilator(BUFFER_SIZE, 440.0, 1.0);
	o2->setWaveform(SINE);

	Envelope* e1 = new Envelope(0.01, 0.2, 0.6, 0.5);
	o1->setAmplitude(e1);
	Envelope* e2 = new Envelope(0.1, 0.5, 1.0, 0.2);
	o2->setAmplitude(e2);

	TriggerMixer *tmix = new TriggerMixer(2);
	tmix->addInput(e1, 0);
	tmix->addInput(e2, 1);

	Controller* c = new MonoController(tmix, 0.0, new FrequencyTable());
	o1->setFrequency(c);

	Multiplier* octaver = new Multiplier(c, 0.5);
	o2->setFrequency(octaver);

	Mixer* mix = new Mixer(BUFFER_SIZE, 2);
	mix->addInput(o1, 0, 0.3);
	mix->addInput(o2, 1, 2.0);

	// Run the synth!
	Synthesizer *s = new Synthesizer(BUFFER_SIZE, mix, c);
    return 0;
}

