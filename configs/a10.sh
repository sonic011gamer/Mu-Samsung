#!/bin/bash

cat ./BootShim/AARCH64/BootShim.bin "./Build/a10Pkg-AARCH64/${_TARGET_BUILD_MODE}_CLANG38/FV/A10_UEFI.fd" > "./ImageResources/bootpayload.bin"||exit 1

python3 ./ImageResources/mkbootimg.py \
  --kernel ./ImageResources/bootpayload.bin \
  --ramdisk ./ImageResources/ramdisk \
  --kernel_offset 0x00000000 \
  --ramdisk_offset 0x01000000 \
  --tags_offset 0x00000100 \
  --os_version 11.0.0 \
  --os_patch_level "$(date '+%Y-%m')" \
  --header_version 1 \
  -o "boot.img" \
  ||_error "\nFailed to create Android Boot Image!\n"

# Compress Boot Image in a tar File for Odin/heimdall Flash
tar -c boot.img -f Mu-a10.tar||exit 1
mv boot.img Mu-a10.img||exit 1