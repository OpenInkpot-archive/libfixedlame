#ifndef FIXEDLAME_H
#define FIXEDLAME_H 1

typedef struct fixedlame_t fixedlame_t;

typedef size_t (*fixedlame_write_callback_t)(void *userdata, void *buf,
                    size_t size);

fixedlame_t *
fixedlame_init(int sample_rate, int channels, int bitrate);

void
fixedlame_set_log_callback(fixedlame_t *, void (*func)(const char *));

void
fixedlame_set_err_callback(fixedlame_t *, void (*func)(const char *));

void
fixedlame_set_write_callback(fixedlame_t *, fixedlame_write_callback_t, void*);

void
fixedlame_shutdown(fixedlame_t *);

void
fixedlame_flush(fixedlame_t *);


int
fixedlame_encode(fixedlame_t *, void *, int);

#endif
