/** @file
  This module installs the MsButtonServicesProtocol.

  Copyright (C) Microsoft Corporation. All rights reserved.
  SPDX-License-Identifier: BSD-2-Clause-Patent
**/
#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/IoLib.h>
#include <Library/DebugLib.h>
#include <Library/DevicePathLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>

#include <Protocol/ButtonServices.h>
#include <Protocol/SimpleTextInEx.h>

#include <Configuration/BootDevices.h>

#include "GpioButtons.h"

/**
  Say Volume Up Button is Pressed because we want to go to Front Page.

  @param[in]     - Button Services Protocol Pointer
  @param[out]    - Pointer to a boolean Value to receive the Button State

  @retval        - EFI_SUCCESS;
**/
EFI_STATUS
EFIAPI
PreBootVolumeUpButtonThenPowerButtonCheck(
  IN  MS_BUTTON_SERVICES_PROTOCOL *This,
  OUT BOOLEAN                     *PreBootVolumeUpButtonThenPowerButton)
{
  GPIO_BUTTON_SERVICES_PROTOCOL *Bsp;

  Bsp                                   = MS_BSP_FROM_BSP(This);
  *PreBootVolumeUpButtonThenPowerButton = (Bsp->ButtonState == VolUpButton);

  return EFI_SUCCESS;
}

/**
  Say Volume Down Button is Pressed because we want to go to Front Page.

  @param[in]     - Button Services Protocol Pointer
  @param[out]    - Pointer to a boolean Value to receive the Button State

  @retval        - EFI_SUCCESS;
**/
EFI_STATUS
EFIAPI
PreBootVolumeDownButtonThenPowerButtonCheck(
  IN  MS_BUTTON_SERVICES_PROTOCOL *This,
  OUT BOOLEAN                     *PreBootVolumeDownButtonThenPowerButton)
{
  GPIO_BUTTON_SERVICES_PROTOCOL *Bsp;

  Bsp                                     = MS_BSP_FROM_BSP(This);
  *PreBootVolumeDownButtonThenPowerButton = (Bsp->ButtonState == VolDownButton);

  return EFI_SUCCESS;
}

/**
  Clear Current Button State.

  @param[in]     - Button Services Protocol Pointer

  @retval        - EFI_SUCCESS;
**/
EFI_STATUS
EFIAPI
PreBootClearVolumeButtonState(IN MS_BUTTON_SERVICES_PROTOCOL *This)
{
  GPIO_BUTTON_SERVICES_PROTOCOL *Bsp;

  Bsp              = MS_BSP_FROM_BSP(This);
  Bsp->ButtonState = NoButtons;

  return EFI_SUCCESS;
}

/**
  GetButtonState gets the Button State of the Vol+/Vol- Buttons, and Stores that
  State in gButtonState.

  @return EFI_SUCCESS - String Buffer returned to Caller
  @return EFI_ERROR   - Error the String
**/
EFI_STATUS
GetButtonState()
{
  EFI_STATUS Status   = EFI_SUCCESS;
  UINT32     PinAddr  = 0;
  UINT32     PinState = 0;

  if (gBsp == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    goto exit;
  }

  // Check Volume Up State
  PinAddr  = ((FixedPcdGet32(PcdButtonsPinctrlBase) + FixedPcdGet32(PcdVolumeUpButtonBankOffset)) + 0x4);
  PinState = MmioRead32 (PinAddr);
  if (!(PinState & (1 << FixedPcdGet32(PcdVolumeUpButtonGpaPin)))) {
    gBsp->ButtonState = VolUpButton;
    goto exit;
  }

  // Check Volume Down State
  PinAddr  = ((FixedPcdGet32(PcdButtonsPinctrlBase) + FixedPcdGet32(PcdVolumeDownButtonBankOffset)) + 0x4);
  PinState = MmioRead32 (PinAddr);
  if (!(PinState & (1 << FixedPcdGet32(PcdVolumeDownButtonGpaPin)))) {
    gBsp->ButtonState = VolDownButton;
  }

exit:
  return Status;
}

/**
  Constructor Routine to Install Button Services Protocol and initialize Anything
  related to Buttons

  @param[in]     - Image Handle of the Process Loading this Module
  @param[in]     - Efi System Table Pointer

  @retval        - EFI_SUCCESS (Always for a Constructor)
**/
EFI_STATUS
EFIAPI
ButtonsInit(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  gBsp = AllocateZeroPool (sizeof(GPIO_BUTTON_SERVICES_PROTOCOL));
  if (gBsp == NULL) {
    Status = EFI_OUT_OF_RESOURCES;
    DEBUG ((EFI_D_ERROR, "Failed to Allocate Memory for Button Service Protocol! Status = %r\n", Status));
    goto exit;
  }

  gBsp->ButtonServicesProtocol.PreBootVolumeDownButtonThenPowerButtonCheck = PreBootVolumeDownButtonThenPowerButtonCheck;
  gBsp->ButtonServicesProtocol.PreBootVolumeUpButtonThenPowerButtonCheck   = PreBootVolumeUpButtonThenPowerButtonCheck;
  gBsp->ButtonServicesProtocol.PreBootClearVolumeButtonState               = PreBootClearVolumeButtonState;
  gBsp->ButtonState                                                        = NoButtons;

  Status = GetButtonState ();
  if (EFI_ERROR (Status)) {
    FreePool(gBsp);
    goto exit;
  }

  // Install the protocol
  Status = gBS->InstallMultipleProtocolInterfaces (&ImageHandle, &gMsButtonServicesProtocolGuid, gBsp, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Button Services Protocol Publisher: Install Protocol Error! Status = %r\n", Status));
    FreePool(gBsp);
    goto exit;
  }

exit:
  return Status;
}