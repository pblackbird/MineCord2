#include "MinecraftNetworkClient.h"
#include "../Packets/BaseNetPacket.h"
#include "../States/StatesBindings.h"
#include "TCPServer.h"

MinecraftNetworkClient::MinecraftNetworkClient(int socket, uint32_t ipv4) : TCPClient(socket, ipv4) {
	buffers.recvFeedBytes = 0;
}

MinecraftNetworkClient::~MinecraftNetworkClient() {

}

void MinecraftNetworkClient::UpdateRecvBuffer(const std::vector<uint8_t>& buffer) {
	buffers.recvBuffer.clear();
	buffers.recvBuffer.resize(buffer.size());
	std::copy(buffer.begin(), buffer.end(), buffers.recvBuffer.begin());

	buffers.recvFeedBytes = 0;

	BaseNetPacket pkt;
	pkt.Parse(buffers.recvBuffer);

	buffers.recvFeedBytes = pkt.length + pkt.packetIdLen;
}

void MinecraftNetworkClient::OnChunk(const std::vector<uint8_t>& buffer) {
	if (state == TcpRawState::IDLE) {
		UpdateRecvBuffer(buffer);

		state = TcpRawState::WAITING_FOR_MESSAGE;
	}

	if (buffer.size() < buffers.recvFeedBytes) {
		buffers.recvBuffer.insert(buffers.recvBuffer.end(), buffer.begin(), buffer.end());
		buffers.recvFeedBytes -= buffer.size();
	}
	
	if (buffer.size() > buffers.recvFeedBytes) {
		std::vector<uint8_t> tmpBuffer;

		for (size_t i = 0; i < buffers.recvFeedBytes; i++) {
			tmpBuffer.push_back(buffers.recvBuffer[i]);
		}

		buffers.recvBuffer.erase(
			buffers.recvBuffer.begin(),
			buffers.recvBuffer.begin() + buffers.recvFeedBytes
		);

		OnMessageReceived(tmpBuffer);

		state = TcpRawState::IDLE;
		OnChunk(std::vector<uint8_t>(buffers.recvBuffer));
	}

	if(buffer.size() == buffers.recvFeedBytes) {
		OnMessageReceived(buffers.recvBuffer);
		state = TcpRawState::IDLE;
	}
}

void MinecraftNetworkClient::OnMessageReceived(std::vector<uint8_t>& buffer) {
	BaseNetPacket pkt;
	pkt.Parse(buffer);

	const auto state = StatesBindings::GetInstance()->GetBinding(clientState);
	state->Process(this, pkt);
}
