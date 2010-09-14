#include <stdio.h>
#include <stdarg.h>
#include <sox.h>
#include "fixedlame.h"
#include "sox_mp3_plugin.h"

#define MP3_LAME_PRECISION 24


static size_t
_fixedlame_write_callback(void *userdata, void *buf, size_t size)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) userdata;
    size_t rc = fwrite(buf, size, 1, self->file);
    //fflush(self->file);
    //fprintf(stderr, "written %d bytes\n", size);
    return rc;
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
    self->file = fopen(ft->filename, "wb");
    if(!self->file)
    {
        return SOX_EOF;
    }
    int channels;
    if (ft->signal.channels == SOX_ENCODING_UNKNOWN) {
        channels = 1;
        ft->signal.channels = 1;
    } else
        channels = ft->signal.channels;
    int bitrate = 128;
    self->codec = fixedlame_init(ft->signal.rate, channels, bitrate);
    ft->signal.precision = MP3_LAME_PRECISION;
    fixedlame_set_err_callback(self->codec, _fixedlame_errf);
    fixedlame_set_log_callback(self->codec, _fixedlame_logf);
    fixedlame_set_write_callback(self->codec, _fixedlame_write_callback, self);
    return SOX_SUCCESS;
}

static int
mp3_stop_write(sox_format_t * ft)
{
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) ft->priv;
    fclose(self->file);
    fixedlame_shutdown(self->codec);
    return SOX_SUCCESS;
}

static size_t
mp3_write(sox_format_t * ft, const sox_sample_t *buf, size_t samp)
{
    int nsamples = samp/ft->signal.channels;
    int bufsize = nsamples * 4; /* backend accept "forced" stereo of 16bit */
    uint16_t *buffer = malloc(bufsize);
    int clips = 0;
    int idx = 0;
    int c = 0;
    int rc;
    SOX_SAMPLE_LOCALS;

    fprintf(stderr, "Create preprocess buffer: %d\n", bufsize);
    if(!buffer)
        return 0;

    if(ft->signal.channels == 1)
    {
        /* mono */
        for(c = 0; c < samp; c++)
        {
            /* left channel */
            buffer[idx++] = SOX_SAMPLE_TO_SIGNED_16BIT(buf[c], clips);

            /* right channel */
            buffer[idx++] = 0;
        }
    }
    else
    {
        /* stereo:  we can ignore special meaning of right channel */
        for(idx = 0; idx < samp; idx++)
        {
           buffer[idx] = SOX_SAMPLE_TO_SIGNED_16BIT(buf[idx], clips);
        }
    }
    sox_fixedpoint_mp3_t *self = (sox_fixedpoint_mp3_t *) ft->priv;
    rc = fixedlame_encode(self->codec, (void *)buffer, samp);
    free(buffer);
    return rc;
}

const sox_format_handler_t *
lsx_fixedpoint_mp3_format_fn()
{
    static char const * const names[] = { "mp3", "fmp3", "fixedpoint_mp3", NULL };
    static unsigned const write_encodings[] = {
        SOX_ENCODING_MP3, 0, 0,
    };
    static sox_format_handler_t const handler = {
        .sox_lib_version_code = SOX_LIB_VERSION_CODE,
        .description = "MPEG Layer 3 audio compression (fixedpoint version)",
        .names = names,
        .flags = SOX_FILE_NOSTDIO | SOX_FILE_MONO,
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
