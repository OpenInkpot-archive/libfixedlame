#include <stdio.h>
#include <stdarg.h>
#include <sox.h>
#include "fixedlame.h"
#include "sox_mp3_plugin.h"

static size_t
_fixedlame_write_callback(void *userdata, void *buf, size_t size)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) userdata;
    return fwrite(buf, size, 1, self->file);
}

static void
_fixedlame_logf(const char *msg)
{
    lsx_warn(msg);
}

static void
_fixedlame_errf(const char *msg)
{
    lsx_fail(msg);
}

static int
mp3_start_write(sox_format_t * ft)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) ft->priv;
    self->codec = fixedlame_init();
    fixedlame_set_err_callback(self->codec, _fixedlame_errf);
    fixedlame_set_log_callback(self->codec, _fixedlame_logf);
    fixedlame_set_write_callback(self->codec, _fixedlame_write_callback, self);
    self->file = fopen(ft->filename, "wb");
    if(!self->file)
    {
        return SOX_EOF;
    }
    return SOX_SUCCESS;
}

static int
mp3_stop_write(sox_format_t * ft)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) ft->priv;
    fixedlame_flush(self->codec);
    fixedlame_shutdown(self->codec);
    fclose(self->file);
    return SOX_SUCCESS;
}

static size_t
mp3_write(sox_format_t * ft, const sox_sample_t *buf, size_t samp)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) ft->priv;
    fixedlame_encode(self->codec, buf, samp);
    return 0;
}

const sox_format_handler_t *
lsx_fixedpoint_mp3_format_fn()
{
    static char const * const names[] = { "fixedpoint_mp3", NULL };
    static unsigned const write_encodings[] = {
        SOX_ENCODING_MP3, 0, 0,
    };
    static sox_format_handler_t const handler = {
        .sox_lib_version_code = SOX_LIB_VERSION_CODE,
        .description = "MPEG Layer 3 audio compression (fixedpoint version)",
        .names = names,
        .flags = SOX_FILE_NOSTDIO,
        .startread = NULL,
        .read = NULL,
        .stopread = NULL,
        .startwrite = mp3_start_write,
        .write = mp3_write,
        .stopwrite = mp3_stop_write,
        .write_formats = write_encodings,
        .write_rates = NULL,
        .priv_size = sizeof(sox_fixedpoint_mp3_t)

    };
    return &handler;
}
