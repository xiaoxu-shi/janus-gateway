#include <glob.h>

#include "recordex.h"

static GHashTable *recordex_handlers = NULL;

static gboolean recordex_handler_compare_by_format(gpointer key, gpointer value, gpointer data) {
    gboolean result = FALSE;
    janus_recordex_hander *handler = (janus_recordex_hander*)value;
    const gchar *s1 = (const gchar*)data;
    const gchar *s2 = handler->get_format();
    if (strcasecmp(s1, s2) == 0) {
        result = TRUE;
    }
    return result;
}

gint janus_recordex_recorder_init(GHashTable *handlers)
{
    recordex_handlers = handlers;
    return 0;
}

void janus_recordex_recorder_deinit(void)
{
    recordex_handlers = NULL;
}

janus_recordex_recorder* janus_recordex_recorder_create(
    const gchar *dir,
    const gchar *codec,
    const gchar *format,
    const gchar *filename)
{
    janus_recordex_hander* handler = NULL;
    janus_recordex_recorder* recorder = NULL;
    if ( dir == NULL || codec == NULL || format == NULL|| filename == NULL ) {
        JANUS_LOG(LOG_ERR, "Couldn't create recordex recorder, params wrong... !\n");
        return recorder;
    }

    if (g_hash_table_size(recordex_handlers) == 0) {
        JANUS_LOG(LOG_ERR, "Couldn't create recordex recorder, hashtable is empty... !\n");
        return recorder;
    }

    handler = g_hash_table_find(recordex_handlers, recordex_handler_compare_by_format, (gpointer)format);
    if (!handler) {
        JANUS_LOG(LOG_ERR, "Couldn't create recordex recorder, format <%s> handler not registered... !\n", format);
        return recorder;
    }

    recorder = handler->rex_create(handler, dir, codec, format, filename);

    return recorder;
}

gint janus_recordex_recorder_open(janus_recordex_recorder *recorder)
{
    return 0;
}

gint janus_recordex_recorder_save_frame(
    janus_recordex_recorder *recorder,
    gpointer buffer,
    guint length)
{
    return 0;
}

gint janus_recordex_recorder_close(janus_recordex_recorder *recorder)
{
    return 0;
}

void janus_recordex_recorder_destroy(janus_recordex_recorder *recorder)
{

}
