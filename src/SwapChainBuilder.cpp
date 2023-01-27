#include "SwapChainBuilder.h"
#include <stdexcept>

SwapChain SwapChainBuilder::build() {
	SwapChain chain;

	VkSwapchainCreateInfoKHR ci{};
	ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

	ci.flags = createflags;
	ci.surface = surface.surface;
	ci.minImageCount = minImageCount;
	ci.imageFormat = imageFormat;
	ci.imageColorSpace = imageColorSpace;
	ci.imageExtent = imageExtent;
	ci.imageArrayLayers = imageArrayLayers;
	ci.imageUsage = imageUsage;
	ci.imageSharingMode = imageSharingMode;
	ci.queueFamilyIndexCount = queueFamilyIndices.size();
	ci.pQueueFamilyIndices = queueFamilyIndices.data();
	ci.preTransform = preTransform;
	ci.compositeAlpha = compositeAlpha;
	ci.presentMode = presentMode;
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

SwapChainBuilder& SwapChainBuilder::setFormat(VkFormat format) {
	imageFormat = format;
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

SwapChainBuilder& SwapChainBuilder::setColorSpace(VkColorSpaceKHR space) {
	imageColorSpace = space;
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

SwapChainBuilder& SwapChainBuilder::setClipped(VkBool32 clip) {
	clipped = clip;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setOldSwapChain(SwapChain old) {
	oldSwapchain = old;
	return *this;
}