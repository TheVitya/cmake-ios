#!/bin/bash

MODULE_NAME="AppCore"
FRAMEWORK_NAME="AppCoreFramework"
ROOT_PATH=$(git rev-parse --show-toplevel)

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        BIN_PATH=$ROOT_PATH/.boilerplate/bin/boilerplate_linux_arm64
elif [[ "$OSTYPE" == "darwin"* ]]; then
        BIN_PATH=$ROOT_PATH/.boilerplate/bin/boilerplate_darwin_arm64
fi

$BIN_PATH \
  --template-url $ROOT_PATH/.boilerplate/module \
  --output-folder $ROOT_PATH/packages/${MODULE_NAME}/ \
  --non-interactive \
  --var ModuleName="$MODULE_NAME" \
  --var FrameworkName="$FRAMEWORK_NAME"
