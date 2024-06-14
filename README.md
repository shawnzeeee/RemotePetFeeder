# Remote Pet Feeder

1) After cloning project
```
git submodule init
git submodule update
```
2) Install necessary dependencies
```
sudo apt-get update
sudo apt-get install cmake
sudo apt install nodejs
sudo apt install npm


```
3) Create a toolchain file to compile libwebsockets with arm
```
cd external/libwebsockets
sudo gedit arm-toolchain.cmake
```
Type the following into the toolchain file:
```
# Toolchain for cross-compiling for ARM
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Specify the cross compiler
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

# Where to find the target environment (headers and libraries)
set(CMAKE_FIND_ROOT_PATH $(arm-linux-gnueabihf-gcc --print-sysroot))

# Adjust the default behavior of the FIND_XXX() commands:
# search for programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# search for libraries and headers in the target environment
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(OPENSSL_ROOT_DIR /usr/lib/x86_64-linux-gnu)
set(OPENSSL_CRYPTO_LIBRARY /usr/lib/x86_64-linux-gnu/lib/libcrypto.so)
set(OPENSSL_SSL_LIBRARY /usr/lib/x86_64-linux-gnu/lib/libssl.so)
```
4) Compiling libwebsockets
```
cd external/libwebsockets
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=../arm-toolchain.cmake -DLWS_WITH_SSL=OFF -DLWS_WITHOUT_EXTENSIONS=ON
make
//Go back to repo folder
make
```
5) Running on beaglebone, Do this if object file does not recongnize libwebsockets
```
export LD_LIBRARY_PATH=/mnt/remote/myApps/ENSC351_PROJECT/external/libwebsockets/build/lib:$LD_LIBRARY_PATH
./main

```
