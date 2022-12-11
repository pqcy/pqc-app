#pragma once

#include <string>
#include "ip.h"

struct Client {
	std::string error_;

    virtual bool connect(Ip ip, int port) = 0;
};
