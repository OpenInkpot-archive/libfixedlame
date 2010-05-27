#ifndef FIXEDLAME_PRIVATE_H
#define FIXEDLAME_PRIVATE_H 1

#define LOGF(codec, format, ...)  fixedlame_logf(codec, 0, format, __FILE__, __LINE__, __VA_ARGS__)
#define ERRF(codec, format, ...)  fixedlame_logf(codec, 1, format, __FILE__, __LINE__, __VA_ARGS__)


struct fixedlame_t {
    void (*logf)(const char *);
    void (*errf)(const char *);
    fixedlame_write_callback_t write_callback;
    void * write_callback_userdata;
};

void
fixedlame_logf(fixedlame_t *self, int flag, const char *fmt, const char *file, int line, ...);

#endif
