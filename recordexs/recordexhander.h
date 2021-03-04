#ifndef JANUS_RECORDEXHANDER_H
#define JANUS_RECORDEXHANDER_H
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mutex.h"
#include "refcount.h"

#define JANUS_RECORDEXHANDER_API_VERSION	1

#define JANUS_RECORDEX_HANDER_INIT(...) {		\
		.init = NULL,							\
		.destroy = NULL,						\
		.get_api_compatibility = NULL,			\
		.get_version = NULL,					\
		.get_version_string = NULL,				\
		.get_description = NULL,				\
		.get_name = NULL,						\
		.get_author = NULL,						\
		.get_package = NULL,					\
		.get_format = NULL,						\
		.rex_create = NULL,						\
		.rex_destory = NULL,					\
		.rex_open = NULL,						\
		.rex_close = NULL,						\
		.rex_process = NULL,					\
		## __VA_ARGS__ }

typedef struct janus_recordex_hander janus_recordex_hander;
typedef struct janus_recordex_recorder janus_recordex_recorder;

struct janus_recordex_hander {
	gint (* const init)(const gchar *config_path);
	void (* const destroy)(void);
	gint (* const get_api_compatibility)(void);
	gint (* const get_version)(void);
	const gchar *(* const get_version_string)(void);
	const gchar *(* const get_description)(void);
	const gchar *(* const get_name)(void);
	const gchar *(* const get_author)(void);
	const gchar *(* const get_package)(void);
	const gchar *(* const get_format)(void);

	janus_recordex_recorder* (* const rex_create)(janus_recordex_hander *handler, const gchar *dir, const gchar *codec, const gchar *format, const gchar *filename);
	void (* const rex_destory)(janus_recordex_recorder* recorder);
	gint (* const rex_open)(janus_recordex_recorder* recorder);
	void (* const rex_close)(janus_recordex_recorder* recorder);
	gint (* const rex_process)(janus_recordex_recorder* recorder, gpointer buffer, guint length);
};

typedef enum janus_recordex_medium {
	JANUS_RECORDEX_AUDIO,
	JANUS_RECORDEX_VIDEO,
	JANUS_RECORDEX_DATA,
	JANUS_RECORDEX_UNKNOWN
} janus_recordex_medium;

struct janus_recordex_recorder {
	janus_recordex_hander* 	hander;
	gchar*					dir;
	gchar* 					codec;
	gchar* 					format;
	gchar*					filename;
	janus_recordex_medium	type;
	volatile gint 			writable;
	volatile gint 			destroyed;
	gpointer				expand;
	janus_mutex 			mutex;
};

typedef janus_recordex_hander* create_r(void);

#endif
