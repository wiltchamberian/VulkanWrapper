#include "MemoryAllocator.h"


MemoryAllocator::MemoryAllocator(LogicalDevice logicalDev)
:dev(logicalDev){
    
}

DeviceMemory MemoryAllocator::allocateMemory() {
    DeviceMemory memory(dev);
    ai.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    vkAllocateMemory(dev.value(), &ai, nullptr, &memory.value());

    return memory;
}

MemoryAllocator& MemoryAllocator::SetAllocationSize(uint64_t siz) {
    ai.allocationSize = siz;
    return *this;
}

MemoryAllocator& MemoryAllocator::SetMemoryTypeIndex(uint32_t index) {
    ai.memoryTypeIndex = index;
    return *this;
}