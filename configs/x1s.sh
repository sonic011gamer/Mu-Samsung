#!/bin/bash

cat ./BootShim/BootShim.bin "./Build/${TARGET_DEVICE}Pkg/${_TARGET_BUILD_MODE}_CLANG38/FV/${TARGET_DEVICE^^}_UEFI.fd" > "./ImageResources/bootpayload.bin"||exit 1

python3 ./ImageResources/mkbootimg.py \
  --kernel ./ImageResources/bootpayload.bin \
  --ramdisk ./ImageResources/ramdisk \
  --dtb "./ImageResources/DTBs/${TARGET_DEVICE}.dtb" \
  --tags_offset 0x00000100 \
  --second_offset 0xf0000000 \
  --ramdisk_offset 0x01000000 \
  --pagesize 2048 \
  --os_version "13.0.0" \
  --os_patch_level "2023-07" \
  --kernel_offset 0x00008000 \
  --header_version 2  \
  --dtb_offset 0x00000000 \
  --cmdline "buildvariant=userdebug" \
  --board "" \
  --base 0x10000000 \
  -o "boot.img" \
  ||_error "\nFailed to create Android Boot Image!\n"

# Compress Boot Image in a tar File for Odin/heimdall Flash
tar -c boot.img -f Mu-${TARGET_DEVICE}.tar||exit 1
mv boot.img Mu-${TARGET_DEVICE}.img||exit 1
