#include <libwebsockets.h>
#include <string.h>
#include <stdio.h>

static int testVariable = 0;

static int callback_ws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len) {
    switch (reason) {
        case LWS_CALLBACK_CLIENT_RECEIVE:
            printf("Received data: %s\n", (char *)in);
            if (strcmp((char *)in, "changeVariable") == 0) {
                testVariable = 1;
                printf("Variable changed to: %d\n", testVariable);
            }
            break;

        default:
            break;
    }
    return 0;
}

int main(void) {
    struct lws_context_creation_info info;
    memset(&info, 0, sizeof(info));

    info.port = CONTEXT_PORT_NO_LISTEN;
    info.protocols = (const struct lws_protocols[]) {
        { "websocket-protocol", callback_ws, 0, 0 },
        { NULL, NULL, 0, 0 }
    };
    info.gid = -1;
    info.uid = -1;

    struct lws_context *context = lws_create_context(&info);
    if (context == NULL) {
        fprintf(stderr, "lws init failed\n");
        return -1;
    }

    struct lws_client_connect_info connectInfo = {
        .context = context,
        .address = "localhost",
        .port = 8080,
        .path = "/",
        .protocol = "websocket-protocol",
        .ssl_connection = 0,
    };

    struct lws *ws = lws_client_connect_via_info(&connectInfo);
    if (ws == NULL) {
        fprintf(stderr, "WebSocket connection failed\n");
        return -1;
    }

    while (1) {
        lws_service(context, 50);
    }

    lws_context_destroy(context);
    return 0;
}
