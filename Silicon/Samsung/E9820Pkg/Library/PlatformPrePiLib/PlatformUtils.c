#include <PiPei.h>

#include <Library/IoLib.h>
#include <Library/PlatformPrePiLib.h>

VOID PlatformInitialize(VOID)
{
  // Enable Frame Buffer Writes
  MmioWrite32(0x19030000, 0x1281);
}
