#include "SwapChainBuilder.h"
#include <stdexcept>

SwapChainBuilder::SwapChainBuilder(LogicalDevice& dev, Surface& surf)
	:logicalDev(dev)
	, surface(surf)
{


}

SwapChainSupportDetails& SwapChainBuilder::querySwapChainSupport() {
	if (logicalDev.physical_device().isValid() && surface.isValid()) {
		VkSurfaceCapabilitiesKHR cap;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(logicalDev.physical_device().value(), surface.value(), &cap);
		details.capabilities = cap;

		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.physical_device().value(), surface.value(), &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.physical_device().value(), surface.value(), &formatCount, details.formats.data());
		}

		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.physical_device().value(), surface.value(), &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.physical_device().value(), surface.value(), &presentModeCount, details.presentModes.data());
		}
	}
	
	return details;
}

SwapChain SwapChainBuilder::build() {
	SwapChain chain;

	VkSwapchainCreateInfoKHR ci{};
	ci.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;

	ci.flags = createflags;
	ci.surface = surface.value();
	if (!minImageCount.has_value()) {
		setDefaultMinImageCount();
		if (minImageCount.has_value()) {
			ci.minImageCount = minImageCount.value();
		}
		else {
			return chain;
		}
	}
	else {
		ci.minImageCount = minImageCount.value();
	}
	if (surfaceFormat.has_value()) {
		ci.imageFormat = surfaceFormat.value().format;
		ci.imageColorSpace = surfaceFormat.value().colorSpace;
	}
	else {
		return chain;
	}
	
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
	ci.oldSwapchain = oldSwapchain.value();

	if (vkCreateSwapchainKHR(logicalDev.value(), &ci, nullptr, &chain.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create swap chain!");
	}
	else {
		chain.surfaceFormat = surfaceFormat.value();
		chain.extent = ci.imageExtent;
		chain.dev = logicalDev;
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

SwapChainBuilder& SwapChainBuilder::setSurfaceFormat(VkSurfaceFormatKHR form, VkSurfaceFormatKHR defaultFormat) {
	surfaceFormat = form;
	std::vector<VkSurfaceFormatKHR> vec;
	if (logicalDev.isValid() && logicalDev.physical_device().isValid()) {
		vec = logicalDev.physical_device().queryPhysicalDeviceSurfaceFormats(surface);
		for (auto& it : vec) {
			if (form.format == it.format && form.colorSpace == it.colorSpace) {
				surfaceFormat = it;
			}
		}
	}
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

SwapChainBuilder& SwapChainBuilder::setDefaultMinImageCount() {
	if (details.capabilities.has_value()) {
		uint32_t imgCount = details.capabilities.value().minImageCount + 1;
		if (details.capabilities.value().maxImageCount > 0 && imgCount > details.capabilities.value().maxImageCount) {
			imgCount = details.capabilities.value().maxImageCount;
		}
		minImageCount = imgCount;
	}
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setImageExtent(VkExtent2D extent, VkExtent2D defaultExtent) {
	imageExtent = defaultExtent;
	if (logicalDev.isValid() && logicalDev.physical_device().isValid() && surface.isValid()) {
		VkSurfaceCapabilitiesKHR cap = logicalDev.physical_device().queryPhysicalDeviceSurfaceCapabilities(surface);
		if (cap.minImageExtent.width <= extent.width &&
			cap.minImageExtent.height <= extent.height
			&& extent.width <= cap.maxImageExtent.width
			&& extent.height <= cap.maxImageExtent.height) {
			imageExtent = extent;
		}
	}
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

SwapChainBuilder& SwapChainBuilder::setImageSharingMode(VkSharingMode mode) {
	imageSharingMode = mode;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setQueueFamilyIndices(const std::vector<uint32_t>& indices) {
	queueFamilyIndices = indices;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setPreTransform(VkSurfaceTransformFlagBitsKHR bits) {
	preTransform = bits;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setCompositeAlpha(VkCompositeAlphaFlagBitsKHR flags) {
	compositeAlpha = flags;
	return *this;
}

SwapChainBuilder& SwapChainBuilder::setPresentMode(VkPresentModeKHR mode, VkPresentModeKHR defaultMode) {
	presentMode = mode;
	std::vector<VkPresentModeKHR> vec;
	if (logicalDev.isValid() && logicalDev.physical_device().isValid()) {
		vec = logicalDev.physical_device().queryPhysicalDeviceSurfacePresentModes(surface);
		for (auto& it : vec) {
			if (mode == it) {
				presentMode = it;
			}
		}
	}
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
	if (logicalDev.physical_device().isValid() && surface.isValid()) {
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(logicalDev.physical_device().value(), surface.value(), &details.capabilities.value());
	}
}

void SwapChainBuilder::queryPhysicalDeviceSurfaceFormats() {
	details.formats.clear();
	if (logicalDev.physical_device().isValid() && surface.isValid()) {
		uint32_t formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.physical_device().value(), surface.value(), &formatCount, nullptr);
		if (formatCount != 0) {
			details.formats.resize(formatCount);
			vkGetPhysicalDeviceSurfaceFormatsKHR(logicalDev.physical_device().value(), surface.value(), &formatCount, details.formats.data());
		}
	}
}

void SwapChainBuilder::queryPhysicalDeviceSurfacePresentModes() {
	details.presentModes.clear();
	if (logicalDev.physical_device().isValid() && surface.isValid()) {
		uint32_t presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.physical_device().value(), surface.value(), &presentModeCount, nullptr);
		if (presentModeCount != 0) {
			details.presentModes.resize(presentModeCount);
			vkGetPhysicalDeviceSurfacePresentModesKHR(logicalDev.physical_device().value(), surface.value(), &presentModeCount, details.presentModes.data());
		}
	}
}
