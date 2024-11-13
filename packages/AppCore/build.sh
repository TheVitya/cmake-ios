#!/bin/bash

# Variables
FRAMEWORK_NAME="AppCoreFramework"
EXECUTABLE_NAME="AppCore"

IOS_DEPLOYMENT_TARGET="14.0"
MACOS_DEPLOYMENT_TARGET="11.0"

ANDROID_PLATFORM="android-21"

# Paths
ANDROID_NDK="~/Library/Android/sdk/ndk/26.1.10909125/build/cmake"
MODULEMAP_PATH="./module.modulemap"
JNI_LIBS_PATH="./android/src/main/jniLibs"

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

build_executable() {
    build_dir="build/executable"
    cmake_args="-DCMAKE_BUILD_TYPE=Release \
      -DBUILD_TARGET=EXECUTABLE \
      -DMODULE_NAME=$FRAMEWORK_NAME"

    cmake -B $build_dir $cmake_args
    cmake --build $build_dir --config Release
}

copy_android_libs() {
    build_dir=$1
    type=$2
    if [ -d "$build_dir" ]; then
        mkdir -p "$JNI_LIBS_PATH/$type"  # Example for arm64-v8a; repeat for other ABIs as needed
        cp -r "$build_dir"/*.so "$JNI_LIBS_PATH/$type/"
    fi
}

# iPhoneSimulator
sim_platform="iphonesimulator"
build_platform "build/$sim_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DMODULE_NAME=$FRAMEWORK_NAME \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphonesimulator \
    -DCMAKE_OSX_ARCHITECTURES=x86_64;arm64"
copy_modules "build/$sim_platform/Release-$sim_platform"

# iPhoneOS
iphone_platform="iphoneos"
build_platform "build/$iphone_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=iOS \
    -DMODULE_NAME=$FRAMEWORK_NAME \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$IOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_SYSROOT=iphoneos \
    -DCMAKE_OSX_ARCHITECTURES=arm64"
copy_modules "build/$iphone_platform/Release-$iphone_platform"

# macOS
macos_platform="macos"
build_platform "build/$macos_platform" \
    "-GXcode -DCMAKE_SYSTEM_NAME=Darwin \
    -DMODULE_NAME=$FRAMEWORK_NAME \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=$MACOS_DEPLOYMENT_TARGET \
    -DCMAKE_OSX_ARCHITECTURES=$(uname -m)"
copy_modules "build/$macos_platform/Release"

# Creating XCFramework
xcodebuild -create-xcframework \
  -framework build/${iphone_platform}/Release-${iphone_platform}/${FRAMEWORK_NAME}.framework \
  -framework build/${sim_platform}/Release-${sim_platform}/${FRAMEWORK_NAME}.framework \
  -framework build/${macos_platform}/Release/${FRAMEWORK_NAME}.framework \
  -output ${FRAMEWORK_NAME}.xcframework

# Android
android_build_dir="build/android"
type=arm64-v8a
build_platform "$android_build_dir" \
    "-DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/android.toolchain.cmake \
    -DMODULE_NAME=$EXECUTABLE_NAME \
    -DANDROID_ABI=$type \
    -DANDROID_PLATFORM=$ANDROID_PLATFORM"
copy_android_libs "$android_build_dir" $type

# Android
android_build_dir="build/android"
type=x86_64
build_platform "$android_build_dir" \
    "-DCMAKE_TOOLCHAIN_FILE=${ANDROID_NDK}/android.toolchain.cmake \
    -DMODULE_NAME=$EXECUTABLE_NAME \
    -DANDROID_ABI=$type \
    -DANDROID_PLATFORM=$ANDROID_PLATFORM"
copy_android_libs "$android_build_dir" $type

build_executable
