#include "PlayerMove.h"
#include "../GamePackets/SyncClientPlayerPositionPacket.h"
#include "../GamePackets/SyncClientPositionRotationPacket.h"
#include "../GamePackets/SyncClientPlayerRotationPacket.h"

void UpdatePlayerTransform(Player* player, Point3D pos, Angle rotation) {
	auto playerEntity = player->GetSlaveEntity();

	const auto currentPlayerPos = playerEntity->GetPosition();

	Point3D vecMove = {
		(pos.x * 32 - currentPlayerPos.x * 32) * 128,
		(pos.y * 32 - currentPlayerPos.y * 32) * 128,
		(pos.z * 32 - currentPlayerPos.z * 32) * 128,
	};

	playerEntity->SetLastPosition(vecMove);
	playerEntity->SetPosition(pos);
	playerEntity->SetRotation(rotation);

	playerEntity->SyncEntity();
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

	/*logger.Info(
		"Player %s pos = %lf %lf %lf (%0.2f %0.2f)", 
		player->GetSlaveEntity()->GetName().c_str(), 
		newPosition.x,
		newPosition.y,
		newPosition.z,

		newAngle.pitch,
		newAngle.yaw
	);*/

	UpdatePlayerTransform(player, newPosition, newAngle);
}
