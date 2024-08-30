#!/bin/bash

# Variables
IOS_DEPLOYMENT_TARGET="14.0"
MACOS_DEPLOYMENT_TARGET="11.0"
ANDROID_PLATFORM="android-21"
FRAMEWORK_NAME="Test"

# Paths
ANDROID_NDK="~/Library/Android/sdk/ndk/26.1.10909125/build/cmake"

# Function to build and install for a specific platform
build_platform() {
    platform=$1
    build_dir=$2
    cmake_args=$3
    
    echo "Building for $platform..."
    cmake -B $build_dir $cmake_args
    cmake --build $build_dir --config Release  
    cmake --install $build_dir --config Release
}

# Function to copy the Modules folder
copy_modules() {
    build_dir=$1
    output_dir="${build_dir}/${FRAMEWORK_NAME}.framework"
    
    if [ -d "$output_dir" ]; then
        echo "Copying Modules to $output_dir..."
        mkdir -p "$output_dir/Modules"
        cp -r module.modulemap "$output_dir/Modules/"
    else
        echo "Output directory $output_dir not found!"
    fi
}

# iPhoneSimulator (arm64)
build_platform "iPhoneSimulator" "build/iphonesimulator" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DCMAKE_OSX_ARCHITECTURES=arm64"

copy_modules "build/iphonesimulator/Release-iphonesimulator"

# iPhoneOS (arm64)
build_platform "iPhoneOS" "build/iphoneos" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_OSX_ARCHITECTURES=arm64"

copy_modules "build/iphoneos/Release-iphoneos"

# macOS (arm64 or x86_64)
build_platform "macOS" "build/macos" \
    "-GXcode -DCMAKE_SYSTEM_NAME=Darwin \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$MACOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_ARCHITECTURES=$(uname -m)"

copy_modules "build/macos/Release"

# Android (arm64-v8a)
build_platform "Android" "build/android" \
    "-DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=$ANDROID_PLATFORM"

# Linux (x86_64)
# build_platform "Linux" "build/linux" \
#     "-DCMAKE_SYSTEM_NAME=Linux"

# Windows (x86_64)
# build_platform "Windows" "build/windows" \
#     "-DCMAKE_SYSTEM_NAME=Windows"

# Creating XCFramework
echo "Creating XCFramework..."
xcodebuild -create-xcframework \
    -framework build/iphonesimulator/Release-iphonesimulator/${FRAMEWORK_NAME}.framework \
    -framework build/iphoneos/Release-iphoneos/${FRAMEWORK_NAME}.framework \
    -framework build/macos/Release/${FRAMEWORK_NAME}.framework \
    -output ${FRAMEWORK_NAME}.xcframework

echo "Build and packaging complete."
