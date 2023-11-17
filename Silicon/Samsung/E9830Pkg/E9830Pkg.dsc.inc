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
  USE_PHYSICAL_TIMER          = 1
  PRECOMPILED_CRYPTO_BINARIES = 0

[BuildOptions.common]
  *_*_AARCH64_CC_FLAGS = -march=armv8.2-a+crypto+rcpc

[PcdsFixedAtBuild.common]
  gArmTokenSpaceGuid.PcdArmArchTimerFreqInHz|26000000
  gArmTokenSpaceGuid.PcdArmArchTimerSecIntrNum|13
  gArmTokenSpaceGuid.PcdArmArchTimerIntrNum|14
  gArmTokenSpaceGuid.PcdArmArchTimerVirtIntrNum|11
  gArmTokenSpaceGuid.PcdArmArchTimerHypIntrNum|10
  gArmTokenSpaceGuid.PcdGicDistributorBase|0x10101000
  gArmTokenSpaceGuid.PcdGicRedistributorsBase|0x10102000
  gArmTokenSpaceGuid.PcdGicInterruptInterfaceBase|0x10100000

  gEfiMdeModulePkgTokenSpaceGuid.PcdAcpiDefaultOemRevision|0x00009830
  gEmbeddedTokenSpaceGuid.PcdInterruptBaseAddress|0x10100000

  gSamsungPkgTokenSpaceGuid.PcdSmbiosProcessorModel|"Exynos (TM) 9830 @ 2.73 GHz"
  gSamsungPkgTokenSpaceGuid.PcdSmbiosProcessorRetailModel|"E9830"

  gArmPlatformTokenSpaceGuid.PcdCoreCount|8
  gArmPlatformTokenSpaceGuid.PcdClusterCount|3

[LibraryClasses.common]
  PlatformPeiLib|E9830Pkg/Library/PlatformPeiLib/PlatformPeiLib.inf
  PlatformPrePiLib|E9830Pkg/Library/PlatformPrePiLib/PlatformPrePiLib.inf
  HwResetSystemLib|ArmPkg/Library/ArmSmcPsciResetSystemLib/ArmSmcPsciResetSystemLib.inf
  ResetSystemLib|ArmPkg/Library/ArmSmcPsciResetSystemLib/ArmSmcPsciResetSystemLib.inf

[Components.common]
  E9830Pkg/Drivers/SmBiosTableDxe/SmBiosTableDxe.inf

!include SamsungPkg/SamsungPkg.dsc.inc
