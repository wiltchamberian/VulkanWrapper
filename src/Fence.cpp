#include "Fence.h"
#include <cassert>

void Fence::reset() {
	vkResetFences(dev.value(), 1, &fence);
}

void Fence::wait(uint64_t timeout) {
	vkWaitForFences(dev.value(), 1, &fence, VK_TRUE, timeout);
}

void Fence::cleanUp() {
	vkDestroyFence(dev.value(), fence, nullptr);
}

FenceGroup& FenceGroup::addFence(Fence fence) {
	assert(dev.value() == fence.dev.value());
	fences.push_back(fence.value());
	return *this;
}

void FenceGroup::reset() {
	vkResetFences(dev.value(), fences.size() , fences.data());
}

void FenceGroup::wait(VkBool32 waitAll, uint64_t timeout) {
	vkWaitForFences(dev.value(), fences.size(), fences.data(), waitAll, timeout);
}

void FenceGroup::cleanUp() {
	for (int i = 0; i < fences.size(); ++i) {
		vkDestroyFence(dev.value(), fences[i], nullptr);
	}
}