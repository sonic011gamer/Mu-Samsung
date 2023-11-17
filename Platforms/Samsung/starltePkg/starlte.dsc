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
  PLATFORM_NAME                  = starlte
  PLATFORM_GUID                  = 93cf4d7c-0441-4a40-891b-4b5f8d4a34ef
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/starltePkg-$(ARCH)
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = starltePkg/starlte.fdf
  BROKEN_CNTFRQ_EL0              = 1
  DISPLAY_USES_RGBA              = 0
  HAS_SPECIAL_BUTTON             = 1

[BuildOptions.common]
  *_*_*_CC_FLAGS = -DDISPLAY_USES_RGBA=$(DISPLAY_USES_RGBA) -DHAS_SPECIAL_BUTTON=$(HAS_SPECIAL_BUTTON) -DBROKEN_CNTFRQ_EL0=$(BROKEN_CNTFRQ_EL0)

[LibraryClasses.common]
  PlatformMemoryMapLib|starltePkg/Library/PlatformMemoryMapLib/PlatformMemoryMapLib.inf

[PcdsFixedAtBuild.common]
  # Platform-specific
  gArmTokenSpaceGuid.PcdSystemMemoryBase|0x80000000         # Starting address
  gArmTokenSpaceGuid.PcdSystemMemorySize|0x100000000        # 4GB Size

  gEfiMdeModulePkgTokenSpaceGuid.PcdFirmwareVendor|L"No Maintainer"   # Device Maintainer

  gArmTokenSpaceGuid.PcdCpuVectorBaseAddress|0x80C40000

  gEmbeddedTokenSpaceGuid.PcdPrePiStackBase|0x80C00000
  gEmbeddedTokenSpaceGuid.PcdPrePiStackSize|0x00040000      # 256K stack

  # SmBios
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemVendor|"Samsung Electronics Co"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemModel|"Galaxy S9"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailModel|"G960F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosSystemRetailSku|"Galaxy_S9_G960F"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosBoardModel|"Galaxy S9"

  # Buttons
  gSamsungPkgTokenSpaceGuid.PcdButtonsPinctrlBase|0x14050000
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonBankOffset|0x0
  gSamsungPkgTokenSpaceGuid.PcdVolumeDownButtonGpaPin|0x4
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonBankOffset|0x0
  gSamsungPkgTokenSpaceGuid.PcdVolumeUpButtonGpaPin|0x3
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonBankOffset|0x40
  gSamsungPkgTokenSpaceGuid.PcdPowerButtonGpaPin|0x4
  gSamsungPkgTokenSpaceGuid.PcdSpecialButtonBankOffset|0x0
  gSamsungPkgTokenSpaceGuid.PcdSpecialButtonGpaPin|0x6

  # Simple FrameBuffer
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferWidth|1440
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferHeight|2960
  gSamsungPkgTokenSpaceGuid.PcdMipiFrameBufferPixelBpp|32

[PcdsDynamicDefault.common]
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoHorizontalResolution|1440
  gEfiMdeModulePkgTokenSpaceGuid.PcdVideoVerticalResolution|2960
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoHorizontalResolution|1440
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupVideoVerticalResolution|2960
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdSetupConOutRow|155
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutColumn|180
  gEfiMdeModulePkgTokenSpaceGuid.PcdConOutRow|155

!include E9810Pkg/E9810Pkg.dsc.inc
