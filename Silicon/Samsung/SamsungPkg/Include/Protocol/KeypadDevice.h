#ifndef __PROTOCOL_KEYPAD_DEVICE_H__
#define __PROTOCOL_KEYPAD_DEVICE_H__

#include <Protocol/SimpleTextInEx.h>

#define KEYPAD_DEVICE_PROTOCOL_GUID                                            \
  {                                                                            \
    0x12cf7c54, 0x4962, 0x4d2a,                                                \
    {                                                                          \
      0x93, 0x48, 0x92, 0x7d, 0xf4, 0xa2, 0x35, 0xe5                           \
    }                                                                          \
  }

typedef struct _KEYPAD_DEVICE_PROTOCOL KEYPAD_DEVICE_PROTOCOL;
typedef struct _KEYPAD_RETURN_API      KEYPAD_RETURN_API;

typedef VOID(EFIAPI *PUSH_EFI_KEY_BUF_TAIL)(
    KEYPAD_RETURN_API *This, EFI_KEY_DATA *KeyData);

struct _KEYPAD_RETURN_API {
  PUSH_EFI_KEY_BUF_TAIL PushEfikeyBufTail;
};

typedef EFI_STATUS(EFIAPI *KEYPAD_RESET)(KEYPAD_DEVICE_PROTOCOL *This);
typedef EFI_STATUS(EFIAPI *KEYPAD_GET_KEYS)(
    KEYPAD_DEVICE_PROTOCOL *This, KEYPAD_RETURN_API *KeypadReturnApi,
    UINT64 Delta);

struct _KEYPAD_DEVICE_PROTOCOL {
  KEYPAD_RESET    Reset;
  KEYPAD_GET_KEYS GetKeys;
};

extern EFI_GUID gExynosKeypadDeviceProtocolGuid;

#endif