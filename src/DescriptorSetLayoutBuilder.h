#pragma once
#include <vector>
#include "LogicalDevice.h"
#include "DescriptorSetLayout.h"

class DescriptorSetLayoutBuilder {
public:
	DescriptorSetLayout build();
	DescriptorSetLayoutBuilder& setDevice(LogicalDevice d);
	DescriptorSetLayoutBuilder& setDescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags f);
	DescriptorSetLayoutBuilder& setVkDescriptorSetLayoutBindings(const std::vector< VkDescriptorSetLayoutBinding>& vec);
private:
	LogicalDevice                              dev;
	VkDescriptorSetLayoutCreateFlags           flags;
	std::vector< VkDescriptorSetLayoutBinding> bindings;
};