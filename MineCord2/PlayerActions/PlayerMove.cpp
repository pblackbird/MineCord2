#include "PlayerMove.h"
#include "../GamePackets/SyncClientPlayerPositionPacket.h"
#include "../GamePackets/SyncClientPositionRotationPacket.h"

void UpdatePlayerTransform(Player* player, Point3D pos, Angle rotation) {
	auto playerEntity = player->GetSlaveEntity();

	playerEntity->SetPosition(pos);
	playerEntity->SetRotation(rotation);
}

void OnPlayerMove(Player* player, BaseNetPacket& msg) {
	Logger logger("Player position debugger");

	Point3D newPosition;
	Angle newAngle;

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
	}

	logger.Info(
		"Player %s pos = %lf %lf %lf (%0.2f %0.2f)", 
		player->GetSlaveEntity()->GetName().c_str(), 
		newPosition.x,
		newPosition.y,
		newPosition.z,

		newAngle.pitch,
		newAngle.yaw
	);

	UpdatePlayerTransform(player, newPosition, newAngle);
}
