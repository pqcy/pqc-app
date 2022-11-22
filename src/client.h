#pragma once

#include <string>

struct Client {
	std::string error_;

	virtual bool connect(std::string, int port) = 0;
};
