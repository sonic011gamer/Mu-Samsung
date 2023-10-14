## @file
#
#  Copyright (c) 2011-2015, ARM Limited. All rights reserved.
#  Copyright (c) 2014, Linaro Limited. All rights reserved.
#  Copyright (c) 2015 - 2016, Intel Corporation. All rights reserved.
#  Copyright (c) 2018 - 2019, Bingxing Wang. All rights reserved.
#
#  SPDX-License-Identifier: BSD-2-Clause-Patent
#
##

# SoC Defines
[Defines]
  USE_PHYSICAL_TIMER             = 1

[BuildOptions.common]
  *_*_*_CC_FLAGS = -march=armv8.2-a+crypto+rcpc

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|26000000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|13
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|14
  gArmTokenSpaceGuid.PcdArmArchTimerVirtIntrNum|11
  gArmTokenSpaceGuid.PcdArmArchTimerHypIntrNum|10
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x12301000
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x12304000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x12300000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00007885
  gEmbeddedTokenSpaceGuid.PcdInterruptBaseAddress|0x12300000

  gSamsungPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Exynos (TM) 7885 @ 2.20 GHz"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"E7885"

  gArmPlatformTokenSpaceGuid.PcdCoreCount|8
  gArmPlatformTokenSpaceGuid.PcdClusterCount|2

[LibraryClasses.common]
  PlatformPeiLib|Exynos7885Pkg/Library/PlatformPeiLib/PlatformPeiLib.inf
  PlatformPrePiLib|Exynos7885Pkg/Library/PlatformPrePiLib/PlatformPrePiLib.inf
  HwResetSystemLib|Exynos7885Pkg/Library/ResetSystemLib/ResetSystemLib.inf
  ResetSystemLib|Exynos7885Pkg/Library/ResetSystemLib/ResetSystemLib.inf

[Components.common]
  Exynos7885Pkg/Drivers/SmBiosTableDxe/SmBiosTableDxe.inf

!include SamsungPkg/SamsungPkg.dsc.inc
