#include "Player.h"
#include "GamePackets/JoinGamePacket.h"
#include "GamePackets/KeepAlivePacket.h"
#include "GamePackets/SetPlayerTransformPacket.h"
#include "World/PrimaryWorld.h"

#include "PlayerActions/ChatMsg.h"

static std::map<int, OnPlayerAction_t> playerActionHandlers = {
	{ CHAT_MSG_FROM_CLIENT_PACKETID, OnPlayerChatMessage }
};

Player::~Player() {
	PrimaryWorld::GetInstance()->DestroyEntity(
		pSlave->GetID()
	);
}

void Player::DispatchServiceMessage(BaseNetPacket& msg) {
	switch (msg.packetId) {
		case KEEP_ALIVE_CLIENT_PACKETID: {
			playerLogger.Info(L"Keep alive pktid = %i", msg.packetId);

			if (!isWaitingForPong) {
				playerLogger.Warning(L"Got pong response, but ping was not requested!");
				return;
			}

			playerLogger.Info(L"Got normal ping response");

			isWaitingForPong = false;
			lastKeepAlive = std::time(NULL);

			break;
		}
	}
}

void Player::Join() {
	JoinGamePacket join;
	join.entityId = pSlave->GetID();
	join.gamemode = GameMode::CREATIVE;
	join.dimension = Dimension::OVERWORLD;
	join.maxPlayers = 100;
	join.worldType = "default";
	join.viewDistance = 10;
	join.isDebug = false;

	pNetClient->Invoke(join);
}

void Player::SetTransform(Point3D position, Angle rotation, int teleportId) {
	SetPlayerTransformPacket transformMsg;
	transformMsg.flags = 0;
	transformMsg.teleportId = teleportId;

	transformMsg.pitch = rotation.pitch;
	transformMsg.yaw = rotation.yaw;

	transformMsg.x = position.x;
	transformMsg.y = position.y;
	transformMsg.z = position.z;

	pNetClient->Invoke(transformMsg);
}

void Player::Ping() {
	KeepAlivePacket keepAliveMsg;
	keepAliveMsg.keepAliveId = std::time(NULL);

	pNetClient->Invoke(keepAliveMsg);

	isWaitingForPong = true;
}

void Player::OnMsg(BaseNetPacket& msg) {
	DispatchServiceMessage(msg);

	if (!playerActionHandlers[msg.packetId]) {
		return;
	}

	playerActionHandlers[msg.packetId](this, msg);
}