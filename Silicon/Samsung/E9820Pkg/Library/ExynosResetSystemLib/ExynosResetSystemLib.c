/** @file
  ResetSystemLib implementation using PMU calls

  Copyright (c) 2017 - 2018, Linaro Ltd. All rights reserved.<BR>
  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2022, Arm Limited. All rights reserved.<BR>
  Copyright (c) 2015, Samsung Electronics Co., Ltd. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/
#include <PiDxe.h>

#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/ExynosPmuLib.h>

// SWRESET Registers
#define SWRESET         0x3A00
#define SWRESET_TRIGGER (1 << 1)

// PS_HOLD Registers
#define PS_HOLD_CONTROL 0x30C
#define PS_HOLD_EN      (1 << 8)

// PMU Registers
#define PMU_BASE_ADDR   0x15860000
#define PMU_SYSIP_DAT0  0x810

/**
  This function causes a system-wide reset (cold reset), in which
  all circuitry within the system returns to its initial state. This type of reset
  is asynchronous to system operation and operates without regard to
  cycle boundaries.

  If this function returns, it means that the system does not support cold reset.
**/
VOID
EFIAPI
ResetCold (VOID)
{
  // Write PMU to reset the System
  PmuWrite (PMU_BASE_ADDR, SWRESET, SWRESET_TRIGGER);
}

/**
  This function causes a system-wide initialization (warm reset), in which all processors
  are set to their initial state. Pending cycles are not corrupted.

  If this function returns, it means that the system does not support warm reset.
**/
VOID
EFIAPI
ResetWarm (VOID)
{
  // Do a Cold Reset as Exynos 9820 does not support Warm Reset.
  ResetCold ();
}

/**
  This function causes the system to enter a power state equivalent
  to the ACPI G2/S5 or G3 states.

  If this function returns, it means that the system does not support shutdown reset.
**/
VOID
EFIAPI
ResetShutdown (VOID)
{
  // Set PS_HOLD low to Shutdown System.
  PmuUpdate (PMU_BASE_ADDR, PS_HOLD_CONTROL, PS_HOLD_EN, 0);
}

/**
  This function causes a systemwide reset. The exact type of the reset is
  defined by the EFI_GUID that follows the Null-terminated Unicode string passed
  into ResetData. If the platform does not recognize the EFI_GUID in ResetData
  the platform must pick a supported reset type to perform.The platform may
  optionally log the parameters from any non-normal reset that occurs.

  @param[in]  DataSize   The size, in bytes, of ResetData.
  @param[in]  ResetData  The data buffer starts with a Null-terminated string,
                         followed by the EFI_GUID.
**/
VOID
EFIAPI
ResetPlatformSpecific (
  IN UINTN  DataSize,
  IN VOID  *ResetData)
{
  if (ResetData == "REBOOT_TO_RECOVERY") {
    // Set Cold Reboot to Recovery Reboot.
    MmioWrite32 (PMU_BASE_ADDR + PMU_SYSIP_DAT0, 0xFF);
  } else if (ResetData == "REBOOT_TO_DOWNLOAD_MODE") {
    // Set Cold Reset to Download Mode Reboot.
    MmioWrite32 (PMU_BASE_ADDR + PMU_SYSIP_DAT0, 0xFC);
  }

  // Map the platform specific reset as reboot
  ResetCold ();
}

/**
  The ResetSystem function resets the entire platform.

  @param[in] ResetType      The type of reset to perform.
  @param[in] ResetStatus    The status code for the reset.
  @param[in] DataSize       The size, in bytes, of ResetData.
  @param[in] ResetData      For a ResetType of EfiResetCold, EfiResetWarm, or EfiResetShutdown
                            the data buffer starts with a Null-terminated string, optionally
                            followed by additional binary data. The string is a description
                            that the caller may use to further indicate the reason for the
                            system reset.
**/
VOID
EFIAPI
ResetSystem (
  IN EFI_RESET_TYPE ResetType,
  IN EFI_STATUS     ResetStatus,
  IN UINTN          DataSize,
  IN VOID          *ResetData OPTIONAL)
{
  switch (ResetType) {
    case EfiResetWarm:
      ResetWarm ();
      break;

    case EfiResetCold:
      ResetCold ();
      break;

    case EfiResetShutdown:
      ResetShutdown ();
      return;

    case EfiResetPlatformSpecific:
      ResetPlatformSpecific (DataSize, ResetData);
      return;

    default:
      return;
  }
}