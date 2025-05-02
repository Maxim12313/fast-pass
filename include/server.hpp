#ifndef SERVER_HPP
#define SERVER_HPP

#include "globals.hpp"
#include "messager_maker.hpp"
#include "random_generator.hpp"
#include <cassert>
#include <cstdint>
#include <enet/enet.h>
#include <iostream>

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

    void handleEvent(Game &g) {
        while (enet_host_service(server, &event, EVENT_WAIT) > 0) {
            switch (event.type) {
            case ENET_EVENT_TYPE_CONNECT:
                handleConnect(g);
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                handleReceive(g);
                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                handleDisconnect();
                break;
            }
        }
    }

    void sendPacket(const char *toSend, size_t n, uint32_t peerId) {
        assert(toPeer.count(peerId) && "peerId not inside");
        ENetPeer *peer = toPeer[peerId];
        ENetPacket *packet =
            enet_packet_create(toSend, n, ENET_PACKET_FLAG_RELIABLE);
        enet_peer_send(peer, 0, packet);
        enet_host_flush(server);
    }

    void deactivate() {
        LOG("deactivating");
        enet_host_destroy(server);
    }

    ~Server() { deactivate(); }

private:
    ENetAddress address;
    ENetHost *server;
    ENetEvent event;

    std::unordered_map<uint32_t, ENetPeer *> toPeer;
    std::unordered_map<ENetPeer *, uint32_t> toId;

    IDGenerator idGenerator;
    char msg[1024];

    void handleConnect(Game &g) {
        ENetAddress &addr = event.peer->address;
        uint32_t id = idGenerator.getId();

        toPeer[id] = event.peer;
        toId[event.peer] = id;

        LOG(id << " connected ");
        g.players.emplace_back(id);
        // sendGameState(g);
    }

    void handleReceive(Game &g) {
        char *received = (char *)event.packet->data;

        uint32_t id = toId[event.peer];

        Vector2 pos;
        readPos(pos, &received[1]);
        for (PlayerBody &body : g.players) {
            if (body.id == id) {
                body.pos = pos;
                break;
            }
        }

        enet_packet_destroy(event.packet);
    }

    void handleDisconnect() {
        uint32_t id = toId[event.peer];
        LOG("client " << id << " disconnected");

        idGenerator.destroyId(id);
        toPeer.erase(id);
        toId.erase(event.peer);
    }

    void sendGameState(Game &g) {
        uint32_t offset = 0;
        for (PlayerBody &body : g.players) {
            offset += setPos(&msg[offset], body.pos);
        }
    }
};

#endif
