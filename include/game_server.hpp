#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include "config.hpp"
#include "random_generator.hpp"
#include <cstdint>
#include <enet/enet.h>
#include <iostream>

struct PeerData {
    uint32_t id;
};

class GameServer {
public:
    GameServer() {
        address.host = ENET_HOST_ANY;
        address.port = 1234;
        server = enet_host_create(&address, 32, 1, 0, 0);
        if (server == nullptr) {
            fprintf(stderr, "An error occurred while trying to create an ENet "
                            "server host.\n");
            exit(1);
        }
    }
    void handleEvent() {
        while (enet_host_service(server, &event, EVENT_WAIT) > 0) {
            ENetAddress &addr = event.peer->address;
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                uint32_t id = idGenerator.getId();
                printf("client connected from %x:%u giving id %u\n", addr.host,
                       addr.port, id);
                PeerData *data = new PeerData(id);
                event.peer->data = (void *)data;
                break;
            }
            case ENET_EVENT_TYPE_RECEIVE: {
                PeerData *data = (PeerData *)event.peer->data;
                printf("packet of length %u containing %s was received "
                       "from %u "
                       "on channel %u.\n",
                       event.packet->dataLength, event.packet->data, data->id,
                       event.channelID);
                enet_packet_destroy(event.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT: {
                PeerData *data = (PeerData *)event.peer->data;
                printf("client %u disconnected.\n", data->id);
                idGenerator.destroyId(data->id);
                event.peer->data = nullptr;
                break;
            }
            }
        }
    }

    void deactivate() {
        puts("deactivating");
        enet_host_destroy(server);
    }

    ~GameServer() { deactivate(); }

private:
    ENetAddress address;
    ENetHost *server;
    ENetEvent event;
    IDGenerator idGenerator;
};

#endif
