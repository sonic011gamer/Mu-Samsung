#include <Library/BaseLib.h>
#include <Library/PlatformMemoryMapLib.h>

static ARM_MEMORY_REGION_DESCRIPTOR_EX gDeviceMemoryDescriptorEx[] = {
    //
    // Name, Address, Length, HobOption,
    // ResourceAttribute, ArmAttributes,
    // ResourceType, MemoryType
    //

    // DDR Regions
    {"HLOS 0", 0x80000000, 0x00C00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"UEFI Stack", 0x80C00000, 0x00040000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiBootServicesData, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"CPU Vectors", 0x80C40000, 0x00010000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiBootServicesData, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"HLOS 1", 0x80C50000, 0x0F3B0000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"UEFI FD", 0x90000000, 0x00200000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiBootServicesData, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"HLOS 2", 0x90200000, 0x2BA00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"HLOS 3", 0xA0000000, 0x2C000000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"Display Reserved",  0xCC000000, 0x02085000, AddMem,
     EFI_RESOURCE_MEMORY_RESERVED, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_THROUGH},

    {"DXE Heap", 0xCE085000, 0x07C00000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"HLOS 4", 0xEC800000, 0x13800000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"ABOX", 0xFB200000, 0x02800000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    {"Exynos SS", 0xFDA00000, 0x01C08000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiReservedMemoryType, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    // RAM partition regions
    {"RAM Partition", 0x880000000, 0x80000000, AddMem,
     EFI_RESOURCE_SYSTEM_MEMORY, SYSTEM_MEMORY_RESOURCE_ATTR_CAPABILITIES,
     EfiConventionalMemory, ARM_MEMORY_REGION_ATTRIBUTE_WRITE_BACK},

    // Register regions
    {"Periphs", 0x00000000, 0x80000000, AddDev,
     EFI_RESOURCE_MEMORY_MAPPED_IO, EFI_RESOURCE_ATTRIBUTE_UNCACHEABLE,
     EfiMemoryMappedIO, ARM_MEMORY_REGION_ATTRIBUTE_NONSECURE_DEVICE},

    // Terminator for MMU
    {"Terminator", 0, 0, 0, 0, 0, 0, 0}};

ARM_MEMORY_REGION_DESCRIPTOR_EX *GetPlatformMemoryMap()
{
    return gDeviceMemoryDescriptorEx;
}