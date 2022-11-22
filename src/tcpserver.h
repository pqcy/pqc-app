#pragma once

#include <list>
#include <mutex>
#include <thread>

#include "server.h"
#include "tcpsession.h"

struct TcpServer : public Server {
	int acceptSock_;

	std::mutex m_;
	std::list<TcpSession*> sessions_;
	std::list<std::thread*> threads_;

	bool start(int port) override;
	bool stop() override;

private:
	std::thread* acceptThread_{nullptr};
	void acceptRun();
	void _run(int newsock);
};
