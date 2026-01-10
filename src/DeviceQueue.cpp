#include "DeviceQueue.h"
#include "Fence.h"
#include <stdexcept>

void DeviceQueue::submit(const VkSubmitInfo& submitInfo, const Fence& fence) {
	if (vkQueueSubmit(que, 1, &submitInfo, fence.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit daw command buffer!");
	}
}

VkResult DeviceQueue::presentKHR(const VkPresentInfoKHR& presentInfo) {
	return vkQueuePresentKHR(que, &presentInfo);
}

void DeviceQueue::waitIdle() {
	VkResult result  = vkQueueWaitIdle(que);
	if (result != VK_SUCCESS) {
		throw std::runtime_error("device queue failed to wait idle!");
	}
}