#pragma once
#include "export.h"
#include <vector>
#include "vulkan/vulkan.h"
#include "RenderPass.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API RenderPassBuilder {
public:
	RenderPass build();
	RenderPassBuilder& setDevice(LogicalDevice dev);
	RenderPassBuilder& setAttachments(const std::vector<VkAttachmentDescription>& vec);
	RenderPassBuilder& setSubpassDescriptions(const std::vector<VkSubpassDescription>& vec);
	RenderPassBuilder& setSubpassDependencies(const std::vector<VkSubpassDependency>& vec);
private:
	LogicalDevice dev;
	std::vector<VkAttachmentDescription> attachmentDescriptions;
	std::vector<VkSubpassDescription> subpassDescriptions;
	std::vector<VkSubpassDependency> subpassDependencies;
};