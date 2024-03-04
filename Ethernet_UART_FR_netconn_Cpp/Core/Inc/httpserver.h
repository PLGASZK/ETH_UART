#ifndef __HTTPSERVER_NETCONN_H__
#define __HTTPSERVER_NETCONN_H__

#include "lwip/api.h"

#ifdef __cplusplus
extern "C" {
#endif

// Declaration of HTTPServer structure
typedef struct {
    // Method for handling connection
    void (*serve)(struct netconn *conn);
} HTTPServer;

// Declaration of HTTPThread structure
typedef struct {
    // Method to start HTTP thread
    void (*start)(void *arg);
} HTTPThread;

// Declaration of function initializing HTTP server
void http_server_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __HTTPSERVER_NETCONN_H__ */
