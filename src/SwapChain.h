#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "VulkanImage.h"
#include "LogicalDevice.h"
#include <vector>

class VULKAN_WRAPPER_API SwapChain {
public:
	std::vector<VkImage> getImages();
	VkSwapchainKHR& value() {
		return chain;
	}
	bool isValid() const {
		return chain != VK_NULL_HANDLE;
	}
private:
	LogicalDevice dev;
	VkSwapchainKHR chain = VK_NULL_HANDLE;
};
