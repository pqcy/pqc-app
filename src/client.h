#pragma once

#include <string>

struct Client {
	virtual bool connect(std::string, int port) = 0;
};
