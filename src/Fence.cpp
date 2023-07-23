#include "Fence.h"
#include <cassert>

void Fence::cleanUp() {
	vkDestroyFence(dev.value(), fence, nullptr);
}

FenceGroup& FenceGroup::addFence(Fence fence) {
	assert(dev.value() == fence.dev.value());
	fences.push_back(fence.value());
	return *this;
}

void FenceGroup::cleanUp() {
	for (int i = 0; i < fences.size(); ++i) {
		vkDestroyFence(dev.value(), fences[i], nullptr);
	}
}