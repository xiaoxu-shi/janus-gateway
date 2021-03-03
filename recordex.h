#ifndef JANUS_RECORDEX_H
#define JANUS_RECORDEX_H
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mutex.h"
#include "refcount.h"

#include "recordexs/recordexhander.h"

int janus_recordex_recorder_init(GHashTable *handlers);
void janus_recordex_recorder_deinit(void);

janus_recordex_recorder* janus_recordex_recorder_create(
    const char *dir,
    const char *codec,
    const char *format,
    const char *filename
);

int janus_recordex_recorder_open(janus_recordex_recorder *recorder);

int janus_recordex_recorder_save_frame(
    janus_recordex_recorder *recorder,
    char *buffer,
    uint length
);

int janus_recordex_recorder_close(janus_recordex_recorder *recorder);

void janus_recordex_recorder_destroy(janus_recordex_recorder *recorder);

#endif
