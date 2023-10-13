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
  PLATFORM_GUID                  = 93cf4d7c-0441-4a40-891b-4b5f8d4a34ef
  PLATFORM_VERSION               = 0.1
  DSC_SPECIFICATION              = 0x00010005
  OUTPUT_DIRECTORY               = Build/a10Pkg
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE
  SKUID_IDENTIFIER               = DEFAULT
  FLASH_DEFINITION               = a10Pkg/a10.fdf

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

!include Exynos7885Pkg/Exynos7885Pkg.dsc.inc
