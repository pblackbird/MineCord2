#include "PlayerMove.h"
#include "../GamePackets/SyncClientPlayerPositionPacket.h"
#include "../GamePackets/SyncClientPositionRotationPacket.h"
#include "../GamePackets/SyncClientPlayerRotationPacket.h"

void UpdatePlayerTransform(Player* player, Point3D pos, Angle rotation) {
	auto playerEntity = player->GetSlaveEntity();

	const auto currentPlayerPos = playerEntity->GetPosition();

	Vector vecMove({
		(pos.x - currentPlayerPos.x),
		(pos.y - currentPlayerPos.y),
		(pos.z - currentPlayerPos.z),
	});

	playerEntity->SetMovementDirection(vecMove);

	playerEntity->SetRotation(rotation);

	playerEntity->OnNetSync();
	playerEntity->OnMove();
}

void OnPlayerMove(Player* player, BaseNetPacket& msg) {
	const auto playerEntity = player->GetSlaveEntity();

	Logger logger("Player position debugger");

	Point3D newPosition = playerEntity->GetPosition();
	Angle newAngle = playerEntity->GetRotation();

	switch (msg.packetId) {
		case SYNC_PLAYER_CLIENT: {
			const auto move = msg.Cast<SyncClientPlayerPositionPacket>();

			newPosition.x = move.x;
			newPosition.y = move.feetY;
			newPosition.z = move.z;

			break;
		}
		case SYNC_PLAYER_CLIENT_ROTATION_POSITION: {
			const auto move = msg.Cast<SyncClientPositionRotationPacket>();

			newPosition.x = move.x;
			newPosition.y = move.feetY;
			newPosition.z = move.z;

			newAngle.pitch = move.pitch;
			newAngle.yaw = move.yaw;

			break;
		}
		case SYNC_PLAYER_CLIENT_ROTATION: {
			const auto move = msg.Cast<SyncClientPlayerRotationPacket>();

			newAngle.pitch = move.pitch;
			newAngle.yaw = move.yaw;

			break;
		}
	}

	UpdatePlayerTransform(player, newPosition, newAngle);
}
