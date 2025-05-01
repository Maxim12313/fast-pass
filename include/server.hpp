#ifndef SERVER_HPP
#define SERVER_HPP

#include "config.hpp"
#include "messager_maker.hpp"
#include "random_generator.hpp"
#include <cassert>
#include <cstdint>
#include <enet/enet.h>
#include <iostream>

struct PeerData {
    uint32_t id;
};

class Server {
public:
    Server() {
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
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                handleConnect();
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                handleReceive();
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                handleDisconnect();
                break;
            }
        }
    }

    void sendPacket(const char *msg, size_t n, uint32_t peerId) {
        assert(peers.count(peerId) && "peerId not inside");
        ENetPeer *peer = peers[peerId];
        ENetPacket *packet =
            enet_packet_create(msg, n, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(server);
    }

    void deactivate() {
        puts("deactivating");
        enet_host_destroy(server);
    }

    ~Server() { deactivate(); }

private:
    ENetAddress address;
    ENetHost *server;
    ENetEvent event;
    std::unordered_map<uint32_t, ENetPeer *> peers;

    IDGenerator idGenerator;

    void handleConnect() {
        ENetAddress &addr = event.peer->address;
        uint32_t id = idGenerator.getId();
        printf("client connected from %x:%u giving id %u\n", addr.host,
               addr.port, id);
        PeerData *data = new PeerData(id);
        event.peer->data = (void *)data;
        peers[id] = event.peer;

        char *msg = "hello there";
        sendPacket(msg, strlen(msg) + 1, id);
    }

    void handleReceive() {
        PeerData *data = (PeerData *)event.peer->data;
        // printf("packet of length %u containing %s was received "
        //        "from %u "
        //        "on channel %u.\n",
        //        event.packet->dataLength, event.packet->data, data->id,
        //        event.channelID);

        char *received = (char *)event.packet->data;
        Vector2 pos = readPos(&received[1]);
        std::cout << pos.x << " " << pos.y << "\n";
        enet_packet_destroy(event.packet);
    }

    void handleDisconnect() {
        PeerData *data = (PeerData *)event.peer->data;
        printf("client %u disconnected.\n", data->id);
        idGenerator.destroyId(data->id);
        event.peer->data = nullptr;
    }
};

#endif
