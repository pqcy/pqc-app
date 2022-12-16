Chatting programm using PQC TLS
===

### Prerequisite
```
sudo apt install cmake gcc libtool libssl-dev make ninja-build git
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
cmake -GNinja -DCMAKE_INSTALL_PREFIX=../../openssl/oqs ..
ninja
ninja install
cd ../..
```

### Build openssl
```
cd openssl
./config --debug
make -j
cd ..
```

### Install header and library files
```
cp openssl/lib*.so* pqc-app/lib/
cp -r openssl/include/crypto pqc-app/include/
cp -r openssl/include/openssl pqc-app/include/
cp -r openssl/include/internal pqc-app/include/
cp -r openssl/oqs/include/oqs/ pqc-app/include/
```
### Make and apply a SPHINCS+ PEM File
```
cd openssl
apps/openssl req -x509 -new -newkey sphincssha256128frobust -keyout spx_CA.key -out spx_CA.crt -nodes -subj "/CN=sphincs+ CA" -days 365 -config apps/openssl.cnf
cat spx_CA.key spx_CA.crt >> spx_CA.pem
cp ./spx_CA.pem ../pqc-app/bin/crt/
```
   
# Open a file that chat.pro with Qt creator (Open Project)
File Location - pqc-app/app/chat.pro   
Qt creator's Projects tab - run tab - "Run as a root user" check
