#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/apps/fs.h"
#include "string.h"
#include <stdio.h>
#include "cmsis_os.h"
#include "stm32f7xx_hal_uart.h"


extern char *read_data;

class HTTPServer {
public:
    HTTPServer() {}

    static void serve(struct netconn *conn) {
        struct netbuf *inbuf;
        err_t recv_err;
        char* buf;
        u16_t buflen;
        struct fs_file file;

        /* Read the data from the port, blocking if nothing yet there */
        recv_err = netconn_recv(conn, &inbuf);

        if (recv_err == ERR_OK) {
            if (netconn_err(conn) == ERR_OK) {
                /* Get the data pointer and length of the data inside a netbuf */
                netbuf_data(inbuf, (void**)&buf, &buflen);

                /* Check if request to get the index.html */
                if (strncmp((char const *)buf,"GET /index.html",15)==0) {
                    fs_open(&file, "/index.html");
                    // Alokacja pamięci dla txt
                    read_data = new char[file.len + 1]; // +1 for null term
                    if (read_data != nullptr) {
                        memcpy(read_data, file.data, file.len);
                        read_data[file.len] = '\0'; // add null term at the end
                        // send to client
                        netconn_write(conn, (const unsigned char*)read_data, (size_t)file.len, NETCONN_NOCOPY);
                    }
                    fs_close(&file);
                    // Zwolnienie pamięci dla txt po zakończeniu używania
                   /// delete[] read_data;
                } else {
                    /* Load Error page */
                    fs_open(&file, "/404.html");
                    // "404.html"
                    read_data = new char[file.len + 1];
                    if (read_data != nullptr) {
                        memcpy(read_data, file.data, file.len);
                        read_data[file.len] = '\0';
                        netconn_write(conn, (const unsigned char*)read_data, (size_t)file.len, NETCONN_NOCOPY);
                    }
                    fs_close(&file);
                   // delete[] read_data;
                }
            }
        }
        /* Close the connection (server closes in HTTP) */
        netconn_close(conn);

        /* Delete the buffer (netconn_recv gives us ownership,
        so we have to make sure to deallocate the buffer) */
        netbuf_delete(inbuf);
    }
};

class HTTPThread {
public:
    HTTPThread() {}

    static void start(void *arg) {
        struct netconn *conn, *newconn;
        err_t err, accept_err;

        /* Create a new TCP connection handle */
        conn = netconn_new(NETCONN_TCP);

        if (conn!= NULL) {
            /* Bind to port 80 (HTTP) with default IP address */
            err = netconn_bind(conn, IP_ADDR_ANY, 80);

            if (err == ERR_OK) {
                /* Put the connection into LISTEN state */
                netconn_listen(conn);

                while(1) {
                    /* accept any incoming connection */
                    accept_err = netconn_accept(conn, &newconn);
                    if(accept_err == ERR_OK) {
                        /* serve connection */
                        HTTPServer::serve(newconn);

                        /* delete connection */
                        netconn_delete(newconn);
                    }
                }
            }
        }
    }
};

void http_server_init() {
    sys_thread_new("http_thread", HTTPThread::start, nullptr, DEFAULT_THREAD_STACKSIZE, osPriorityNormal);
}
