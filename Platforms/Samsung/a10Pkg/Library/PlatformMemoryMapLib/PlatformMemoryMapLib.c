#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    /* DDR Regions */
    {"Peripherals",       0x00000000, 0x80000000, AddDev, MMAP_IO, UNCACHEABLE,  MmIO,   NS_DEVICE},
    /* DDR Bank 0 Start */
    {"HLOS 0",            0x80000000, 0x00C00000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK_XN},
    {"UEFI Stack",        0x80C00000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP,  BsData, WRITE_BACK},
    {"CPU Vectors",       0x80C40000, 0x00010000, AddMem, SYS_MEM, SYS_MEM_CAP,  BsCode, WRITE_BACK},
    {"Dxe Heap",          0x80C50000, 0x0F3B0000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},
    {"UEFI FD",           0x90000000, 0x00930000, AddMem, SYS_MEM, SYS_MEM_CAP,  BsCode, WRITE_BACK},
    {"HLOS 1",            0x90930000, 0x2B2D0000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},
    //{"NonRelocateable 0", 0xBBC00000, 0x04400000, AddMem, SYS_MEM, SYS_MEM_CAP,  Reserv, NS_DEVICE},
    {"HLOS 2",            0xC0000000, 0x2C000000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},
    {"Display Reserved",  0xEC000000, 0x00800000, AddMem, MEM_RES, SYS_MEM_CAP,  Reserv, WRITE_THROUGH_XN},
    {"HLOS 3",            0xEC800000, 0x13800000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},

    /* Terminator for MMU */
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
    return gDeviceMemoryDescriptorEx;
}
