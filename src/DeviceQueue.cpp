#include "DeviceQueue.h"
#include "Fence.h"
#include <stdexcept>

void DeviceQueue::submit(const VkSubmitInfo& submitInfo, const Fence& fence) {
	if (vkQueueSubmit(que, 1, &submitInfo, fence.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to submit daw command buffer!");
	}
}

void DeviceQueue::presentKHR(const VkPresentInfoKHR& presentInfo) {
	if (vkQueuePresentKHR(que, &presentInfo) != VK_SUCCESS) {
		throw std::runtime_error("failed to presentKHR!");
	}
}