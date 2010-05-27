#define _GNU_SOURCE 1
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "fixedlame.h"
#include "fixedlame_private.h"

fixedlame_t *
fixedlame_init()
{
    fixedlame_t *codec = calloc(1, sizeof(fixedlame_t));

    /* currently ci is static, but it can change later */
//    codec->ci = fixedlame_private_init_ci();
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
    /* encode here */
    return 0;
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
