#pragma once
#include <vector>
#include "LogicalDevice.h"
#include "DescriptorSetLayout.h"

class DescriptorSetLayoutBuilder {
public:
	DescriptorSetLayout build();
	void setDevice(LogicalDevice d);
	void setDescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags f);
	void setVkDescriptorSetLayoutBindings(const std::vector< VkDescriptorSetLayoutBinding>& vec);
private:
	LogicalDevice                              dev;
	VkDescriptorSetLayoutCreateFlags           flags;
	std::vector< VkDescriptorSetLayoutBinding> bindings;
};