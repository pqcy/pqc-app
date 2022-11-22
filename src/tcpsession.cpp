#include "tcpsession.h"

TcpSession::TcpSession(int sock) {
	sock_ = sock;
}

int TcpSession::read(char* buf, int size) {
	// TO DO
}

int TcpSession::write(char* buf, int size) {
	// TO DO
}

bool TcpSession::close() {
	// TO DO
}
