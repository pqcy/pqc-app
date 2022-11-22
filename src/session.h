#pragma once

#include <string>

struct Session {
	std::string error_;

	virtual int read(char* buf, int size) = 0;
	virtual int write(char* buf, int size) = 0;
	virtual bool close() = 0;
};
typedef Session *PSession;
