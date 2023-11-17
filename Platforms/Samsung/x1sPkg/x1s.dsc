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
  PLATFORM_NAME                  = x1s
  PLATFORM_GUID                  = fffa8af8-0c7a-4240-a68f-4f3611db3547
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/x1sPkg-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = x1sPkg/x1s.fdf
  BROKEN_CNTFRQ_EL0              = 1
  DISPLAY_USES_RGBA              = 0
  HAS_SPECIAL_BUTTON             = 0

[BuildOptions.common]
  *_*_*_CC_FLAGS = -DDISPLAY_USES_RGBA=$(DISPLAY_USES_RGBA) -DHAS_SPECIAL_BUTTON=$(HAS_SPECIAL_BUTTON) -DBROKEN_CNTFRQ_EL0=$(BROKEN_CNTFRQ_EL0)

[LibraryClasses.common]
  PlatformMemoryMapLib|x1sPkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # Starting address
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x300000000        # 12GB Size

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"halal-beef"   # Device Maintainer

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x80C40000

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x80C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack

  # SmBios
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemVendor|"Samsung Electronics Co., Ltd."
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy S20 5G"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"G981B"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_S20_5G_G981B"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy S20 5G"

  # Buttons
  gSamsungPkgTokenSpaceGuid.PcdButtonsPinctrlBase|0x15850000
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonBankOffset|0x00
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonGpaPin|0x4
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonBankOffset|0x00
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonGpaPin|0x3
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonBankOffset|0x40
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonGpaPin|0x4

  # Simple FrameBuffer
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1440
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|3200
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1440
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|3200
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1440
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|3200
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|168
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|168

!include E9830Pkg/E9830Pkg.dsc.inc
