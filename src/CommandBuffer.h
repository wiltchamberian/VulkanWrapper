#ifndef __COMMAND_BUFFER_H
#define __COMMAND_BUFFER_H

#include "export.h"
#include "vulkan/vulkan.h"

class CommandBuffer {
public:
	friend class CommandPool;
	CommandBuffer& begin(VkCommandBufferBeginInfo info);
	CommandBuffer& end();
private:
	VkCommandBuffer buf;
};


#endif