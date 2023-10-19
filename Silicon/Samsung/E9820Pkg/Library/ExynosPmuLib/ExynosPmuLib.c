/** @file
  Exynos 9820 Power Management Unit Library

  Copyright (c) 2015, Samsung Electronics Co., Ltd. All rights reserved.<BR>

  SPDX-License-Identifier: BSD-2-Clause-Patent
**/
#include <PiDxe.h>

#include <Library/ExynosPmuLib.h>
#include <Library/IoLib.h>

EFI_STATUS
PmuWrite (
  UINT32 PmuBaseAddr,
  UINT32 Offset,
  UINT32 Value)
{
  // TODO: Add Stuff
  return EFI_SUCCESS;
}

EFI_STATUS
PmuUpdate (
  UINT32 PmuBaseAddr,
  UINT32 Offset,
  UINT32 Mask,
  UINT32 Value)
{
  INT32 i;

  if (Offset > 0x3FFF) {
    // TODO: Add Stuff
  } else {
    for (i = 0; i < 32; i++) {
      if (Mask & (1 << i)) {
        if (Value & (1 << i)) {
          MmioWrite32 (PmuBaseAddr + (Offset | 0xC000), i);
        } else {
          MmioWrite32 (PmuBaseAddr + (Offset | 0x8000), i);
        }
      }
    }
  }

  return EFI_SUCCESS;
}