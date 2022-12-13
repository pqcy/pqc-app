this is a Chatting programm using PQC TLS

before PQC TLS build
$ sudo apt install cmake gcc libtool libssl-dev make ninja-build git
$ git clone https://github.com/open-quantum-safe/openssl.git

$ git clone --branch main https://github.com/open-quantum-safe/liboqs.git
$ cd liboqs
$ mkdir build && cd build
$ cmake -GNinja -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=<OPENSSL_DIR>/oqs ..
$ ninja
$ ninja install

go to <OPENSSL_DIR>
$ ./config --debug
$  make -j

$ cp <OPENSSL_DIR>/libssl.so.1.1 pqc-app/lib/
$ cp <OPENSSL_DIR>/libcrypto.so.1.1 pqc-app/lib/
$ cp <OPENSSL_DIR>/oqs/lib/liboqs.so pqc-app/lib/
$ cp -r <OPENSSL_DIR>/include/ pqc-app/include/
$ cp -r <OPENSSL_DIR>/oqs/include/ pqc-app/include/

