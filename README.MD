Chatting programm using PQC TLS
===
### Comment
This programm need OpenSSL 3.x, liboqs, oqs-provider
### Prerequisite
```
sudo apt install cmake gcc libtool libssl-dev make ninja-build git qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools python3-pytest python3-pytest-xdist unzip xsltproc doxygen graphviz python3-yaml valgrind
```

### Git clone
```
git clone --branch main https://github.com/open-quantum-safe/liboqs.git
git clone https://github.com/open-quantum-safe/oqs-provider.git
https://github.com/openssl/openssl.git
git clone git@github.com:pqcy/pqc-app.git
```

### Build oqs
```
cd liboqs
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug -GNinja ..
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
### using oqs-provider
```
cd oqs-provider
env OPENSSL_ROOT_DIR="../openssl" \
    liboqs_DIR="../liboqs" \
    MAKE_PARAMS="-j" \
    CMAKE_PARAMS="-DCMAKE_BUILD_TYPE=Debug" \
    bash scripts/fullbuild.sh
cd ..
```

### Configurate Openssl-Provider
```
cd openssl
cat <<EOL > ./ssl/openssl.cnf
openssl_conf = openssl_init

[openssl_init]
providers = provider_sect

[provider_sect]
default = default
oqsprovider = oqsprovider

EOL

export OPENSSL_CONF=$(pwd)/ssl/openssl.cnf
export OPENSSL_MODULES=$(pwd)/ossl-modules
```

### Install header and library files
```
cp openssl/lib*.so* pqc-app/lib/
cp -r openssl/ossl-modules pqc-app/lib/
cp -r openssl/include/crypto pqc-app/include/
cp -r openssl/include/openssl pqc-app/include/
cp -r openssl/include/internal pqc-app/include/
```
### Make and apply a SPHINCS+ PEM File
```
cd openssl
apps/openssl req -x509 -new -newkey sphincssha256128frobust -keyout spx_CA.key -out spx_CA.crt -nodes -subj "/CN=sphincs+ CA" -days 365 -config apps/openssl.cnf
cat spx_CA.key spx_CA.crt >> spx_CA.pem
cp ./spx_CA.pem ../pqc-app/bin/crt/
```
---
###  Build
```
cd pqc-app
export LD_LIBRARY_PATH=$PWD/lib
cd app
qmake
make -j
```

### Client Run
```
cd pqc-app/
export LD_LIBRARY_PATH=$PWD/lib
cd bin/
./chat
```

### Server Run
```
cd pqc-app/
export LD_LIBRARY_PATH=$PWD/lib
cd bin/
./tlsserver-test 12345 crt/spx_CA.pem
```

# Open a file that chat.pro with Qt creator (Open Project)
File Location - pqc-app/app/chat.pro   
Qt creator's Projects tab - run tab - "Run as a root user" check   
Now you can run the program
