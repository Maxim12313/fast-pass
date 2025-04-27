#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include <enet/enet.h>
#include <iostream>
#include <string.h>

class GameClient {
public:
    GameClient() {
        client = enet_host_create(nullptr, 1, 1, 0, 0);
        if (client == nullptr) {
            fprintf(stderr, "An error occurred while trying to create an ENet "
                            "client host.\n");
            exit(1);
        }
    }
    void connect() {
        enet_address_set_host(&address, "localhost");
        address.port = 1234;

        /* Initiate the connection, allocating the one channel */
        peer = enet_host_connect(client, &address, 1, 0);

        if (peer == NULL) {
            fprintf(stderr,
                    "No available peers for initiating an ENet connection.\n");
            exit(EXIT_FAILURE);
        }

        /* Wait up to 5 seconds for the connection attempt to succeed. */
        if (enet_host_service(client, &event, 5000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT) {
            puts("Connection succeeded.");
        } else {
            enet_peer_reset(peer);
            puts("Connection to localhost:1234 failed.");
            exit(1);
        }
    }
    void handleEvent() {
        while (enet_host_service(client, &event, 0) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                printf(
                    "A packet of length %u containing %s was received from %s "
                    "on channel %u.\n",
                    event.packet->dataLength, event.packet->data,
                    event.peer->data, event.channelID);
                enet_packet_destroy(event.packet);
            }
        }
    }

    void sendPacket(const char *msg) {
        ENetPacket *packet =
            enet_packet_create(msg, strlen(msg) + 1, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(client);
    }

    void disconnect() {
        enet_peer_disconnect(peer, 0);
        while (enet_host_service(client, &event, 3000) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                enet_packet_destroy(event.packet);
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                puts("Disconnection successful");
                break;
            }
        }
    }

    ~GameClient() { disconnect(); }

private:
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;
    ENetHost *client;
};

#endif
