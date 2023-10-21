/** @file
  ResetSystemLib implementation using PSCI calls

  Copyright (c) 2017 - 2018, Linaro Ltd. All rights reserved.<BR>
  Copyright (c) 2019, Intel Corporation. All rights reserved.<BR>
  Copyright (c) 2022, Arm Limited. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent

**/
#include <PiDxe.h>

#include <Library/ArmLib.h>
#include <Library/BaseLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PcdLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/ResetSystemLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/CacheMaintenanceLib.h>



#define PMU_BASE (0x11c80000)
#define SWRESET_OFFSET						(0x400)

VOID DestroyExynosMemMap(VOID);
typedef VOID (EFIAPI *CALL_STUB)(VOID);

VOID
DestroyExynosMemMap (
  VOID
  )
{
  EFI_STATUS              Status;
  UINTN                   MemoryMapSize;
  EFI_MEMORY_DESCRIPTOR   *MemoryMap;
  UINTN                   MapKey;
  UINTN                   DescriptorSize;
  UINT32                   DescriptorVersion;
  UINTN                   Pages;

  MemoryMap = NULL;
  MemoryMapSize = 0;
  do {
    Status = gBS->GetMemoryMap (
                    &MemoryMapSize,
                    MemoryMap,
                    &MapKey,
                    &DescriptorSize,
                    &DescriptorVersion
                    );
    if (Status == EFI_BUFFER_TOO_SMALL) {

      Pages = EFI_SIZE_TO_PAGES (MemoryMapSize) + 1;
      MemoryMap = AllocatePages (Pages);

      //
      // Get System MemoryMap
      //
      Status = gBS->GetMemoryMap (
                      &MemoryMapSize,
                      MemoryMap,
                      &MapKey,
                      &DescriptorSize,
                      &DescriptorVersion
                      );
      // Don't do anything between the GetMemoryMap() and ExitBootServices()
      if (!EFI_ERROR (Status)) {
        Status = gBS->ExitBootServices (gImageHandle, MapKey);
        if (EFI_ERROR (Status)) {
          FreePages (MemoryMap, Pages);
          MemoryMap = NULL;
          MemoryMapSize = 0;
        }
      }
    }
  } while (EFI_ERROR (Status));

  //Clean and invalidate caches.
  WriteBackInvalidateDataCache();
  InvalidateInstructionCache();

  //Turning off Caches and MMU
  ArmDisableDataCache ();
  ArmDisableInstructionCache ();
  ArmDisableMmu ();
}

/**
  This function causes a system-wide reset (cold reset), in which
  all circuitry within the system returns to its initial state. This type of reset
  is asynchronous to system operation and operates without regard to
  cycle boundaries.

  If this function returns, it means that the system does not support cold reset.
**/
VOID
EFIAPI
ResetCold (
  VOID
  )
{
  DEBUG ((EFI_D_ERROR, "ResetSystemLib: Cold reset!"));
  MmioWrite32 ((PMU_BASE + SWRESET_OFFSET), 0x01);
  while ((MmioRead32(PMU_BASE + SWRESET_OFFSET)) != 0x1);
}

/**
  This function causes a system-wide initialization (warm reset), in which all processors
  are set to their initial state. Pending cycles are not corrupted.

  If this function returns, it means that the system does not support warm reset.
**/
VOID
EFIAPI
ResetWarm (
  VOID
  )
{
  DEBUG ((EFI_D_ERROR, "ResetSystemLib: Warm Reset!"));
  DestroyExynosMemMap();
  CALL_STUB   StartOfFv;
  StartOfFv = (CALL_STUB)(UINTN)FixedPcdGet32(PcdFvBaseAddress);
  StartOfFv ();
}

/**
  This function causes the system to enter a power state equivalent
  to the ACPI G2/S5 or G3 states.

  If this function returns, it means that the system does not support shutdown reset.
**/
VOID
EFIAPI
ResetShutdown (
  VOID
  )
{
  ResetCold();
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
  IN VOID   *ResetData
  )
{
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
  IN EFI_RESET_TYPE  ResetType,
  IN EFI_STATUS      ResetStatus,
  IN UINTN           DataSize,
  IN VOID            *ResetData OPTIONAL
  )
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
