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
  PLATFORM_NAME                  = j4lte
  PLATFORM_GUID                  = 93cf4d7c-0441-4a40-891b-4b5f8d4a34ef
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/j4ltePkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = j4ltePkg/j4lte.fdf
  BROKEN_CNTFRQ_EL0              = 1
  HAS_SPECIAL_BUTTON             = 0

[BuildOptions.common]
  *_CLANG38_AARCH64_CC_FLAGS = -DBROKEN_CNTFRQ_EL0=$(BROKEN_CNTFRQ_EL0) -DHAS_SPECIAL_BUTTON=$(HAS_SPECIAL_BUTTON)

[LibraryClasses.common]
  PlatformMemoryMapLib|j4ltePkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x40000000         # Starting address
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x80000000         # 2GB Size

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"predefine"   # Device Maintainer

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x40C40000

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x40C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack

  # SmBios
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemVendor|"Samsung Electronics Co., Ltd."
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy J4"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"J400F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_J4_J400F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy J4"

  # Buttons
  gSamsungPkgTokenSpaceGuid.PcdButtonsPinctrlBase|0x139F0000
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonBankOffset|0x80
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonGpaPin|0x3
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonBankOffset|0x40
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonGpaPin|0x7
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonBankOffset|0x40
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonGpaPin|0x4      # TODO: Write pmic power keys driver
  # Simple FrameBuffer
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|720
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|1280
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|720
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|1280
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|720
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|1280
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|90
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|80
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|90
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|80

!include E7570Pkg/E7570Pkg.dsc.inc
