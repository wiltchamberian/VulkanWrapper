#include "RenderPassBuilder.h"
#include <stdexcept>

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
	if (vkCreateRenderPass(dev.dev, &renderPassInfo, nullptr, &pass.pass) != VK_SUCCESS) {
		pass.pass = VK_NULL_HANDLE;
		throw std::runtime_error("failed to create render pass!");
	}
	return pass;
}

void RenderPassBuilder::setDevice(LogicalDevice d) {
	dev = d;
}

void RenderPassBuilder::setAttachments(const std::vector<VkAttachmentDescription>& vec) {
	attachmentDescriptions = vec;
}

void RenderPassBuilder::setSubpassDescriptions(const std::vector<VkSubpassDescription>& vec) {
	subpassDescriptions = vec;
}

void RenderPassBuilder::setSubpassDependencies(const std::vector<VkSubpassDependency>& vec) {
	subpassDependencies = vec;
}