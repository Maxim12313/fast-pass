#include <enet/enet.h>
#include <iostream>

int main() {
    if (enet_initialize() != 0) {
        fprintf(stderr, "erorr while init enet\n");
        exit(1);
    }
    atexit(enet_deinitialize);

    ENetAddress address;
    ENetHost *server;

    address.host = ENET_HOST_ANY;
    address.port = 1234;

    server = enet_host_create(&address, 32, 1, 0, 0);
    if (server == nullptr) {
        fprintf(
            stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(1);
    }

    ENetEvent event;
    while (true) {
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 5000) > 0) {
            printf("%d\n", event.type);
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u.\n",
                       event.peer->address.host, event.peer->address.port);
                event.peer->data = (void *)"client stuff";
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                printf(
                    "A packet of length %u containing %s was received from %s "
                    "on channel %u.\n",
                    event.packet->dataLength, event.packet->data,
                    event.peer->data, event.channelID);

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%s disconnected.\n", event.peer->data);
                event.peer->data = nullptr;
            }
        }
    }

    enet_host_destroy(server);
}
