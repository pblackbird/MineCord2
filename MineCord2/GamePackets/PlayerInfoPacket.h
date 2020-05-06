#pragma once

#include <string>
#include <vector>
#include "../MinecraftTypes.h"
#include "../Packets/BaseNetPacket.h"
#include <uuid/uuid.h>

enum class PlayerInfoAction {
    ADD_PLAYER,
    UPDATE_GAMEMODE,
    UPDATE_LATENCY,
    UPDATE_DISPLAY_NAME,
    REMOVE_PLAYER
};

typedef struct {
    std::string propertyName;
    std::string value;
    bool isSigned;
    std::string signature;
} PlayerPropertyListEntry;

typedef struct {
    uuid_t uuid;
    std::string name;
    std::vector<PlayerPropertyListEntry> properties;
    GameMode gamemode;
    int ping;
    bool hasDisplayName;
    std::string displayName;
} PlayerListEntry;

class PlayerInfoPacket : public BaseNetPacket {
public:
    PlayerInfoAction action;
    uuid_t uuid;
    std::vector<PlayerListEntry> players;

public:
    PlayerInfoPacket() {
        isCompressed = true;
    }

    virtual void Build(Buffer& dest) override;
};