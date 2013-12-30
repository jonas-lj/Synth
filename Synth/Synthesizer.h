//
//  Synthesizer.h
//  Synthesizer
//
//  Created by Jonas Lindstrøm Jensen on 11/11/13.
//  Copyright (c) 2013 Jonas Lindstrøm Jensen. All rights reserved.
//

#ifndef Synthesizer_Synthesizer_h
#define Synthesizer_Synthesizer_h

#include <alsa/asoundlib.h>
#include "Modules/Module.h"
#include "Modules/Controller.h"

class Synthesizer {

public:
    Synthesizer(int buffer_size, Module* source, Controller* controller);
    ~Synthesizer();

public:
    void setSource(Module* o);
    
private:
    int midiCallback();
    int playbackCallback(snd_pcm_sframes_t nframes);
    void synthLoop(int seq_nfds, int nfds, struct pollfd *pfds);
    
private:
    snd_seq_t *openSequencer();
    snd_pcm_t *openPcm(char *pcm_name);

private:
    unsigned int rate;
    int buffer_size;
    double* buffer;
    short* out_buffer;
    snd_pcm_t* playback_handle;
    snd_seq_t* sequencer;
    Module *source;
    Controller *controller;
    
};

#endif
