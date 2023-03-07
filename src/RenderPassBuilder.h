#pragma once
#include <vector>
#include "vulkan/vulkan.h"
#include "RenderPass.h"
#include "LogicalDevice.h"

class RenderPassBuilder {
public:
	RenderPass build();
	void setDevice(LogicalDevice dev);
	void setAttachments(const std::vector<VkAttachmentDescription>& vec);
	void setSubpassDescriptions(const std::vector<VkSubpassDescription>& vec);
	void setSubpassDependencies(const std::vector<VkSubpassDependency>& vec);
private:
	LogicalDevice dev;
	std::vector<VkAttachmentDescription> attachmentDescriptions;
	std::vector<VkSubpassDescription> subpassDescriptions;
	std::vector<VkSubpassDependency> subpassDependencies;
};