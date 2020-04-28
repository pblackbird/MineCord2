#pragma once

#include <stdint.h>
#include <string>

#include "ThirdParty/BufferedIO.h"

typedef int entity_id;

enum class ServerChatMessageType : uint8_t {
	CHATBOX = 0,
	SYSTEM = 1,
	GAMEINFO = 2
};

enum class GameMode : uint8_t {
	SURVIVAL = 0,
	CREATIVE = 1,
	ADVENTURE = 2,
	SPECTATOR = 3
};

enum class Dimension : int {
	NETHER = -1,
	OVERWORLD = 0,
	END = 1
};

namespace MinecraftTypes {
	int ReadVarInt(Buffer& buff, int* bytesRead = nullptr);
	void WriteVarInt(Buffer& buff, int val);

	std::string ReadString(Buffer& buff);
	void WriteString(Buffer& buf, std::string str);
	void WriteString(Buffer& buf, char str[], int size);

	//static void WritePosition(Buffer& buff, Point3D position);
	//static Point3D ReadPosition(Buffer& buff);
};
