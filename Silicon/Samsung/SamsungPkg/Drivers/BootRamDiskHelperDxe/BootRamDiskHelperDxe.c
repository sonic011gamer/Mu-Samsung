/**
 * @file BootRamdiskHelperDxe.c
 * @author amarioguy (Arminder Singh)
 * 
 * Sets up an embedded RAMDisk in the FV. For right now this is primarily used to bring up WinPE.
 * 
 * @version 1.0
 * @date 2022-12-25
 * 
 * @copyright Copyright (c) amarioguy (Arminder Singh), 2022.
 * 
**/

#include <PiDxe.h>

#include "BootRamdiskHelperDxe.h"

/**
  @brief Main function for RAMDisk initialization.

  Note that we only allocate a RAMDisk with a boot image here if we are told to do so and actually have the file embedded in the FV.

  @param ImageHandle 
  @param SystemTable 
  @return
 
  EFI_SUCCESS - we initialized the RAMDisk as a bootable device.
  EFI_UNSUPPORTED - we are configured not to set up the RAMDisk.
  EFI_NOT_FOUND - no FV embedded candidate image is present.
  EFI_OUT_OF_RESOURCES - for some reason, we are out of memory and cannot create the ramdisk.
  EFI_ABORTED - an unexpected error occurred.
**/
EFI_STATUS
EFIAPI
BootRamdiskHelperDxeInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable)
{
  EFI_STATUS                Status                = EFI_SUCCESS;
  BOOLEAN                   RamdiskBootConfigured = FALSE;
  VOID                     *OriginalRamDiskPtr    = NULL;
  VOID                     *DestinationRamdiskPtr = NULL;
  UINTN                     RamDiskSize           = 0;
  EFI_GUID                 *RamDiskRegisterType   = &gEfiVirtualDiskGuid; // Hardcode to IMG image for now
  EFI_RAM_DISK_PROTOCOL    *RamdiskProtocol       = NULL;
  EFI_DEVICE_PATH_PROTOCOL *DevicePath            = NULL;

  DEBUG((EFI_D_WARN, "BootRamdiskHelperDxe started\n"));

  Status = GetSectionFromAnyFv(&gSamsungPkgEmbeddedRamdiskGuid, EFI_SECTION_RAW, 0, &OriginalRamDiskPtr, &RamDiskSize);
  if (EFI_ERROR (Status)) {
    DEBUG((EFI_D_ERROR, "%a: No FV Embedded Ramdisk Found.\n", __FUNCTION__));
    goto exit;
  }

  ASSERT (OriginalRamDiskPtr != NULL);
  ASSERT (RamDiskSize != 0);

  // Copy the RAMDisk to a New Scratch Location
  DestinationRamdiskPtr = AllocateCopyPool(RamDiskSize, OriginalRamDiskPtr);

  ASSERT (DestinationRamdiskPtr != NULL);

  Status = gBS->LocateProtocol(&gEfiRamDiskProtocolGuid, NULL, (VOID **)&RamdiskProtocol);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "%a: Couldn't find the RAMDisk Protocol! Status = %r\n", __FUNCTION__, Status));
    goto exit;
  }

  Status = RamdiskProtocol->Register((UINTN)DestinationRamdiskPtr, (UINT64)RamDiskSize, RamDiskRegisterType, NULL, &DevicePath);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "%a: Cannot register RAM Disk! Status = %r\n", __FUNCTION__, Status));
  }

exit:
  return Status;
}