#include <stdexcept>
#include "PipelineLayoutBuilder.h"

PipelineLayout PipelineLayoutBuilder::build() {
	PipelineLayout layout;
	VkPipelineLayoutCreateInfo ci = {};
	ci.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	ci.pSetLayouts = (VkDescriptorSetLayout*)layouts.data();
	ci.setLayoutCount = layouts.size();
	ci.pPushConstantRanges = pushConstantRanges.data();
	ci.pushConstantRangeCount = pushConstantRanges.size();
	VkResult suc = vkCreatePipelineLayout(dev.value(), &ci, nullptr, &(layout.value()));
	if (suc != VK_SUCCESS) {
		throw std::runtime_error("failed to create pipelineLayout!");
	}
	return layout;
}

PipelineLayoutBuilder::PipelineLayoutBuilder(LogicalDevice d) 
:dev(d)
{
}

PipelineLayoutBuilder& PipelineLayoutBuilder::setPipelineLayoutCreateFlags(VkPipelineLayoutCreateFlags flgs) {
	flags = flgs;
	return *this;
}

PipelineLayoutBuilder& PipelineLayoutBuilder::setDescriptorSetLayouts(const std::vector<DescriptorSetLayout>& vec) {
	layouts = vec;
	return *this;
}

PipelineLayoutBuilder& PipelineLayoutBuilder::setPushConstantRanges(const std::vector<VkPushConstantRange>& vec) {
	pushConstantRanges = vec;
	return *this;
}