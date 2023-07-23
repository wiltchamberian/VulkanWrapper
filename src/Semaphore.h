#ifndef __SEMAPHORE_H
#define __SEMAPHORE_H

#include "export.h"
#include "LogicalDevice.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API Semaphore {
public:
	friend class SemaphoreBuilder;
	VkSemaphore& value() { return semaphore;  }
	const VkSemaphore& value() const { return semaphore;  }
	void cleanUp();
private:
	LogicalDevice dev;
	VkSemaphore semaphore;
};


#endif