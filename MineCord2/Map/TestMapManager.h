#pragma once

#include "IMapManager.h"

class TestMapManager : public IMapManager {
public:
	virtual void SerializeChunkAtPosition(Point3D pos, Buffer& dest) override;
};