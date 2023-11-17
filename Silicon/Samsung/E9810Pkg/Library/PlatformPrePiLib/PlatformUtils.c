#include <PiPei.h>

#include <Library/IoLib.h>
#include <Library/PcdLib.h>
#include <Library/PlatformPrePiLib.h>

VOID PlatformInitialize(VOID)
{
  // Enable Frame Buffer Writes
  MmioWrite32(0x16030000, 0x1281);
}
