this is a Chatting programm using PQC TLS
<br><br>

before PQC TLS build <br>
$ sudo apt install cmake gcc libtool libssl-dev make ninja-build git <br>
$ git clone https://github.com/open-quantum-safe/openssl.git
<br><br>

$ git clone --branch main https://github.com/open-quantum-safe/liboqs.git <br>
$ cd liboqs <br>
$ mkdir build && cd build <br>
$ cmake -GNinja -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=<OPENSSL_DIR>/oqs .. <br>
$ ninja <br>
$ ninja install

<br><br>

go to <OPENSSL_DIR> <br>
$ ./config --debug <br>
$  make -j
<br> <br>
$ cp <OPENSSL_DIR>/libssl.so.1.1 pqc-app/lib/ <br>
$ cp <OPENSSL_DIR>/libcrypto.so.1.1 pqc-app/lib/ <br>
$ cp <OPENSSL_DIR>/oqs/lib/liboqs.so pqc-app/lib/ <br>
$ cp -r <OPENSSL_DIR>/include/ pqc-app/include/ <br>
$ cp -r <OPENSSL_DIR>/oqs/include/ pqc-app/include/

