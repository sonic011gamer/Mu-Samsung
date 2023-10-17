## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018, Bingxing Wang. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

################################################################################
#
# Defines Section - statements that will be processed to create a Makefile.
#
################################################################################
[Defines]
  PLATFORM_NAME                  = a10
  PLATFORM_GUID                  = f54e021f-3f08-4971-9860-56892e7e78cb
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/a10Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = a10Pkg/a10.fdf
  ENABLE_RAMDISK                 = 0

[BuildOptions.common]
  *_*_*_CC_FLAGS = -DENABLE_RAMDISK=$(ENABLE_RAMDISK)

[LibraryClasses.common]
  PlatformMemoryMapLib|a10Pkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # Starting address
!if $(RAM_SIZE) == 2
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x80000000         # 2GB Size
!elseif $(RAM_SIZE) == 4
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x100000000        # 4GB Size
!else
!error "Invaild RAM Size! Use 2 or 4."
!endif

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"snaccy"   # Device Maintainer

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x80C40000

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x80C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack

  # SmBios
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemVendor|"Samsung Electronics Co., Ltd."
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy A10"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"A105F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_A10_A105F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy A10"

  # Buttons
  gSamsungPkgTokenSpaceGuid.PcdButtonsPinctrlBase|0x11CB0000
  gSamsungPkgTokenSpaceGuid.PcdVolumeButtonsBankOffset|0x60
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonGpaPin|0x6
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonGpaPin|0x5
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonBankOffset|0x60
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonGpaPin|0x7
  gSamsungPkgTokenSpaceGuid.PcdSpecialButton|FALSE
  gSamsungPkgTokenSpaceGuid.PcdSpecialButtonGpaPin|0x0

  # Simple FrameBuffer
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|720
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|1520
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|720
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1520
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|720
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1520
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|90
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|80
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|90
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|80

!include E7885Pkg/E7885Pkg.dsc.inc