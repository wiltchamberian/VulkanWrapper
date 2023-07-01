#pragma once
#include "vulkan/vulkan.h"
#include "export.h"

class VULKAN_WRAPPER_API Sampler {
public:
	VkSampler& value() {
		return sampler;
	}
private:
	VkSampler sampler;
};