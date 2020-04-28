#include "TCPServer.h"
#include "MinecraftNetworkClient.h"

TCPServer* TCPServer::instance;

void TCPServer::EpollLoop() {
	while (true) {
		int readySocketsCount = epoll_wait(epollFD, epollEvents, MAX_CLIENTS + 1, -1);

		for (int i = 0; i < readySocketsCount; i++) {
			const auto event = &epollEvents[i];

			if (event->events & EPOLLERR) {
				logger.Error(L"EPOLL event error on socket: %i | %i", event->data.fd, errno);
				DisconnectClient(event->data.fd);
				continue;
			}

			if (event->data.fd == serverSocket) {
				ProcessServerEpoll();
			} else {
				ProcessClientEpoll(event);
			}
		}
	}
}

void TCPServer::DisconnectClient(int fd) {
	const auto client = clients[fd];
	assert(client);
	
	logger.Info(L"Disconnecting %ls ...", NetworkUtils::FormatIPv4(client->GetIPv4()).c_str());

	close(fd);
	delete client;
}

void TCPServer::SetBuffersCapacity(int socket, size_t sendBufSize, size_t recvBufSize) {
	int result = setsockopt(socket, SOL_SOCKET, SO_SNDBUF, &sendBufSize, sizeof(sendBufSize));
	if (result < 0) {
		logger.Error(L"setsockopt for SO_SNDBUF failed: %i", errno);
		exit(1);
	}

	result = setsockopt(socket, SOL_SOCKET, SO_RCVBUF, &recvBufSize, sizeof(recvBufSize));
	if (result < 0) {
		logger.Error(L"setsockopt for SO_RCVBUF failed: %i", errno);
		exit(1);
	}
}

void TCPServer::InitializeEpoll() {
	epollFD = epoll_create1(0);

	if (epollFD < 0) {
		logger.Error(L"epoll_create() failed: %i", errno);
		exit(1);
	}
}

void TCPServer::ProcessServerEpoll() {
	struct sockaddr_in clientAddress;
	socklen_t clientAddressSize = sizeof(clientAddress);

	int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);

	if (clientSocket < 0 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
		return;
	}

	if (clientSocket < 0) {
		logger.Error(L"accept() failed: ", errno);
		return;
	}

	DisableSocketBlocking(clientSocket);
	SetBuffersCapacity(clientSocket, SEND_BUFFER_SIZE, RECV_BUFFER_SIZE);

	AddEpollFD(clientSocket, EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLERR);

	std::wstring ip = NetworkUtils::FormatIPv4(clientAddress.sin_addr.s_addr);
	logger.Info(L"New connection from %ls:%i", ip.c_str(), clientAddress.sin_port);

	clients[clientSocket] = new MinecraftNetworkClient(clientSocket, clientAddress.sin_addr.s_addr);
}

void TCPServer::ProcessClientEpoll(epoll_event* pEvent) {
	if (pEvent->events & EPOLLIN) {
		uint8_t buf[RECV_BUFFER_SIZE];
		ssize_t numBytesRead = recv(pEvent->data.fd, buf, sizeof(buf), 0);

		if (numBytesRead < -1) {
			if (errno == EAGAIN) {
				return;
			}

			logger.Error(L"recv() failed: %i", errno);

			return;
		}

		if (numBytesRead == 0) {
			DisconnectClient(pEvent->data.fd);
			return;
		}

		std::vector<uint8_t> resizedBuf;
		resizedBuf.resize(numBytesRead);
		memcpy(resizedBuf.data(), buf, numBytesRead);

		clients[pEvent->data.fd]->OnChunk(resizedBuf);
	}

	if (pEvent->events & EPOLLOUT) {
		clients[pEvent->data.fd]->SendChunk();
	}
}

TCPServer::TCPServer() {
	logger.SetTag(L"TCP Server");
}

void TCPServer::Start(uint16_t port) {
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket < 0) {
		logger.Error(L"socket() failed: %i", errno);
		exit(1);
	}

	DisableSocketBlocking(serverSocket);

	bool enableValue = 1;
	int result = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &enableValue, sizeof(int));

	if (result < 0) {
		logger.Error(L"setsockopt() failed: %i", result);
		exit(1);
	}

	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	result = bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
	if (result < 0) {
		logger.Error(L"bind() failed: %i", result);
		exit(1);
	}

	result = listen(serverSocket, MAX_CLIENTS);
	if (result < 0) {
		logger.Error(L"listen() failed: %i", result);
		exit(1);
	}

	InitializeEpoll();

	AddEpollFD(serverSocket, EPOLLIN | EPOLLET);

	epollWorker = std::thread(EpollThreadEntry);
	epollWorker.join();
}
