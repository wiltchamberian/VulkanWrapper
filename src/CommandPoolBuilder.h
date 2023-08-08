#ifndef __COMMAND_POOL_BUILDER_H
#define __COMMAND_POOL_BUILDER_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class CommandPool;

class VULKAN_WRAPPER_API CommandPoolBuilder {
public:
	CommandPoolBuilder(LogicalDevice dev);
	CommandPool build();
	CommandPoolBuilder& setCommandPoolCreateFlags(VkCommandPoolCreateFlags flags);
	CommandPoolBuilder& setQueueFamilyIndex(uint32_t index);
private:
	LogicalDevice dev;
	VkCommandPoolCreateInfo ci{};
};



#endif