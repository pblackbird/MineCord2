#pragma once

#include <string>
#include "../ThirdParty/BufferedIO.h"
#include "../MinecraftTypes.h"
#include "../Transformable.h"

enum class MetadataType : int {
	BYTE,
	VARINT,
	FLOAT,
	STRING,
	CHAT,
	OPTCHAT,
	SLOT,
	BOOLEAN,
	ROTATION,
	POSITION,
	OPTPOSITION,
	DIRECTION,
	OPTUUID,
	OPTBLOCKID,
	NBT,
	PARTICLE,
	VILLAGERDATA,
	OPTVARINT,
	POSE
};
enum class BaseMetadataIndex : uint8_t {
	STATE_BITMASK = 0,
	AIR = 1,
	CUSTOMNAME = 2,
	IS_CUSTOMNAME_VISIBLE = 3,
	IS_SILENT = 4,
	NO_GRAVITY = 5
};

class Entity : public Transformable {
protected:
	entity_id entityId;
	std::string entityName, uuid;
	Buffer metadataBlob;

public:
	uint8_t stateMask = 0;
	int air = 300;
	std::string customName;
	bool isCustomNameVisible = false;
	bool isSilent = false;
	bool isNoGravity = false;

private:
	static entity_id entityIndexCounter;

protected:

	void AddStringMetadataEntry(uint8_t index, std::string& val) {
		metadataBlob.writeUInt8(index);
		metadataBlob.writeUInt8((uint8_t)MetadataType::STRING);
		MinecraftTypes::WriteString(metadataBlob, val);
	}

	template<class T>
	void AddMetadataEntry(uint8_t index, MetadataType type, T val) {
		metadataBlob.writeUInt8(index);
		metadataBlob.writeUInt8((uint8_t)type);

		// todo: finish types switch

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wfloat-conversion"
		switch (type) {
			case MetadataType::BYTE: {
				metadataBlob.writeUInt8(val);
				break;
			}
			case MetadataType::VARINT: {
				MinecraftTypes::WriteVarInt(metadataBlob, val);
				break;
			}
			case MetadataType::FLOAT: {
				metadataBlob.writeFloat_BE(val);
				break;
			}
		}
#pragma GCC diagnostic pop
	}

	void EndMetadataArray();

public:
	virtual void BuildMetadata();

public:
	Entity(const std::string&& uuid);
	Entity();

	virtual void OnTick() = 0;
	virtual void OnCreate() = 0;

	virtual void OnDestroy();

	std::vector<uint8_t> GetMetadataBlob();

	std::string GetName() {
		return entityName;
	}

	std::string GetUUID() {
		return uuid;
	}

	void SetName(const std::string& name) {
		entityName = name;
	}

	entity_id GetID() {
		return entityId;
	}
};