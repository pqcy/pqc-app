#include <iostream>

#include "netinfo.h"

using namespace std;

struct Param {
	string intfName_;
	bool parse(int argc, char** argv) {
		if (argc != 2)
			return false;
		intfName_ = argv[1];
		return true;
	}

	static void usage() {
		printf("syntax : netinfo-test <interface name>\n");
		printf("sample : netinfo-test wlan0\n");
	}
};

int main(int argc, char* argv[]) {
	Param param;
	if (!param.parse(argc, argv)) {
		Param::usage();
		return -1;
	}

	NetInfo ni;
	if (!ni.init(param.intfName_)) {
		fprintf(stderr, "ni.init return false\n");
		return -1;
	}

	printf("mac=%s\n", std::string(ni.mac_).data());
	printf("ip=%s\n", std::string(ni.ip_).data());

	return 0;
}
