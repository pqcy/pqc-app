Chatting programm using PQC TLS
===

### Prerequisite
```
$ sudo apt install cmake gcc libtool libssl-dev make ninja-build git
```

### Git clone
```
git clone --branch main https://github.com/open-quantum-safe/liboqs.git
git clone https://github.com/open-quantum-safe/openssl.git
git clone git@github.com:pqcy/pqc-app.git
```

### Build oqs
```
cd liboqs
mkdir build && cd build
cmake -GNinja -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=../../openssl/oqs ..
ninja
ninja install
```

### Build openssl
```
cd ../../openssl
./config --debug
make -j
```

### Install header and library files
```
cp ./libssl.so.1.1 ../pqc-app/lib/
cp ./libcrypto.so.1.1 ../pqc-app/lib/
cp ./oqs/lib/liboqs.so.2 ../pqc-app/lib/
cp -r ./include/crypto ../pqc-app/include/
cp -r ./include/openssl ../pqc-app/include/
cp -r ./include/internal ../pqc-app/include/
cp -r ./oqs/include/oqs/ ../pqc-app/include/
```