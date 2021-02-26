#ifndef JANUS_RECORDEXHANDER_H
#define JANUS_RECORDEXHANDER_H
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mutex.h"
#include "refcount.h"

#define JANUS_RECORDEXHANDER_API_VERSION	15

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
		.recordex_create = NULL, 				\
		.recordex_delete = NULL,				\
		.recordex_open = NULL, 					\
		.recordex_close = NULL, 				\
		.recordex_process = NULL, 				\
		## __VA_ARGS__ }

typedef struct janus_recordex_hander janus_recordex_hander;
typedef struct janus_recordex_recorder janus_recordex_recorder;

struct janus_recordex_hander {
	int  (* const init)(const char *config_path);
	void (* const destroy)(void);
	int  (* const get_api_compatibility)(void);
	int  (* const get_version)(void);
	const char *(* const get_version_string)(void);
	const char *(* const get_description)(void);
	const char *(* const get_name)(void);
	const char *(* const get_author)(void);
	const char *(* const get_package)(void);

	janus_recordex_recorder* (* recordex_create)(const char *dir, const char *filename);
	void (* recordex_delete)(janus_recordex_recorder* recorder);
	int  (* recordex_open)(janus_recordex_recorder* recorder);
	void (* recordex_close)(janus_recordex_recorder* recorder);
	int  (* recordex_process)(janus_recordex_recorder* recorder, char *buffer, uint length);
};

typedef enum janus_recordex_medium {
	JANUS_RECORDEX_AUDIO,
	JANUS_RECORDEX_VIDEO,
	JANUS_RECORDEX_DATA
} janus_recordex_medium;

struct janus_recordex_recorder {
	janus_recordex_hander* 	hander;
	const char*				dir;
	const char*				filename;
	janus_recordex_medium	type;
	volatile int 			writable;
	volatile gint 			destroyed;
	FILE*					file;
	void*					expand;
	janus_refcount 			ref;
};

typedef janus_recordex_hander* create_e(void);

#endif
