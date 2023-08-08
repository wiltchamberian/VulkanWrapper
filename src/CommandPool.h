#ifndef __COMMAND_POOL_H
#define __COMMAND_POOL_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class CommandBuffer;

class VULKAN_WRAPPER_API CommandPool {
public:
	friend class CommandPoolBuilder;
	VkCommandPool& value() { return pool;  }
	void cleanUp();
	CommandBuffer allocBuffer(VkCommandBufferLevel level);
	std::vector<CommandBuffer> allocBuffers(VkCommandBufferLevel level,uint32_t count);
	void destroyBuffer(const CommandBuffer& buf);
private:
	LogicalDevice dev;
	VkCommandPool pool;
};

#endif