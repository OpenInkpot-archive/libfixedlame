#ifndef FIXEDLAME_PRIVATE_H
#define FIXEDLAME_PRIVATE_H 1

#include <stdbool.h>

#define LOGF(codec, format, ...)  fixedlame_logf(codec, 0, format, __FILE__, __LINE__, __VA_ARGS__)
#define ERRF(codec, format, ...)  fixedlame_logf(codec, 1, format, __FILE__, __LINE__, __VA_ARGS__)


struct fixedlame_t {
    void (*logf)(const char *);
    void (*errf)(const char *);
    fixedlame_write_callback_t write_callback;
    void * write_callback_userdata;
    bool start;
    unsigned long num_pcm;
    int sample_rate;
    int num_channels;
    int bitrate;
    int rec_mono_mode;
};

void
fixedlame_logf(fixedlame_t *self, int flag, const char *fmt, const char *file, int line, ...);

size_t
fixedlame_encode_internal(fixedlame_t *fl, void *samples, int n_samps);

bool fixedlame_enc_init(fixedlame_t *fl);
#endif
