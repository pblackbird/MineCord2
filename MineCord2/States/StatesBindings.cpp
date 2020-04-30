#include "StatesBindings.h"
#include "HandshakeState.h"
#include "StatusState.h"
#include "LoginState.h"
#include "PlayState.h"

StatesBindings* StatesBindings::pSingleton;

void StatesBindings::Fill() {
	bindingMap[ClientState::HANDSHAKE] = new HandshakeState();
	bindingMap[ClientState::STATUS] = new StatusState();
	bindingMap[ClientState::LOGIN] = new LoginState();
	bindingMap[ClientState::PLAY] = new PlayState();
}

BaseClientState* StatesBindings::GetBinding(ClientState state) {
	if (!bindingMap.count(state)) {
		return nullptr;
	}

	return bindingMap[state];
}
