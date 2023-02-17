#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "VulkanImage.h"
#include "LogicalDevice.h"
#include <vector>

class VULKAN_WRAPPER_API SwapChain {
public:
	std::vector<VkImage> getImages();
	
private:
	LogicalDevice dev;
	VkSwapchainKHR chain;
};
