#ifndef __FENCE_H
#define __FENCE_H

#include "export.h"
#include "vulkan/vulkan.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API Fence {
public:
	friend class FenceBuilder;
	friend class FenceGroup;
	VkFence& value() { return fence; }
	const VkFence& value() const { return fence; }
	const VkFence* data() const { return &fence;  }
	void reset();
	void wait(uint64_t timeout);
	void cleanUp();
private:
	LogicalDevice dev;
	VkFence fence = VK_NULL_HANDLE;
};

class VULKAN_WRAPPER_API FenceGroup {
public:
	friend class FenceBuilder;
	FenceGroup& addFence(Fence fence);
	const VkFence* data() const { return fences.data(); } 
	size_t size() const { return  fences.size(); }
	void cleanUp();
	void wait(VkBool32 waitAll, uint64_t timeout);
	void reset();
private:
	LogicalDevice dev;
	std::vector<VkFence> fences;
};


#endif