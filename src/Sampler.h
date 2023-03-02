#pragma once
#include "vulkan/vulkan.h"
#include "export.h"

class Sampler {
public:
	VkSampler& value() {
		return sampler;
	}
private:
	VkSampler sampler;
};