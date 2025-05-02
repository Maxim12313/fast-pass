#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "globals.hpp"
#include "messager_maker.hpp"
#include "player_system.hpp"
#include <enet/enet.h>
#include <string.h>

class Client {
public:
    Client() {
        client = enet_host_create(nullptr, 1, 1, 0, 0);
        if (client == nullptr) {
            fprintf(stderr, "An error occurred while trying to create an ENet "
                            "client host.\n");
            exit(1);
        }
        connect();
    }

    void handleEvent(Game &game) {
        while (enet_host_service(client, &event, EVENT_WAIT) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_RECEIVE:
                handleReceive(game);
                break;
            }
        }
    }

    void sendPos(Vector2 &pos) {
        uint32_t size = setPos(msg, pos);
        sendPacket(msg, size);
    }

    void sendPacket(const char *toSend, size_t n) {
        ENetPacket *packet = enet_packet_create(toSend, n, 0);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(client);
    }

    ~Client() {
        disconnect();
        enet_host_destroy(client);
    }

private:
    ENetAddress address;
    ENetEvent event;
    ENetPeer *peer;
    ENetHost *client;
    char msg[1024];

    void handleReceive(Game &game) {
        printf("A packet of length %u containing %s was received from %s "
               "on channel %u.\n",
               event.packet->dataLength, event.packet->data, event.peer->data,
               event.channelID);
        enet_packet_destroy(event.packet);
    }

    void connect() {
        enet_address_set_host(&address, "localhost");
        address.port = 1234;

        /* Initiate the connection, allocating the one channel */
        peer = enet_host_connect(client, &address, 1, 0);

        if (peer == nullptr) {
            fprintf(stderr,
                    "No available peers for initiating an ENet connection.\n");
            exit(1);
        }

        /* Wait up to 5 seconds for the connection attempt to succeed. */
        if (enet_host_service(client, &event, 1000) > 0 &&
            event.type == ENET_EVENT_TYPE_CONNECT) {
            puts("Connection succeeded.");
        } else {
            enet_peer_reset(peer);
            puts("Connection to localhost:1234 failed.");
            exit(1);
        }
    }
    void disconnect() {
        enet_peer_disconnect(peer, 0);
        while (enet_host_service(client, &event, 1000) > 0) {
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
};

#endif
