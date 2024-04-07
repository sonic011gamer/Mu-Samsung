#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
//--------------------- Register ---------------------
    {"Periphs",           0x00000000, 0x20000000,  AddMem, MEM_RES, UNCACHEABLE,  RtCode,   NS_DEVICE},

//--------------------- DDR --------------------- */

    {"HLOS 0",            0x80000000, 0x00C00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv, WRITE_BACK},
    {"UEFI Stack",        0x80C00000, 0x00040000, AddMem, SYS_MEM, SYS_MEM_CAP,  BsData, WRITE_BACK},
    {"CPU Vectors",       0x80C40000, 0x00010000, AddMem, SYS_MEM, SYS_MEM_CAP,  BsCode, WRITE_BACK},
    {"Dxe Heap",          0x80C50000, 0x0F3B0000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},
    {"UEFI FD",           0x90000000, 0x00200000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
    {"HLOS 0 Split 2",    0x90200000, 0xF3B0000, AddMem, SYS_MEM, SYS_MEM_CAP, BsCode, WRITE_BACK},
    {"HLOS 1",            0xC1200000, 0x3EE00000, AddMem, SYS_MEM, SYS_MEM_CAP, Conv,   WRITE_BACK},
    {"HLOS 2",            0xE1900000, 0x1E700000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},
    {"Display Reserved",  0xf1000000, 0x00800000, AddMem, MEM_RES, SYS_MEM_CAP, Reserv, WRITE_THROUGH},
    {"HLOS 3",            0x880000000, 0x183550000, AddMem, SYS_MEM, SYS_MEM_CAP,  Conv,   WRITE_BACK},

    /* Terminator for MMU */
    { "Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
    return gDeviceMemoryDescriptorEx;
}