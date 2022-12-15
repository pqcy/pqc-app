#include <chrono>
#include <iostream>
#include <thread>

#include "tlsserver.h"

struct ChatServer : public TlsServer {
protected:
	void run(Session* session) override {
		std::puts("connected");
        char buf[512];
		while (true) {
			int res = session->read(buf, 256);
			if (res <= 0) break;
			buf[res] = '\0';
			std::puts(buf);
			sessions_.lock();
            for (TlsSession* sessionList: sessions_)
                if (session != sessionList)
                    sessionList->write(buf, res);
			sessions_.unlock();
		}
		std::puts("disconnected");
	}
};

struct Param {
    int port;
    std::string pem;

	bool parse(int argc, char** argv) {
        if (argc != 3) return false;
        port = std::stoi(argv[1]);
        pem = argv[2];
		return true;
	}

	static void usage() {
        printf("syntax : tlsserver-test <port> <pem file name>\n");
        printf("sample : tlsserver-test 12345 crt/spx_CA.pem\n");
	}
};

int main(int argc, char* argv[]) {
	ChatServer cs;

	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
    }
    cs.pemFileName_ = param.pem;

    if (!cs.start(param.port)) {
		std::cerr << cs.error_ << std::endl;
		return -1;
	}

	while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	cs.stop();
}
