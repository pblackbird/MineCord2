#pragma once

#include "BaseWorld.h"

class PrimaryWorld : public BaseWorld {
private:
	static PrimaryWorld* pSingleton;

public:
	static PrimaryWorld* GetInstance() {
		if (!pSingleton) {
			pSingleton = new PrimaryWorld();
		}

		return pSingleton;
	}

public:
	PrimaryWorld();

	virtual void Tick() override;
};