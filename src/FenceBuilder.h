#ifndef __FENCE_BUILDER_H
#define __FENCE_BUILDER_H

#include "Fence.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API FenceBuilder {
public:
	FenceBuilder(LogicalDevice d);
	Fence build();
	FenceBuilder& setFenceCreateFlags(VkFenceCreateFlags flags);
private:
	LogicalDevice dev;
	VkFenceCreateInfo ci;
};

#endif