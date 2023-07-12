#ifndef __COMMAND_POOL_H
#define __COMMAND_POOL_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class CommandBuffer;

class CommandPool {
public:
	friend class CommandPoolBuilder;
	void cleanUp();
	CommandBuffer allocBuffer(VkCommandBufferLevel level);
	std::vector<CommandBuffer> allocBuffers(VkCommandBufferLevel level,uint32_t count);
	void destroyBuffer(const CommandBuffer& buf);
private:
	LogicalDevice dev;
	VkCommandPool pool;
};

#endif