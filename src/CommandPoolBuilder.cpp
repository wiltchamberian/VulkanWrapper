#include "CommandPoolBuilder.h"
#include "CommandPool.h"
#include <stdexcept>

CommandPoolBuilder::CommandPoolBuilder(LogicalDevice d)
:dev(d)
, ci{}
{
	ci.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
}

CommandPool CommandPoolBuilder::build() {
	CommandPool pool;
	if (vkCreateCommandPool(dev.dev, &ci, nullptr, &pool.pool) != VK_SUCCESS) {
		throw std::runtime_error("failed to create command pool!");
	}
	else {
		pool.dev = dev;
	}
	return pool;
}

CommandPoolBuilder& CommandPoolBuilder::setCommandPoolCreateFlags(VkCommandPoolCreateFlags flags) {
	ci.flags = flags;
	return *this;
}

CommandPoolBuilder& CommandPoolBuilder::setQueueFamilyIndex(uint32_t index) {
	ci.queueFamilyIndex = index;
	return *this;
}

