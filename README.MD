this is a Chatting programm using PQC TLS
<br><br>

before PQC TLS build <br>
$ sudo apt install cmake gcc libtool libssl-dev make ninja-build git <br>
$ git clone https://github.com/open-quantum-safe/openssl.git
<br><br>

$ git clone --branch main https://github.com/open-quantum-safe/liboqs.git <br>
$ cd liboqs <br>
$ mkdir build && cd build <br>
$ cmake -GNinja -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=../../openssl/oqs .. <br>
$ ninja <br>
$ ninja install
<br><br>
$ cd ../../openssl
$ ./config --debug <br>
$ make -j <br>
$ cp ./libssl.so.1.1 ../pqc-app/lib/ <br>
$ cp ./libcrypto.so.1.1 ../pqc-app/lib/ <br>
$ cp ./oqs/lib/liboqs.so.2 ../pqc-app/lib/ <br>
$ cp -r ./include/crypto ../pqc-app/include/ <br>
$ cp -r ./include/openssl ../pqc-app/include/ <br>
$ cp -r ./include/internal ../pqc-app/include/ <br>
$ cp -r ./oqs/include/oqs/ ../pqc-app/include/

