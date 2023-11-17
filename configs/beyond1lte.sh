#!/bin/bash

# Build an Android kernel that is actually UEFI disguised as the Kernel
cat ./BootShim/AARCH64/BootShim.bin "./Build/beyond1ltePkg-AARCH64/${_TARGET_BUILD_MODE}_CLANG38/FV/BEYOND1LTE_UEFI.fd" > "./Build/beyond1ltePkg-AARCH64/${_TARGET_BUILD_MODE}_CLANG38/FV/BEYOND1LTE_UEFI.fd-bootshim"||exit 1
cat "./Build/beyond1ltePkg-AARCH64/${_TARGET_BUILD_MODE}_CLANG38/FV/BEYOND1LTE_UEFI.fd-bootshim" ./ImageResources/DTBs/beyond1lte.dtb > ./ImageResources/bootpayload.bin||exit 1

# Create bootable Android boot.img
python3 ./ImageResources/mkbootimg.py \
  --kernel ./ImageResources/bootpayload.bin \
  --ramdisk ./ImageResources/ramdisk \
  --kernel_offset 0x00000000 \
  --ramdisk_offset 0x00000000 \
  --tags_offset 0x00000000 \
  --os_version 13.0.0 \
  --os_patch_level "$(date '+%Y-%m')" \
  --header_version 1 \
  -o boot.img \
  ||_error "\nFailed to create Android Boot Image!\n"

# Compress Boot Image in a tar File for Odin/heimdall Flash
tar -c boot.img -f Mu-beyond1lte.tar||exit 1
mv boot.img Mu-beyond1lte.img||exit 1