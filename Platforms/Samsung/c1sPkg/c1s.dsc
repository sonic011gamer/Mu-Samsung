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
  PLATFORM_NAME                  = c1s
  PLATFORM_GUID                  = f54e021f-3f08-4971-9860-56892e7e78cb
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/c1sPkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = c1sPkg/c1s.fdf
  BROKEN_CNTFRQ_EL0              = 1
  HAS_SPECIAL_BUTTON             = 0

[BuildOptions.common]
  *_*_*_CC_FLAGS = -DHAS_SPECIAL_BUTTON=$(HAS_SPECIAL_BUTTON)

[BuildOptions.common]
  *_CLANG38_AARCH64_CC_FLAGS = -DBROKEN_CNTFRQ_EL0=$(BROKEN_CNTFRQ_EL0)

[LibraryClasses.common]
  PlatformMemoryMapLib|c1sPkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x200000000        # 8GB Size

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"BotchedRPR"   # Device Maintainer

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x80C40000

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x80C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack

  # SmBios
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemVendor|"Samsung Electronics Co., Ltd."
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy Note20 5G"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"N981(B/F)"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_Note20_5G_N981B/F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy Note20 5G"

  # Buttons
  gSamsungPkgTokenSpaceGuid.PcdButtonsPinctrlBase|0x15850000
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonBankOffset|0x00
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonGpaPin|0x4
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonBankOffset|0x00
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonGpaPin|0x3
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonBankOffset|0x40
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonGpaPin|0x4

  # Simple FrameBuffer
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1080
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2400
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1080
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2400
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1080
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2400
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|168
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|168

!include E9830Pkg/E9830Pkg.dsc.inc
