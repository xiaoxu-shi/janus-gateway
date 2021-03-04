#ifndef JANUS_RECORDEX_UILTS_H
#define JANUS_RECORDEX_UILTS_H
#include "recordexhander.h"

janus_recordex_medium get_media_type(const gchar* codec);

gint create_if_dir_not_exist(const gchar* dir);

#endif
