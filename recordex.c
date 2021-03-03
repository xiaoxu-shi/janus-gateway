#include "recordex.h"

static GHashTable *recordex_handlers = NULL;

void janus_recordex_recorder_init(GHashTable *handlers)
{
    recordex_handlers = handlers;
}

void janus_recordex_recorder_deinit(void)
{
    recordex_handlers = NULL;
}

janus_recordex_recorder* janus_recordex_recorder_create(
    const char *dir,
    const char *codec,
    const char *filename)
{
    return 0;
}

int janus_recordex_recorder_open(janus_recordex_recorder *recorder)
{
    return 0;
}

int janus_recordex_recorder_save_frame(
    janus_recordex_recorder *recorder,
    char *buffer,
    uint length)
{
    return 0;
}

int janus_recordex_recorder_close(janus_recordex_recorder *recorder)
{
    return 0;
}

void janus_recordex_recorder_destroy(janus_recordex_recorder *recorder)
{

}
