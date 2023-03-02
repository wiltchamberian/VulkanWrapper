#include "DescriptorSetLayoutBuilder.h"
#include <stdexcept>

DescriptorSetLayout DescriptorSetLayoutBuilder::build() {
	DescriptorSetLayout layout;
	VkDescriptorSetLayoutCreateInfo ci = {};
	ci.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	ci.flags = flags;
	ci.bindingCount = bindings.size();
	ci.pBindings = bindings.data();
	
	auto suc = vkCreateDescriptorSetLayout(dev.dev,&ci , nullptr, &layout.value());
	if (suc != VK_SUCCESS) {
		throw std::runtime_error("failed to create DescriptorSetLayout!");
	}
	return layout;
}

void DescriptorSetLayoutBuilder::setDevice(LogicalDevice d) {

}

void DescriptorSetLayoutBuilder::setDescriptorSetLayoutCreateFlags(VkDescriptorSetLayoutCreateFlags f) {
	flags = f;
}

void DescriptorSetLayoutBuilder::setVkDescriptorSetLayoutBindings(const std::vector< VkDescriptorSetLayoutBinding>& vec) {
	bindings = vec;
}