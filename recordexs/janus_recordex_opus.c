#include "recordexhander.h"

#define JANUS_RECORDEX_OPUS_VERSION			1
#define JANUS_RECORDEX_OPUS_VERSION_STRING 	"0.0.1"
#define JANUS_RECORDEX_OPUS_DESCRIPTION 	"This is recorder handler plugin for Janus, which recording opus file."
#define JANUS_RECORDEX_OPUS_NAME 		    "Janus recordex opus plugin"
#define JANUS_RECORDEX_OPUS_AUTHOR 			"xiaoxu.shi <xaoxu_shi@yeah.net>"
#define JANUS_RECORDEX_OPUS_PACKAGE			"janus.recordex.opus"
#define JANUS_RECORDEX_OPUS_FORMAT			"opus"

janus_recordex_hander* create(void);
int  janus_recordex_opus_init(const char *config_path);
void janus_recordex_opus_destroy(void);
int  janus_recordex_opus_get_api_compatibility(void);
int  janus_recordex_opus_get_version(void);
const char *janus_recordex_opus_get_version_string(void);
const char *janus_recordex_opus_get_description(void);
const char *janus_recordex_opus_get_name(void);
const char *janus_recordex_opus_get_author(void);
const char *janus_recordex_opus_get_package(void);
const char *janus_recordex_opus_get_format(void);

janus_recordex_recorder* janus_recordex_opus_rex_create(const char *dir, const char *filename);
void janus_recordex_opus_rex_destory(janus_recordex_recorder* recorder);
int  janus_recordex_opus_rex_open(janus_recordex_recorder* recorder);
void janus_recordex_opus_rex_close(janus_recordex_recorder* recorder);
int  janus_recordex_opus_rex_process(janus_recordex_recorder* recorder, char *buffer, uint length);

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


int janus_recordex_opus_init(const char *config_path) {
    JANUS_LOG(LOG_VERB, "%s inited!\n", JANUS_RECORDEX_OPUS_NAME);
    return 0;
}

void janus_recordex_opus_destroy(void) {
    JANUS_LOG(LOG_VERB, "%s destroyed!\n", JANUS_RECORDEX_OPUS_NAME);
}

int janus_recordex_opus_get_api_compatibility(void) {
    return JANUS_RECORDEXHANDER_API_VERSION;
}

int janus_recordex_opus_get_version(void) {
    return JANUS_RECORDEX_OPUS_VERSION;
}

const char *janus_recordex_opus_get_version_string(void) {
    return JANUS_RECORDEX_OPUS_VERSION_STRING;
}

const char *janus_recordex_opus_get_description(void) {
    return JANUS_RECORDEX_OPUS_DESCRIPTION;
}

const char *janus_recordex_opus_get_name(void) {
    return JANUS_RECORDEX_OPUS_NAME;
}

const char *janus_recordex_opus_get_author(void) {
    return JANUS_RECORDEX_OPUS_AUTHOR;
}

const char *janus_recordex_opus_get_package(void) {
    return JANUS_RECORDEX_OPUS_PACKAGE;
}

const char *janus_recordex_opus_get_format(void) {
    return JANUS_RECORDEX_OPUS_FORMAT;
}

janus_recordex_recorder* janus_recordex_opus_rex_create(const char *dir, const char *filename) {
    return NULL;
}

void janus_recordex_opus_rex_destory(janus_recordex_recorder* recorder) {

}

int janus_recordex_opus_rex_open(janus_recordex_recorder* recorder) {
    return 0;
}

void janus_recordex_opus_rex_close(janus_recordex_recorder* recorder) {

}

int janus_recordex_opus_rex_process(janus_recordex_recorder* recorder, char *buffer, uint length) {
    return 0;
}

