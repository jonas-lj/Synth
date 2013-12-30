#include "Synthesizer.h"

#define FPS 44100
#define SCALE 10000

Synthesizer::Synthesizer(int buffer_size, Module* source, Controller* controller) {
    rate = FPS;

    this->source = source;
    this->buffer_size = buffer_size;

    this->controller = controller;

    // The number of samples per second
    rate = FPS;
    
    out_buffer = (short *) malloc(2 * sizeof(short) * buffer_size);
    bzero(out_buffer, 2 * sizeof(short) * buffer_size);

    buffer = (double *) malloc(sizeof(double)*buffer_size);
    bzero(buffer, sizeof(double)*buffer_size);

    playback_handle = openPcm("hw:0");
    sequencer = openSequencer();
    int seq_nfds = snd_seq_poll_descriptors_count(sequencer, POLLIN);
    int nfds = snd_pcm_poll_descriptors_count(playback_handle);
    struct pollfd *pfds = (struct pollfd *) alloca(sizeof(struct pollfd) * (seq_nfds + nfds));
    snd_seq_poll_descriptors(sequencer, pfds, seq_nfds, POLLIN);
    snd_pcm_poll_descriptors(playback_handle, pfds + seq_nfds, nfds);

    printf("Synth ready - enjoy!\n");

    synthLoop(seq_nfds, nfds, pfds);

}

Synthesizer::~Synthesizer() {
    snd_pcm_close(playback_handle);
    snd_seq_close(sequencer);

    free(out_buffer);
	free(buffer);
}

void Synthesizer::synthLoop(int seq_nfds, int nfds, struct pollfd *pfds) {
	int i;
    while (1) {
        if (poll(pfds, seq_nfds + nfds, 1000) > 0) {
            for (i = 0; i < seq_nfds; i++)
                if (pfds[i].revents > 0)
                    midiCallback();

            for (i = seq_nfds; i < seq_nfds + nfds; i++) {
                if (pfds[i].revents > 0) {
                    if (playbackCallback(buffer_size) < buffer_size) {
                        fprintf(stderr, "Error: xrun\n");
                        snd_pcm_prepare(playback_handle);
                    }
                }
            }
        }
    }
}

snd_seq_t *Synthesizer::openSequencer() {
    snd_seq_t * seq_handle;

    if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_DUPLEX, 0) < 0) {
        fprintf(stderr, "Error opening ALSA sequencer.\n");
        exit(1);
    }
    snd_seq_set_client_name(seq_handle, "8bitSynth");
    if (snd_seq_create_simple_port(seq_handle, "8bitSynth", SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
                                   SND_SEQ_PORT_TYPE_APPLICATION) < 0) {
        fprintf(stderr, "Error creating sequencer port.\n");
        exit(1);
    }
    return (seq_handle);
}

snd_pcm_t *Synthesizer::openPcm(char *pcm_name)
{
  snd_pcm_t * playback_handle;
  snd_pcm_hw_params_t *hw_params;
  snd_pcm_sw_params_t *sw_params;

  if (snd_pcm_open(&playback_handle, pcm_name, SND_PCM_STREAM_PLAYBACK, 0) < 0) {
    fprintf(stderr, "Error: Cannot open audio device %s\n", pcm_name);
    exit(1);
  }
  snd_pcm_hw_params_alloca(&hw_params);
  snd_pcm_hw_params_any(playback_handle, hw_params);
  snd_pcm_hw_params_set_access(playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED);
  snd_pcm_hw_params_set_format(playback_handle, hw_params, SND_PCM_FORMAT_S16_LE);
  snd_pcm_hw_params_set_rate_near(playback_handle, hw_params, &rate, 0);
  snd_pcm_hw_params_set_channels(playback_handle, hw_params, 2);
  snd_pcm_hw_params_set_periods(playback_handle, hw_params, 2, 0);
  snd_pcm_hw_params_set_period_size(playback_handle, hw_params, buffer_size, 0);
  snd_pcm_hw_params(playback_handle, hw_params);
  snd_pcm_sw_params_alloca(&sw_params);
  snd_pcm_sw_params_current(playback_handle, sw_params);
  snd_pcm_sw_params_set_avail_min(playback_handle, sw_params, buffer_size);
  snd_pcm_sw_params(playback_handle, sw_params);
  return (playback_handle);
}

void Synthesizer::setSource(Module *o) {
	source = o;
}

int Synthesizer::playbackCallback(snd_pcm_sframes_t nframes) {
	if (!source)
		return nframes;

	source->getOutput(buffer, nframes);

	for (int i = 0; i < nframes; i++) {
		out_buffer[2*i] = buffer[i] * SCALE;
		out_buffer[2*i+1] = buffer[i] * SCALE;
	}
	return snd_pcm_writei(playback_handle, out_buffer, nframes);
}

int Synthesizer::midiCallback() {
	snd_seq_event_t *ev;

	do {
		snd_seq_event_input(sequencer, &ev);

		switch (ev->type) {

		case SND_SEQ_EVENT_PITCHBEND:
			break;

		case SND_SEQ_EVENT_CONTROLLER:
			//	      if (ev->data.control.param == 1)
			//		modulation = (double) ev->data.control.value / 128.0;
			//	      if (ev->data.control.param == 2) //cutoff currently not working
			//		cutoff = (double) ev->data.control.value / 128.0;
			//	      if (ev->data.control.param == 64) {
			//		if (ev->data.control.value == 127) {
			//		  //tap pressed
			//		}
			//	      }
			break;

		case SND_SEQ_EVENT_NOTEON:
			controller->noteOn(ev->data.note.note);
			break;

		case SND_SEQ_EVENT_NOTEOFF:
			controller->noteOff(ev->data.note.note);
			break;

		}
		snd_seq_free_event(ev);
	} while (snd_seq_event_input_pending(sequencer, 0) > 0);
	return 0;
}


