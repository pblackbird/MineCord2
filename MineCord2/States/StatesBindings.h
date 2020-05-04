#pragma once

#include <map>
#include <array>

#include "../Utl.h"
#include "BaseClientState.h"

class StatesBindings {
private:
	static StatesBindings* pSingleton;

public:
	static StatesBindings* GetInstance() {
		if (!pSingleton) {
			pSingleton = new StatesBindings();
		}

		return pSingleton;
	}

private:
	std::map<ClientState, BaseClientState*> bindingMap;
	Logger logger;

public:
	StatesBindings() {
		logger.SetTag("States bindings");
	}

	void Fill();
	BaseClientState* GetBinding(ClientState state);
};