#include "FenceBuilder.h"
#include <stdexcept>

FenceBuilder::FenceBuilder(LogicalDevice d)
:dev(d)
{
	ci.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	ci.pNext = nullptr;
}

Fence FenceBuilder::build() {
	Fence fence;
	if (vkCreateFence(dev.value(), &ci, nullptr, &fence.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create fence!");
	}
	else {
		fence.dev = dev;
	}
	return fence;
}

FenceBuilder& FenceBuilder::setFenceCreateFlags(VkFenceCreateFlags flags) {
	ci.flags = flags;
	return *this;
}