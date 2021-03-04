#include "recordexhander.h"
#include "recordex_uilts.h"

#define JANUS_RECORDEX_OPUS_VERSION			1
#define JANUS_RECORDEX_OPUS_VERSION_STRING 	"0.0.1"
#define JANUS_RECORDEX_OPUS_DESCRIPTION 	"This is recorder handler plugin for Janus, which recording opus file."
#define JANUS_RECORDEX_OPUS_NAME 		    "Janus recordex opus plugin"
#define JANUS_RECORDEX_OPUS_AUTHOR 			"xiaoxu.shi <xaoxu_shi@yeah.net>"
#define JANUS_RECORDEX_OPUS_PACKAGE			"janus.recordex.opus"
#define JANUS_RECORDEX_OPUS_FORMAT			"opus"

static gint s_initialized = 0;

janus_recordex_hander* create(void);
gint  janus_recordex_opus_init(const char *config_path);
void janus_recordex_opus_destroy(void);
gint  janus_recordex_opus_get_api_compatibility(void);
gint  janus_recordex_opus_get_version(void);
const gchar *janus_recordex_opus_get_version_string(void);
const gchar *janus_recordex_opus_get_description(void);
const gchar *janus_recordex_opus_get_name(void);
const gchar *janus_recordex_opus_get_author(void);
const gchar *janus_recordex_opus_get_package(void);
const gchar *janus_recordex_opus_get_format(void);

janus_recordex_recorder* janus_recordex_opus_rex_create(janus_recordex_hander *handler, const gchar *dir, const gchar *codec, const gchar *format, const gchar *filename);
void janus_recordex_opus_rex_destory(janus_recordex_recorder* recorder);
gint  janus_recordex_opus_rex_open(janus_recordex_recorder* recorder);
void janus_recordex_opus_rex_close(janus_recordex_recorder* recorder);
gint  janus_recordex_opus_rex_process(janus_recordex_recorder* recorder, gpointer buffer, guint length);

static gpointer janus_recordex_opus_expand_malloc(void);
static void janus_recordex_opus_expand_free(gpointer expand);

janus_recordex_hander janus_recordex_opus_hander =
    JANUS_RECORDEX_HANDER_INIT(
        .init = janus_recordex_opus_init,
        .destroy = janus_recordex_opus_destroy,
        .get_api_compatibility = janus_recordex_opus_get_api_compatibility,
        .get_version = janus_recordex_opus_get_version,
        .get_version_string = janus_recordex_opus_get_version_string,
        .get_description = janus_recordex_opus_get_description,
        .get_format = janus_recordex_opus_get_format,
        .get_name = janus_recordex_opus_get_name,
        .get_author = janus_recordex_opus_get_author,
        .get_package = janus_recordex_opus_get_package,
        .rex_create = janus_recordex_opus_rex_create,
        .rex_destory = janus_recordex_opus_rex_destory,
        .rex_open = janus_recordex_opus_rex_open,
        .rex_close = janus_recordex_opus_rex_close,
        .rex_process = janus_recordex_opus_rex_process,
    );

janus_recordex_hander* create(void) {
    JANUS_LOG(LOG_VERB, "%s created!\n", JANUS_RECORDEX_OPUS_NAME);
    return &janus_recordex_opus_hander;
}


gint janus_recordex_opus_init(const gchar *config_path) {
    JANUS_LOG(LOG_VERB, "%s inited!\n", JANUS_RECORDEX_OPUS_NAME);
    g_atomic_int_set(&s_initialized, 1);
    return 0;
}

void janus_recordex_opus_destroy(void) {
    JANUS_LOG(LOG_VERB, "%s destroyed!\n", JANUS_RECORDEX_OPUS_NAME);
}

gint janus_recordex_opus_get_api_compatibility(void) {
    return JANUS_RECORDEXHANDER_API_VERSION;
}

gint janus_recordex_opus_get_version(void) {
    return JANUS_RECORDEX_OPUS_VERSION;
}

const gchar *janus_recordex_opus_get_version_string(void) {
    return JANUS_RECORDEX_OPUS_VERSION_STRING;
}

const gchar *janus_recordex_opus_get_description(void) {
    return JANUS_RECORDEX_OPUS_DESCRIPTION;
}

const gchar *janus_recordex_opus_get_name(void) {
    return JANUS_RECORDEX_OPUS_NAME;
}

const gchar *janus_recordex_opus_get_author(void) {
    return JANUS_RECORDEX_OPUS_AUTHOR;
}

const gchar *janus_recordex_opus_get_package(void) {
    return JANUS_RECORDEX_OPUS_PACKAGE;
}

const gchar *janus_recordex_opus_get_format(void) {
    return JANUS_RECORDEX_OPUS_FORMAT;
}

janus_recordex_recorder* janus_recordex_opus_rex_create(janus_recordex_hander *handler, const gchar *dir, const gchar *codec, const gchar *format, const gchar *filename) {
    janus_recordex_recorder *recorder = NULL;
    janus_recordex_medium rec_type = JANUS_RECORDEX_UNKNOWN;

    if (!g_atomic_int_get(&s_initialized)) {
        JANUS_LOG(LOG_ERR, "%s Couldn't create recorder, not initialized...! \n", JANUS_RECORDEX_OPUS_NAME);
        return recorder;
    }

    if (strcasecmp(codec, janus_recordex_opus_get_format()) != 0) {
        JANUS_LOG(LOG_ERR, "%s Couldn't create recorder, format mismatch...! \n", JANUS_RECORDEX_OPUS_NAME);
        return recorder;
    }

    rec_type = get_media_type(codec);
    if (rec_type == JANUS_RECORDEX_UNKNOWN) {
        JANUS_LOG(LOG_ERR, "%s Unsupported codec '%s'\n", JANUS_RECORDEX_OPUS_NAME, codec);
        return recorder;
    }

    if (create_if_dir_not_exist(dir)) {
        JANUS_LOG(LOG_ERR, "%s Couldn't create directory '%s'\n", JANUS_RECORDEX_OPUS_NAME, dir);
        return recorder;
    }

    recorder = g_malloc0(sizeof(janus_recordex_recorder));
    recorder->type = rec_type;
    recorder->hander = handler;
    recorder->dir = g_strdup(dir);
    recorder->codec = g_strdup(codec);
    recorder->format = g_strdup(format);
    recorder->filename = g_strdup(filename);
    g_atomic_int_set(&recorder->writable, 0);
    g_atomic_int_set(&recorder->destroyed, 0);
    recorder->expand = janus_recordex_opus_expand_malloc();
    janus_mutex_init(&recorder->mutex);

    return recorder;
}

void janus_recordex_opus_rex_destory(janus_recordex_recorder* recorder) {
    // Rmove hasttable
    janus_mutex_lock_nodebug(&recorder->mutex);
    if (recorder->hander)
        recorder->hander = NULL;
    if (recorder->dir)
        g_free(recorder->dir), recorder->dir = NULL;
    if (recorder->codec)
        g_free(recorder->codec), recorder->codec = NULL;
    if (recorder->format)
        g_free(recorder->format), recorder->format = NULL;
    if (recorder->filename)
        g_free(recorder->filename), recorder->filename = NULL;
    if (recorder->expand)
        janus_recordex_opus_expand_free(recorder->expand), recorder->expand = NULL;
    janus_mutex_unlock_nodebug(&recorder->mutex);
    janus_mutex_destroy(&recorder->mutex);
}

gint janus_recordex_opus_rex_open(janus_recordex_recorder* recorder) {
    return 0;
}

void janus_recordex_opus_rex_close(janus_recordex_recorder* recorder) {
	//if(!recorder || !g_atomic_int_compare_and_exchange(&recorder->writable, 1, 0))
}

gint janus_recordex_opus_rex_process(janus_recordex_recorder* recorder, gpointer buffer, guint length) {
    return 0;
}

static gpointer janus_recordex_opus_expand_malloc(void) {
    return (gpointer)g_malloc0(10);
}

static void janus_recordex_opus_expand_free(gpointer expand) {
    g_free(expand);
}