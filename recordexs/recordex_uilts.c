#include <sys/stat.h>
#include <errno.h>

#include "../utils.h"
#include "recordex_uilts.h"

janus_recordex_medium get_media_type(const gchar* codec)
{
    janus_recordex_medium type = JANUS_RECORDEX_UNKNOWN;

    if(!strcasecmp(codec, "vp8") || !strcasecmp(codec, "vp9") || !strcasecmp(codec, "h264")
			 || !strcasecmp(codec, "av1") || !strcasecmp(codec, "h265")) {
		type = JANUS_RECORDEX_VIDEO;
	} else if(!strcasecmp(codec, "opus") || !strcasecmp(codec, "multiopus")
			|| !strcasecmp(codec, "g711") || !strcasecmp(codec, "pcmu") || !strcasecmp(codec, "pcma")
			|| !strcasecmp(codec, "g722")) {
		type = JANUS_RECORDEX_AUDIO;
	} else if(!strcasecmp(codec, "text") || !strcasecmp(codec, "binary")) {
		type = JANUS_RECORDEX_DATA;
	} else {
		type = JANUS_RECORDEX_UNKNOWN;
	}

    return type;
}

gint create_if_dir_not_exist(const gchar* dir)
{
    gint result = -1;

    if(dir != NULL) {
		/* Check if this directory exists, and create it if needed */
		struct stat s;
		int err = stat(dir, &s);
		if(err == -1) {
			if(ENOENT == errno) {
				/* Directory does not exist, try creating it */
				if(janus_mkdir(dir, 0755) < 0) {
					JANUS_LOG(LOG_ERR, "mkdir (%s) error: %d (%s)\n", dir, errno, strerror(errno));
				} else {
                    JANUS_LOG(LOG_VERB, "Directory created: %s\n", dir);
                    result = 0;
                }
			} else {
				JANUS_LOG(LOG_ERR, "stat (%s) error: %d (%s)\n", dir, errno, strerror(errno));
			}
		} else {
			if(S_ISDIR(s.st_mode)) {
				/* Directory exists */
				JANUS_LOG(LOG_VERB, "Directory exists: %s\n", dir);
                result = 0;
			} else {
				/* File exists but it's not a directory? */
				JANUS_LOG(LOG_ERR, "Not a directory? %s\n", dir);
			}
		}
	}

    return result;
}
