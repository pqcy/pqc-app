#include <iostream>
#include <thread>
#include <netinet/in.h>
#include "tcpclient.h"

struct Param {
    Ip ip_;
	int port_;

	bool parse(int argc, char** argv) {
		if (argc != 3) return false;
        ip_ = Ip(inet_addr(argv[1]));
		port_ = std::stoi(argv[2]);
		return true;
	}

	static void usage() {
		printf("syntax : tcpclient-test <host> <port>\n");
		printf("sample : tcpclient-test <host> <port>\n");
	}
};

void readAndPrint(Session* session) {
	std::puts("connected");
	char buf[256];
	while (true) {
		int res = session->read(buf, 256);
		if (res <= 0) break;
		buf[res] = '\0';
		std::puts(buf);
	}
	std::puts("disconnected");
    exit(0);
}

int main(int argc, char* argv[]) {
	TcpClient tc;

	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
	}

    if (!tc.connect(param.ip_, param.port_)) {
		std::cerr << tc.error_ << std::endl;
		return -1;
    }

	std::thread thread(&readAndPrint, &tc);

	while (true) {
		std::string msg;
		std::getline(std::cin, msg);
		int writeLen = tc.write(msg.data(), msg.size());
		if (writeLen == -1) break;
	}
	tc.close();
}
