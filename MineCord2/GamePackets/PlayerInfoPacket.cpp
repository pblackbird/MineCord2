#include "PlayerInfoPacket.h"

void PlayerInfoPacket::PlayerAdd(PlayerListEntry player) {
    MinecraftTypes::WriteString(buff, player.name);
    MinecraftTypes::WriteVarInt(buff, (int)player.properties.size());

    for (int j = 0; j < (int)player.properties.size(); j++) {
        PlayerPropertyListEntry prop = player.properties[j];

        MinecraftTypes::WriteString(buff, prop.propertyName);
        MinecraftTypes::WriteString(buff, prop.value);
        buff.writeUInt8((uint8_t)prop.isSigned);
        MinecraftTypes::WriteString(buff, prop.signature);
    }

    UpdateGameMode(player);
    UpdateLatency(player);
   // UpdateDisplayName(player); TODO: figure out whats wrong with it
}

void PlayerInfoPacket::UpdateGameMode(PlayerListEntry player) {
    MinecraftTypes::WriteVarInt(buff, (int)player.gamemode);
}

void PlayerInfoPacket::UpdateLatency(PlayerListEntry player) {
    MinecraftTypes::WriteVarInt(buff, player.ping);
}

void PlayerInfoPacket::UpdateDisplayName(PlayerListEntry player) {
    buff.writeBool(player.hasDisplayName);

    if (player.hasDisplayName)
        MinecraftTypes::WriteString(buff, player.displayName);
}

void PlayerInfoPacket::Build(Buffer& dest) {
    PKT_BEGIN(PLAYER_INFO_PACKETID);

    MinecraftTypes::WriteVarInt(buff, (int)action);
    MinecraftTypes::WriteVarInt(buff, (int)players.size());

    for (int i = 0; i < (int)players.size(); i++) {
        PlayerListEntry player = players[i];

        MinecraftTypes::WriteUUID(buff, player.uuid);

        switch (action) {
            case PlayerInfoAction::ADD_PLAYER:
                PlayerAdd(player);
                break;
            case PlayerInfoAction::UPDATE_GAMEMODE:
                UpdateGameMode(player);
                break;
            case PlayerInfoAction::UPDATE_LATENCY:
                UpdateLatency(player);
                break;
            case PlayerInfoAction::UPDATE_DISPLAY_NAME:
               // UpdateDisplayName(player);
                break;
            case PlayerInfoAction::REMOVE_PLAYER:
                break;
        }
    }

    PKT_END();
}