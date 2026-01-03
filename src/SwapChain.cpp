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

void SwapChain::cleanUp() {
	vkDestroySwapchainKHR(dev.value(), chain, nullptr);
}

const VkExtent2D& SwapChain::getExtent() {
	return extent;
}

const VkSurfaceFormatKHR& SwapChain::getSurfaceFormat() {
	return surfaceFormat;
}

VkResult SwapChain::acquireNextImageKHR(uint64_t timeout, const Semaphore& semaphore, const Fence& fence, uint32_t& index) {
	VkResult result = vkAcquireNextImageKHR(dev.value(), chain, timeout, semaphore.value(), fence.value(), &index);
	return result;
}