#pragma once
#include "export.h"
#include "vulkan/vulkan.h"

class VULKAN_WRAPPER_API DescriptorSetLayout {
public:
	VkDescriptorSetLayout& value() {
		return layout;
	}
private:
	VkDescriptorSetLayout layout;
};