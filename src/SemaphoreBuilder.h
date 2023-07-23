#ifndef __SEMAPHORE_BUILDER_H
#define __SEMAPHORE_BUILDER_H

#include "export.h"
#include "Semaphore.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API SemaphoreBuilder {
public:
	SemaphoreBuilder(LogicalDevice dev);
	Semaphore build();
	SemaphoreBuilder& setSemaphoreCreateFlags(VkSemaphoreCreateFlags flags);
private:
	LogicalDevice dev;
	VkSemaphoreCreateInfo ci;
};

#endif