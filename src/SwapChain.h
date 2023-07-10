#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "VulkanImage.h"
#include "LogicalDevice.h"
#include <vector>

class VULKAN_WRAPPER_API SwapChain {
public:
	friend class SwapChainBuilder;
	std::vector<VkImage> getImages();
	VkSwapchainKHR& value() {
		return chain;
	}
	bool isValid() const {
		return chain != VK_NULL_HANDLE;
	}
	const VkExtent2D& getExtent();
	const VkSurfaceFormatKHR& getSurfaceFormat();
private:
	LogicalDevice dev;
	VkSurfaceFormatKHR surfaceFormat;
	VkExtent2D extent;
	VkSwapchainKHR chain = VK_NULL_HANDLE;
};
