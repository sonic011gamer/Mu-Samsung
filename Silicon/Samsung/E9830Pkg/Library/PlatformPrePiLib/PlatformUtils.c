#include <PiPei.h>

#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformPrePiLib.h>

#include "PlatformUtils.h"

VOID PlatformInitialize(VOID)
{
  // Initialize GIC
  MmioWrite32(GICR_WAKER_CURRENT_CPU, (MmioRead32(GICR_WAKER_CURRENT_CPU) & ~GIC_WAKER_PROCESSORSLEEP));

  // Enable Framebuffer
  MmioWrite32(DECON_F_BASE + HW_SW_TRIG_CONTROL, 0x1281);
}
