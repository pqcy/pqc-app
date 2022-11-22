#include <iostream>
#include <thread>

#include "tcpclient.h"

struct Param {
	std::string host_;
	int port_;

	bool parse(int argc, char** argv) {
		if (argc != 3) return false;
		host_ = argv[1];
		port_ = std::stoi(argv[2]);
		return true;
	}

	static void usage() {
		printf("syntax : tcpclient-test <host> <port>\n");
		printf("sample : tcpclient-test <host> <port>\n");
	}
};

void readAndPrint(Session* session) {
	char buf[256];
	while (true) {
		int res = session->read(buf, 256);
		if (res <= 0) break;
		buf[res] = '\0';
		std::puts(buf);
	}
}

void inputAndWrite(Session* session) {
	while (true) {
		std::string msg;
		std::getline(std::cin, msg);
		if (msg == "quit") break;
		int writeLen = session->write(msg.data(), msg.size());
		if (writeLen == -1) break;
	}
}

int main(int argc, char* argv[]) {
	TcpClient tc;

	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
	}

	if (!tc.connect(param.host_, param.port_)) {
		std::cerr << tc.error_ << std::endl;
		return -1;
	}

	std::thread* thread1 = new std::thread(&readAndPrint, &tc);
	std::thread* thread2 = new std::thread(&inputAndWrite, &tc);

	thread1->join();
	thread2->join();

	tc.close();
}
