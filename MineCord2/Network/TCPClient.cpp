#include "TCPClient.h"
#include "TCPServer.h"

ssize_t TCPClient::SendData(const std::vector<uint8_t>& buffer) {
	ssize_t result = send(clientSocket, buffer.data(), buffer.size(), 0);

	if (result < 0) {
		logger.Error(L"send() failed: %i", errno);
	}

	return result;
}

void TCPClient::Disconnect() {
	TCPServer::GetInstance()->DisconnectClient(clientSocket);
}
