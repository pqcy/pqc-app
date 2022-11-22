#pragma once

#include "session.h"
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <cassert>

struct TlsSession : public Session {
	int sock_;
	SSL* ssl_;

	TlsSession(int sock = 0, SSL* ssl = 0);
	virtual ~TlsSession();

	int read(char* buf, int size) override;
	int write(char* buf, int size) override;
	bool close() override;
};
typedef TlsSession *PTlsSession;
