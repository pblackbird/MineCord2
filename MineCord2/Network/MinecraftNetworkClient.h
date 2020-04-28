#pragma once

#include "TCPClient.h"
#include "NetworkUtils.h"
#include "../States/BaseClientState.h"
#include "../Logger.h"
#include "../Packets/BaseNetPacket.h"
#include "../ThirdParty/BufferedIO.h"

enum class ClientState : int {
	HANDSHAKE = -1,
	LOGIN = 2,
	STATUS = 1,
	PLAY = 3
};

class BaseNetPacket;

class MinecraftNetworkClient : public TCPClient {
protected:
	ClientState clientState = ClientState::HANDSHAKE;
	std::wstring username;

public:
	MinecraftNetworkClient(int socket, uint32_t ipv4);
	virtual ~MinecraftNetworkClient() override;

	template<class T>
	void Invoke(T& pkt) {
		Buffer data;
		pkt.Build(data);

		SendData(data.getBuffer());
	}

	std::wstring GetUsername() {
		return username;
	}

	void SetUsername(const std::wstring&& newUsername) {
		username = newUsername;
	}

	ClientState GetState() {
		return clientState;
	}

	void SwitchState(ClientState newState) {
		clientState = newState;
	}

	void UpdateRecvBuffer(const std::vector<uint8_t>& buffer);
	void OnChunk(const std::vector<uint8_t>& buffer) override;
	void OnMessageReceived(std::vector<uint8_t>& buffer) override;
};

