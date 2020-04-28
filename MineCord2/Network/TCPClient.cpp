#include "TCPClient.h"
#include "TCPServer.h"

void TCPClient::SendData(const std::vector<uint8_t>& buffer) {
	std::lock_guard<std::mutex> lock(_mutex);

	buffers.sendFeedBytes += buffer.size();

	for (const auto byte : buffer) {
		buffers.sendBuffer.push_back(byte);
	}
}

void TCPClient::SendChunk() {
	assert(buffers.sendFeedBytes >= buffers.sendBuffer.size());

	std::vector<uint8_t> tmpBuffer;

	if (buffers.sendFeedBytes > SEND_BUFFER_SIZE) {
		for (int i = 0; i < SEND_BUFFER_SIZE; i++) {
			tmpBuffer.push_back(buffers.sendBuffer[i]);
		}

		buffers.sendBuffer.erase(
			buffers.sendBuffer.begin(),
			buffers.sendBuffer.begin() + SEND_BUFFER_SIZE
		);

		buffers.sendFeedBytes -= SEND_BUFFER_SIZE;
	} else {
		tmpBuffer = buffers.sendBuffer;
	}

	ssize_t result = send(clientSocket, tmpBuffer.data(), tmpBuffer.size(), MSG_NOSIGNAL);

	if (result < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
		TCPServer::GetInstance()->ModifyEpollFD(clientSocket, EPOLLOUT);
	} else {
		buffers.sendBuffer.erase(buffers.sendBuffer.begin(), buffers.sendBuffer.begin() + result);
		buffers.sendFeedBytes -= result;
	}
}

void TCPClient::Disconnect() {
	TCPServer::GetInstance()->DisconnectClient(clientSocket);
}
