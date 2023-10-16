#ifndef _GPA_PROTOCOL_H_
#define _GPA_PROTOCOL_H_

//
// Global ID for the Gpa Protocol
//
#define EFI_GPA_PROTOCOL_GUID { 0xc20139b1, 0x0306, 0x4a2e, { 0xa5, 0x44, 0xb8, 0xc8, 0xbf, 0xd0, 0x14, 0x31 } }

//
// Declare forward reference to the Gpa Protocol
//
typedef struct _EFI_GPA_PROTOCOL EFI_GPA_PROTOCOL;

/**
  This Function Reads the Value from Defined Pin from the GPIO Controller

  @param This         The EFI_GPA_PROTOCOL instance.
  @param GpaBase      The Base Address of the GPIO Controller.
  @param Pin          The GPIO Pin that will be read from.
  @param PinValue     Puts Out the Read Value from GPIO Pin.

  @retval EFI_SUCCESS The Pin has been Read Successfully.
**/
typedef
EFI_STATUS
(EFIAPI *EFI_GPA_READ_PIN)(
  IN EFI_GPA_PROTOCOL *This,
  IN UINT32            GpaBase,
  IN UINT8             Pin,
  OUT UINT32           PinValue
  );

//
// Define Protocol Functions
//
struct _EFI_GPA_PROTOCOL {
  EFI_GPA_READ_PIN  ReadPin;
};

extern EFI_GUID gGpaProtocolGuid;

#endif /* _GPA_PROTOCOL_H_ */