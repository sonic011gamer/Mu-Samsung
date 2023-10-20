#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* DDR Regions */
    {"Peripherals",       0x00000000, 0x15000000, AddDev, MMAP_IO, UNCACHEABLE,  MmIO,  NS_DEVICE},
    /* DDR Bank 0 Start */
    /* Memory addresses: 40000000-7e7fffff */
    {"HLOS 0",            0x40000000, 0x00C00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
    //{"HLOS 1",            0x40000000, 0x00C00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
    {"UEFI Stack",        0x40C00000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP, BsData, WRITE_BACK},
    {"CPU Vectors",       0x40C40000, 0x00010000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
    {"Dxe Heap",          0x40C50000, 0x0F3B0000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
    {"UEFI FD",           0x50000000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
    {"Display Reserved",  0x67000000, 0x00800000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH},
    /* DDR Bank 1 Start */
    /* Memory addresses: 80000000-ffffffff */


    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
    return gDeviceMemoryDescriptorEx;
}
