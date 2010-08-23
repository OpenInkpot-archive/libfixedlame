#define _GNU_SOURCE 1
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "fixedlame.h"
#include "fixedlame_private.h"

fixedlame_t *
fixedlame_init(int sample_rate, int channels, int bitrate)
{
    fixedlame_t *codec = calloc(1, sizeof(fixedlame_t));
    codec->start = true;

//    codec->rec_mono_mode = channels == 1 ? 1 : 0;
    if(channels == 1) {
        channels = 2;
        codec->rec_mono_mode = 1;
    }
    else
        codec->rec_mono_mode = 0;
    codec->num_channels = channels;
    codec->sample_rate = sample_rate;
    codec->bitrate = bitrate;

    fixedlame_enc_init(codec);
    return codec;
}

void
fixedlame_set_write_callback(fixedlame_t *codec, fixedlame_write_callback_t callback, void *userdata)
{
    codec->write_callback = callback;
    codec->write_callback_userdata = userdata;
}

void
fixedlame_set_log_callback(fixedlame_t *codec,
    void (*func)(const char *))
{
    codec->logf = func;
}

void
fixedlame_set_err_callback(fixedlame_t *codec,
    void (*func)(const char *))
{
    codec->errf = func;
}

/*
void
fixedlame_configure_input(fixedlame_t *codec, fixedlame_input_t *input)
{
    // init rest of ci here
} */

void
fixedlame_shutdown(fixedlame_t *codec)
{
    free(codec);
}

int
fixedlame_encode(fixedlame_t *codec, void *src, int size)
{
    return fixedlame_encode_internal(codec, src, size);
}

int
fixedlame_finish(fixedlame_t* codec)
{
    return 0;
}

void
fixedlame_logf(fixedlame_t *self, int flag, const char *fmt, const char *file, int line, ...)
{
   char *str1, *str2;
   va_list ap;
   va_start(ap, line);
   vasprintf(&str1, fmt, ap);
   va_end(ap);
   asprintf(&str2, "mp3: %s:%d -- %s\n", file, line, str1);
   if(flag)
        self->errf(str2);
   else
        self->logf(str2);
   free(str1);
   free(str2);
}
