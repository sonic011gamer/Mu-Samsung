#include <PiPei.h>
#include <Library/IoLib.h>
#include <Library/PlatformPrePiLib.h>
#include "PlatformUtils.h"

VOID PlatformInitialize(VOID)
{
  // Enable Framebuffer
  MmioWrite32(DECON_F_BASE + HW_SW_TRIG_CONTROL, 0x1281);
/*  UINT8 *base = (UINT8 *)0x067000000ull;
  for (UINTN i = 0; i < 0x00800000; i++) {
    base[i] = 0;
  }(*/
}
