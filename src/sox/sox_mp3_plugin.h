#ifndef _SOX_MP3_PLUGIN_H
#define _SOX_MP3_PLUGIN_H

#include <stdio.h>
#include <fixedlame.h>

typedef struct sox_fixedpoint_mp3_t sox_fixedpoint_mp3_t;
struct sox_fixedpoint_mp3_t {
    fixedlame_t *codec;
    FILE *file;
};

#endif
