cmake -B build -G Xcode -DCMAKE_TOOLCHAIN_FILE=./toolchain/ios.toolchain.cmake -DPLATFORM=OS64COMBINED
cmake --build build --config Release
cmake --install build --config Release