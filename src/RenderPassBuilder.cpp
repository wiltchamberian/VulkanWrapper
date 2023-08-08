#include "RenderPassBuilder.h"
#include <stdexcept>

RenderPassBuilder::RenderPassBuilder(const LogicalDevice& d)
:dev(d){

}

RenderPass RenderPassBuilder::build() {
	RenderPass pass;
	VkRenderPassCreateInfo renderPassInfo{};
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.pAttachments = attachmentDescriptions.data();
	renderPassInfo.attachmentCount = attachmentDescriptions.size();
	renderPassInfo.pSubpasses = subpassDescriptions.data();
	renderPassInfo.subpassCount = subpassDescriptions.size();
	renderPassInfo.pDependencies = subpassDependencies.data();
	renderPassInfo.dependencyCount = subpassDependencies.size();
	if (vkCreateRenderPass(dev.value(), &renderPassInfo, nullptr, &pass.value()) != VK_SUCCESS) {
		pass.value() = VK_NULL_HANDLE;
		throw std::runtime_error("failed to create render pass!");
	}
	else {
		pass.dev = dev;
	}
	return pass;
}

RenderPassBuilder& RenderPassBuilder::setAttachments(const std::vector<VkAttachmentDescription>& vec) {
	attachmentDescriptions = vec;
	return *this;
}

RenderPassBuilder& RenderPassBuilder::setSubpassDescriptions(const std::vector<VkSubpassDescription>& vec) {
	subpassDescriptions = vec;
	return *this;
}

RenderPassBuilder& RenderPassBuilder::setSubpassDependencies(const std::vector<VkSubpassDependency>& vec) {
	subpassDependencies = vec;
	return *this;
}