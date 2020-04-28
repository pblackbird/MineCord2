#pragma once

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <strings.h>
#include <cstdint>
#include <thread>
#include <vector>
#include <string.h>
#include <cassert>

#include "NetworkUtils.h"
#include "../Logger.h"
#include "NetConfig.h"
#include "TCPClient.h"

class TCPServer {
private:
	static TCPServer* instance;

	int serverSocket, epollFD;
	bool isRunning = false;

	std::thread epollWorker;
	Logger logger;

	TCPClient* clients[MAX_CLIENTS];
	epoll_event epollEvents[MAX_CLIENTS + 1]; // +1 to include server's socket FD

public:
	static inline TCPServer* GetInstance() {
		if (instance == nullptr) {
			instance = new TCPServer();
		}

		return instance;
	}

	inline void ModifyEpollFD(int fd, int events) {
		struct epoll_event event;
		event.data.fd = fd;
		event.events = events | EPOLLET;

		int result = epoll_ctl(epollFD, EPOLL_CTL_MOD, fd, &event);

		if (result < 0) {
			logger.Error(L"epoll_ctl() with EPOLL_CTL_MOD failed: %i", fd);
		}
	}

private:
	static void EpollThreadEntry() {
		TCPServer::GetInstance()->EpollLoop();
	}

	inline void AddEpollFD(int fd, int events) {
		struct epoll_event event;
		event.data.fd = fd;
		event.events = events;

		int result = epoll_ctl(epollFD, EPOLL_CTL_ADD, fd, &event);

		if (result < 0) {
			logger.Error(L"epoll_ctl() with EPOLL_CTL_ADD failed: %i", fd);
		}
	}

	inline void RemoveEpollFD(int fd) {
		int result = epoll_ctl(epollFD, EPOLL_CTL_DEL, fd, NULL);

		if (result < 0) {
			logger.Error(L"epoll_ctl() with EPOLL_CTL_DEL failed: %i", fd);
		}
	}

	inline void DisableSocketBlocking(int socket) {
		fcntl(socket, F_SETFL, fcntl(socket, F_GETFD, 0) | O_NONBLOCK);
	}

	void SetBuffersCapacity(int socket, size_t sendBufSize, size_t recvBufSize);

	void InitializeEpoll();
	void ProcessServerEpoll();
	void ProcessClientEpoll(epoll_event* pEvent);

public:
	TCPServer();

	void Start(uint16_t port);
	void EpollLoop();

	void DisconnectClient(int fd);
};

