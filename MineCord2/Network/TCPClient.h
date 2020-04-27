#pragma once

#include <cstdint>
#include <vector>
#include <unistd.h>
#include <sys/socket.h>

#include "NetworkUtils.h"
#include "../Logger.h"

enum class TcpRawState {
	WAITING_FOR_MESSAGE,
	IDLE
};

typedef struct {
	std::size_t recvFeedBytes = 0, sendFeedBytes = 0;
	std::vector<uint8_t> recvBuffer, sendBuffer;
} NetworkBuffers;

class TCPClient {
protected:
	int clientSocket;
	uint32_t ipv4;
	NetworkBuffers buffers;
	TcpRawState state = TcpRawState::IDLE;

	Logger logger;

public:
	TCPClient(int socket, uint32_t ipv4) : clientSocket(socket), ipv4(ipv4) {
		logger.SetTag(NetworkUtils::FormatIPv4(ipv4));
	};

	ssize_t SendData(const std::vector<uint8_t>& buffer);

	virtual void OnChunk(const std::vector<uint8_t>& buffer) = 0;
	virtual void OnMessageReceived(std::vector<uint8_t>& buffer) = 0;

	void Disconnect();
};

