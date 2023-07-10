#include "SwapChain.h"

std::vector<VkImage> SwapChain::getImages(){
	std::vector<VkImage> imgs;
	uint32_t imageCount = 0;
	vkGetSwapchainImagesKHR(dev.dev, chain, &imageCount, nullptr);
	imgs.resize(imageCount);
	vkGetSwapchainImagesKHR(dev.dev, chain, &imageCount, imgs.data());
	return imgs;
}

const VkExtent2D& SwapChain::getExtent() {
	return extent;
}

const VkSurfaceFormatKHR& SwapChain::getSurfaceFormat() {
	return surfaceFormat;
}