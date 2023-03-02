#pragma once
#include "vulkan/vulkan.h"

class DescriptorSetLayout {
public:
	VkDescriptorSetLayout& value() {
		return layout;
	}
private:
	VkDescriptorSetLayout layout;
};