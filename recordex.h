#ifndef JANUS_RECORDEX_H
#define JANUS_RECORDEX_H
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mutex.h"
#include "refcount.h"

#include "recordexs/recordexhander.h"

gint janus_recordex_recorder_init(GHashTable *handlers);
void janus_recordex_recorder_deinit(void);

janus_recordex_recorder* janus_recordex_recorder_create(
    const gchar *dir,
    const gchar *codec,
    const gchar *format,
    const gchar *filename
);

gint janus_recordex_recorder_open(janus_recordex_recorder *recorder);

gint janus_recordex_recorder_save_frame(
    janus_recordex_recorder *recorder,
    gpointer buffer,
    guint length
);

gint janus_recordex_recorder_close(janus_recordex_recorder *recorder);

void janus_recordex_recorder_destroy(janus_recordex_recorder *recorder);

#endif
