#include "tcpclient.h"

bool TcpClient::connect(std::string host, int port) {
	sock_ = ::socket(AF_INET, SOCK_STREAM, 0);
	if (sock_ == -1) {
		error_ = strerror(errno);
		return false;
	}

	struct in_addr ip;
	int res = inet_pton(AF_INET, host.data(), &ip);
	switch (res) {
		case 1: break;
		case 0: fprintf(stderr, "not a valid network address\n"); return false;
		case -1: perror("inet_pton"); return false;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr = ip;
	memset(&addr.sin_zero, 0, sizeof(addr.sin_zero));

	res = ::connect(sock_, (struct sockaddr *)&addr, sizeof(addr));
	if (res == -1) {
		error_ = strerror(errno);
		return false;
	}

	return true;
}
