#!/bin/bash

# Variables
FRAMEWORK_NAME="Test"

IOS_DEPLOYMENT_TARGET="14.0"
MACOS_DEPLOYMENT_TARGET="11.0"

ANDROID_PLATFORM="android-21"

# Paths
ANDROID_NDK="~/Library/Android/sdk/ndk/26.1.10909125/build/cmake"
MODULEMAP_PATH="./module.modulemap"

rm -rf build
rm -rf "${FRAMEWORK_NAME}.xcframework"

# Function to build and install for a specific platform
build_platform() {
    build_dir=$1
    cmake_args=$2

    cmake -B $build_dir $cmake_args
    cmake --build $build_dir --config Release
    cmake --install $build_dir --config Release
}

# Function to copy the Modules folder
copy_modules() {
    build_dir=$1
    output_dir="${build_dir}/${FRAMEWORK_NAME}.framework"

    if [ -d "$output_dir" ]; then
        mkdir -p "$output_dir/Modules"
        cp -r module.modulemap "$output_dir/Modules/"
    fi
}

# iPhoneSimulator
sim_platform="iphonesimulator"
build_platform "build/$sim_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DCMAKE_OSX_ARCHITECTURES=x86_64;arm64"
copy_modules "build/$sim_platform/Release-$sim_platform"

# iPhoneOS
iphone_platform="iphoneos"
build_platform "build/$iphone_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_OSX_ARCHITECTURES=arm64"
copy_modules "build/$iphone_platform/Release-$iphone_platform"

# macOS
macos_platform="macos"
build_platform "build/$macos_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=Darwin \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$MACOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_ARCHITECTURES=$(uname -m)"

copy_modules "build/$macos_platform/Release"

# Creating XCFramework
xcodebuild -create-xcframework \
  -framework build/${iphone_platform}/Release-${iphone_platform}/${FRAMEWORK_NAME}.framework \
  -framework build/${sim_platform}/Release-${sim_platform}/${FRAMEWORK_NAME}.framework \
  -framework build/${macos_platform}/Release/${FRAMEWORK_NAME}.framework \
  -output ${FRAMEWORK_NAME}.xcframework

# # Android (arm64-v8a), skip copying module.modulemap
build_platform "build/android" \
    "-DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=$ANDROID_PLATFORM"
