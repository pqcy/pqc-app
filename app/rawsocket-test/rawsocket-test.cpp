#include <iostream>
#include "rawsocket.h"

char ipPacket[] = "\x45\x00" \
"\x00\x54\x91\xb2\x40\x00\x40\x01\x8c\xd8\x0a\x00\x02\x0f\x08\x08" \
"\x08\x08\x08\x00\x9b\x73\x00\x01\x00\x01\xfe\x01\x8a\x63\x00\x00" \
"\x00\x00\x0d\x52\x08\x00\x00\x00\x00\x00\x10\x11\x12\x13\x14\x15" \
"\x16\x17\x18\x19\x1a\x1b\x1c\x1d\x1e\x1f\x20\x21\x22\x23\x24\x25" \
"\x26\x27\x28\x29\x2a\x2b\x2c\x2d\x2e\x2f\x30\x31\x32\x33\x34\x35" \
"\x36\x37";

int main()
{
   RawSocket raw;

   if (!raw.open())
       printf("%s", raw.error_.c_str());
   if (!raw.write(ipPacket, sizeof(ipPacket) - 1))
       printf("%s", raw.error_.c_str());
   raw.close();
}
