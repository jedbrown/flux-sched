#ifndef PLUGIN_H
#define PLUGIN_H

#include "flux.h"

/* Plugins will be connected to these well-known shared memory zmq sockets.
 */
#define REQUEST_URI         "inproc://request"
#define EVENT_URI           "inproc://event"

/* A plugin defines 'const struct plugin_ops ops = {...}' containing
 * its implementations of one or more of the plugin operations.
 */
struct plugin_ops {
    int (*main)(flux_t h, zhash_t *args);
};

typedef struct plugin_ctx_struct *plugin_ctx_t;

/* Load plugin by path.
 */
plugin_ctx_t plugin_load (flux_t h, const char *path,
                          const char *name, const char *uuid, zhash_t *args);

/* Signal plugin to unload by sending it EOF (zero length message).
 * It will respond with an EOF when it is ready to be destroyed.
 */
void plugin_unload (plugin_ctx_t p);

/* Destroy plugin.
 * This function calls pthread_join thus should only be called after
 * EOF is received as described above or the calling thread may be blocked.
 */
void plugin_destroy (plugin_ctx_t p);

/* Accessors.
 */
const char *plugin_name (plugin_ctx_t p);
const char *plugin_uuid (plugin_ctx_t p);
const char *plugin_digest (plugin_ctx_t p);
int plugin_size (plugin_ctx_t p);
void *plugin_sock (plugin_ctx_t p);

#endif /* !PLUGIN_H */

/*
 * vi:tabstop=4 shiftwidth=4 expandtab
 */
