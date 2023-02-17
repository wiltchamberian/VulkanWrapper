#include "SwapChainBuilder.h"
#include <stdexcept>

SwapChainBuilder::SwapChainBuilder(const LogicalDevice& dev, const Surface& surf)
	:logicalDev(dev)
	, surface(surf)
{


}

SwapChainSupportDetails SwapChainBuilder::querySwapChainSupport() {
	SwapChainSupportDetails details;

	if (logicalDev.phy_dev.isValid() && surface.isValid()) {
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(logicalDev.phy_dev.dev, surface.surface, &details.capabilities);

		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.phy_dev.dev, surface.surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.phy_dev.dev, surface.surface, &formatCount, details.formats.data());
		}

		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.phy_dev.dev, surface.surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.phy_dev.dev, surface.surface, &presentModeCount, details.presentModes.data());
		}

	}
	
	return details;
}

SwapChain SwapChainBuilder::build() {
	SwapChain chain;

	VkSwapchainCreateInfoKHR ci{};
	ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

	ci.flags = createflags;
	ci.surface = surface.surface;
	ci.minImageCount = minImageCount;
	ci.imageFormat = surfaceFormat.value().format;
	ci.imageColorSpace = surfaceFormat.value().colorSpace;
	ci.imageExtent = imageExtent;
	ci.imageArrayLayers = imageArrayLayers;
	ci.imageUsage = imageUsage;
	ci.imageSharingMode = imageSharingMode;
	ci.queueFamilyIndexCount = queueFamilyIndices.size();
	ci.pQueueFamilyIndices = queueFamilyIndices.data();
	ci.preTransform = preTransform;
	ci.compositeAlpha = compositeAlpha;
	ci.presentMode = presentMode.value();
	ci.clipped = clipped;
	ci.oldSwapchain = oldSwapchain.chain;

	if (vkCreateSwapchainKHR(logicalDev.dev, &ci, nullptr, &chain.chain) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}

	return chain;
}

SwapChainBuilder& SwapChainBuilder::setLogicalDevice(LogicalDevice dev) {
	logicalDev = dev;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setSurface(const Surface& surf) {
	surface = surf;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setSurfaceFormat(VkSurfaceFormatKHR form) {
	surfaceFormat = form;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setSurfaceFormatCheck(VkSurfaceFormatKHR surfFormat) {
	if (details.formats.empty()) {
		queryPhysicalDeviceSurfaceFormats();
	}
	for (const auto& availablePresentMode : details.formats) {
		if (availablePresentMode.format == surfFormat.format 
			&& availablePresentMode.colorSpace == surfFormat.colorSpace
			) 
		{
			surfaceFormat = availablePresentMode;
			return *this;
		}
	}
	surfaceFormat.reset();
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setCreateFlags(VkSwapchainCreateFlagsKHR flgs) {
	createflags = flgs;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setMinImageCount(uint32_t imageCount) {
	minImageCount = imageCount;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setExtent2D(VkExtent2D extent) {
	imageExtent = extent;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setImageArrayLayers(uint32_t layers) {
	imageArrayLayers = layers;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setImageUsageFlags(VkImageUsageFlags flags) {
	imageUsage = flags;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setSharingMode(VkSharingMode mode) {
	imageSharingMode = mode;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setQueueFamilyIndices(const std::vector<uint32_t>& indices) {
	queueFamilyIndices = indices;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setSurfaceTransform(VkSurfaceTransformFlagBitsKHR bits) {
	preTransform = bits;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setCompositeAlpha(VkCompositeAlphaFlagBitsKHR flags) {
	compositeAlpha = flags;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setPresentMode(VkPresentModeKHR mode) {
	presentMode = mode;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setPresentModeCheck(VkPresentModeKHR pm) {
	if (details.presentModes.empty()) {
		queryPhysicalDeviceSurfacePresentModes();
	}
	for (const auto& availablePresentMode : details.presentModes) {
		if (availablePresentMode == pm) {
			presentMode = availablePresentMode;
			return *this;
		}
	}
	presentMode.reset();
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setClipped(VkBool32 clip) {
	clipped = clip;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setOldSwapChain(SwapChain old) {
	oldSwapchain = old;
	return *this;
}

void SwapChainBuilder::queryPhysicalDeviceSurfaceCapabilities() {
	if (logicalDev.phy_dev.isValid() && surface.isValid()) {
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(logicalDev.phy_dev.dev, surface.surface, &details.capabilities);
	}
}

void SwapChainBuilder::queryPhysicalDeviceSurfaceFormats() {
	details.formats.clear();
	if (logicalDev.phy_dev.isValid() && surface.isValid()) {
		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.phy_dev.dev, surface.surface, &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.phy_dev.dev, surface.surface, &formatCount, details.formats.data());
		}
	}
}

void SwapChainBuilder::queryPhysicalDeviceSurfacePresentModes() {
	details.presentModes.clear();
	if (logicalDev.phy_dev.isValid() && surface.isValid()) {
		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.phy_dev.dev, surface.surface, &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.phy_dev.dev, surface.surface, &presentModeCount, details.presentModes.data());
		}
	}
}
