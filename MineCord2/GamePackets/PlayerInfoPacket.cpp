#include "PlayerInfoPacket.h"

void PlayerInfoPacket::Build(Buffer& dest) {
    PKT_BEGIN(PLAYER_INFO_PACKETID);

    MinecraftTypes::WriteVarInt(buff, (int)action);
    MinecraftTypes::WriteVarInt(buff, (int)players.size());

    for (int i = 0; i < (int)players.size(); i++) {
        // todo: uuid
        for (int j = 0; j < 16; j++) {
            buff.writeUInt8(0x11);
        }

        PlayerListEntry player = players[i];

        MinecraftTypes::WriteString(buff, player.name);
        MinecraftTypes::WriteVarInt(buff, (int)player.properties.size());

        for (int j = 0; j < (int)player.properties.size(); j++) {
            PlayerPropertyListEntry prop = player.properties[j];

            MinecraftTypes::WriteString(buff, prop.propertyName);
            MinecraftTypes::WriteString(buff, prop.value);
            buff.writeUInt8((uint8_t)prop.isSigned);
            MinecraftTypes::WriteString(buff, prop.signature);
        }

        MinecraftTypes::WriteVarInt(buff, (int)player.gamemode);
        MinecraftTypes::WriteVarInt(buff, player.ping);
    }

    PKT_END();
}