#include "TCPClient.h"
#include "TCPServer.h"

void TCPClient::CheckFD() {
	int events = EPOLLET;

	if (buffers.recvFeedBytes > 0) {
		events |= EPOLLIN;
	}

	if (buffers.sendFeedBytes > 0) {
		events |= EPOLLOUT;
	}

	TCPServer::GetInstance()->ModifyEpollFD(clientSocket, events);
}

void TCPClient::SendData(const std::vector<uint8_t>& buffer) {
	std::lock_guard<std::mutex> lock(_mutex);

	buffers.sendFeedBytes += buffer.size();

	for (const auto byte : buffer) {
		buffers.sendBuffer.push_back(byte);
	}

	CheckFD();
}

void TCPClient::SendChunk() {
	std::lock_guard<std::mutex> lock(_mutex);

	assert(buffers.sendFeedBytes >= buffers.sendBuffer.size());

	std::vector<uint8_t> tmpBuffer;

	if (buffers.sendFeedBytes > SEND_BUFFER_SIZE) {
		for (int i = 0; i < (int)buffers.sendFeedBytes; i++) {
			tmpBuffer.push_back(buffers.sendBuffer[i]);
		}
	} else {
		tmpBuffer = buffers.sendBuffer;
	}

	if (tmpBuffer.size() == 0) {
		return;
	}

	ssize_t result = send(clientSocket, tmpBuffer.data(), tmpBuffer.size(), MSG_NOSIGNAL);

	buffers.sendBuffer.erase(buffers.sendBuffer.begin(), buffers.sendBuffer.begin() + result);
	buffers.sendFeedBytes -= result;

	if (result < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
		CheckFD();
	}
}

void TCPClient::Disconnect() {
	TCPServer::GetInstance()->DisconnectClient(clientSocket);
}
