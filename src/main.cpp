#include <lv2/core/lv2.h>
#include <stdlib.h>
#include <cmath>
#include <algorithm>

enum {
    PORT_INPUT  = 0,
    PORT_OUTPUT = 1,
    PORT_DRY    = 2,
    PORT_WET    = 3,
    PORT_TONE   = 4
};

class MyOctavePedal {
public:
    const float* input;
    float* output;
    const float* dry_lev;
    const float* wet_lev;
    const float* tone_val;

    float in_lpf_state;
    float out_lpf_state;
    float sample_rate;

    float last_sample;
    int state;
    int flip_flop;

    MyOctavePedal(double rate) :
    in_lpf_state(0.0f), out_lpf_state(0.0f),
    sample_rate((float)rate), last_sample(0.0f),
    state(1), flip_flop(0) {}
};

static LV2_Handle instantiate(const LV2_Descriptor* descriptor, double rate, const char* bundle_path, const LV2_Feature* const* features) {
    return new MyOctavePedal(rate);
}

static void connect_port(LV2_Handle instance, uint32_t port, void* data) {
    MyOctavePedal* self = (MyOctavePedal*)instance;
    switch (port) {
        case PORT_INPUT:  self->input = (const float*)data; break;
        case PORT_OUTPUT: self->output = (float*)data; break;
        case PORT_DRY:    self->dry_lev = (const float*)data; break;
        case PORT_WET:    self->wet_lev = (const float*)data; break;
        case PORT_TONE:   self->tone_val = (const float*)data; break;
    }
}

static void run(LV2_Handle instance, uint32_t n_samples) {
    MyOctavePedal* self = (MyOctavePedal*)instance;

    float dry_vol = *self->dry_lev;
    float wet_vol = *self->wet_lev;
    float tone_freq = *self->tone_val;

    float in_alpha = (2.0f * 3.14159265f * 150.0f) / self->sample_rate;
    float out_alpha = (2.0f * 3.14159265f * tone_freq) / self->sample_rate;

    for (uint32_t i = 0; i < n_samples; ++i) {
        float in = self->input[i];

        self->in_lpf_state += in_alpha * (in - self->in_lpf_state);
        float analysis_sig = self->in_lpf_state;

        if (self->last_sample <= 0.0f && analysis_sig > 0.0f) {
            self->flip_flop++;
            if (self->flip_flop >= 2) {
                self->state *= -1;
                self->flip_flop = 0;
            }
        }
        self->last_sample = analysis_sig;

        float oct_raw = (float)self->state * std::abs(in);

        self->out_lpf_state += out_alpha * (oct_raw - self->out_lpf_state);
        float oct_smooth = self->out_lpf_state;

        self->output[i] = (in * dry_vol) + (oct_smooth * wet_vol);
    }
}

static void cleanup(LV2_Handle instance) {
    delete (MyOctavePedal*)instance;
}

static const LV2_Descriptor descriptor = {
    "https://example.org/SubOctaveForBass",
    instantiate,
    connect_port,
    nullptr,
    run,
    nullptr,
    cleanup,
    nullptr
};

extern "C" LV2_SYMBOL_EXPORT const LV2_Descriptor* lv2_descriptor(uint32_t index) {
    return (index == 0) ? &descriptor : nullptr;
}
