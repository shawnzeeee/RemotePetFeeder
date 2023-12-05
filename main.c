#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "solenoid.h"


static int count = 0;
static int callback_ws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:
            lws_callback_on_writable(wsi);
            break;

        case LWS_CALLBACK_CLIENT_RECEIVE:
            printf("Received data: %s\n", (char *)in);
            if (strcmp((char *)in, "changeVariable") == 0) {
            pin_on();
            sleep(1);
            pin_off();
            }
            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE:
            // Example: sending a message
            {
                unsigned char buf[LWS_SEND_BUFFER_PRE_PADDING + 512 +
                                  LWS_SEND_BUFFER_POST_PADDING];
                unsigned char *p = &buf[LWS_SEND_BUFFER_PRE_PADDING];
                size_t n = sprintf((char *)p, "Hello from C client");
                lws_write(wsi, p, n, LWS_WRITE_TEXT);
            }
            break;

        default:
            break;
    }
    return 0;
}

int main(void) {

    unexport_gpio();
    export_gpio();
    set_gpio_direction_out();


    struct lws_context_creation_info info;
    memset(&info, 0, sizeof info);

    struct lws_protocols protocols[] = {
        { "my-protocol", callback_ws, 0, 512, },
        { NULL, NULL, 0, 0 } /* terminator */
    };

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = protocols;
    info.gid = -1;
    info.uid = -1;

    struct lws_context *context = lws_create_context(&info);

    // Client connection
    struct lws_client_connect_info ccinfo = {0};
    ccinfo.context = context;
    ccinfo.address = "207.23.207.85";
    ccinfo.port = 3000;
    ccinfo.path = "/ws";
    ccinfo.host = lws_canonical_hostname(context);
    ccinfo.origin = "http://207.23.207.85";
    ccinfo.protocol = protocols[0].name;

    struct lws *wsi = lws_client_connect_via_info(&ccinfo);

    // Event loop
    while (1) {
        lws_service(context, 50);
    }

    lws_context_destroy(context);
    return 0;
}


