#pragma once

#include <vector>

#include "../Packets/BaseNetPacket.h"
#include "../Transformable.h"

class SpawnPlayerPacket : public BaseNetPacket {
public:
    entity_id id;
    uuid_t uuid;
    Point3D position;
    Angle rotation;

    std::vector<uint8_t> metadata;

public:
    SpawnPlayerPacket() {
        isCompressed = true;
    }

    virtual void Build(Buffer& dest) override;
};