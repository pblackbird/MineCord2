#pragma once

#include "BaseWorld.h"

class TestWorld : public BaseWorld {
private:
	static TestWorld* pSingleton;

public:
	static TestWorld* GetInstance() {
		if (!pSingleton) {
			pSingleton = new TestWorld();
		}

		return pSingleton;
	}

public:
	virtual void Tick() override;
};