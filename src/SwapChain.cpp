#include "SwapChain.h"
#include "Semaphore.h"
#include "Fence.h"
#include <stdexcept>

std::vector<VkImage> SwapChain::getImages(){
	std::vector<VkImage> imgs;
	uint32_t imageCount = 0;
	vkGetSwapchainImagesKHR(dev.value(), chain, &imageCount, nullptr);
	imgs.resize(imageCount);
	vkGetSwapchainImagesKHR(dev.value(), chain, &imageCount, imgs.data());
	return imgs;
}

const VkExtent2D& SwapChain::getExtent() {
	return extent;
}

const VkSurfaceFormatKHR& SwapChain::getSurfaceFormat() {
	return surfaceFormat;
}

uint32_t SwapChain::acquireNextImageKHR(uint64_t timeout, const Semaphore& semaphore, const Fence& fence) {
	uint32_t index = 0;
	if (VK_SUCCESS != vkAcquireNextImageKHR(dev.value(), chain, timeout, semaphore.value(), fence.value(), &index)) {
		throw std::runtime_error("fail to acuqire next image!");
	}
	return index;
}