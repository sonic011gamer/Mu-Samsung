#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/IoLib.h>

#include <Protocol/EfiGpa.h>

EFI_STATUS
EFIAPI
ReadPin (
  IN EFI_GPA_PROTOCOL *This,
  IN UINT32            GpaBase,
  IN UINT8             Pin,
  OUT UINT32           PinValue)
{
  // Read Value from Pin
  PinValue = MmioRead32(GpaBase + Pin);

  return EFI_SUCCESS;
}

EFI_GPA_PROTOCOL gGpa = {
  ReadPin
};

EFI_STATUS
EFIAPI
GpaInit (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable)
{
  EFI_STATUS Status = EFI_SUCCESS;

  Status = gBS->InstallMultipleProtocolInterfaces(&ImageHandle, &gGpaProtocolGuid, &gGpa, NULL);
  if (EFI_ERROR (Status)) {
    DEBUG ((EFI_D_ERROR, "Failed to Install Gpa Protocol Interface!\n"));
    ASSERT_EFI_ERROR (Status);
  }

  return Status;
}