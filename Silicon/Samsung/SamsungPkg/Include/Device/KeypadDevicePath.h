#ifndef __KEYPAD_DEVICE_PATH_H__
#define __KEYPAD_DEVICE_PATH_H__

typedef struct {
  VENDOR_DEVICE_PATH Keypad;
  EFI_DEVICE_PATH    End;
} KEYPAD_DEVICE_PATH;

KEYPAD_DEVICE_PATH mInternalKeypadDevicePath = {
  {
    {
      HARDWARE_DEVICE_PATH,
      HW_VENDOR_DP,
      {
        (UINT8)(sizeof(VENDOR_DEVICE_PATH)),
        (UINT8)((sizeof(VENDOR_DEVICE_PATH)) >> 8),
      },
    },
    {
      0x12cf7c54,
      0x4962,
      0x4d2a,
      {0x93, 0x48, 0x92, 0x7d, 0xf4, 0xa2, 0x35, 0xe5},
    },
  },
  {
    END_DEVICE_PATH_TYPE,
    END_ENTIRE_DEVICE_PATH_SUBTYPE,
    {sizeof(EFI_DEVICE_PATH_PROTOCOL), 0},
  },
};

#endif