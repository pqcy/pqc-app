#include <chrono>
#include <iostream>
#include <thread>

#include "tcpserver.h"

struct ChatServer : public TcpServer {
protected:
	void run(Session* session) override {
		// TO DO
	}
};

struct Param {
	int port_;

	bool parse(int argc, char** argv) {
		if (argc != 2) return false;
		port_ = std::stoi(argv[1]);
		return true;
	}

	static void usage() {
		printf("syntax : tcpserver-test <port>\n");
		printf("sample : tcpserver-test <port>\n");
	}
};

int main(int argc, char* argv[]) {
	ChatServer cs;

	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
	}

	if (!cs.start(param.port_)) {
		std::cerr << cs.error_ << std::endl;
		return -1;
	}

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	cs.stop();
}
