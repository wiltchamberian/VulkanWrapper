#include "Instance.h"
#include <vector>
#include <stdexcept>

PhysicalDevice VulkanInstance::selectPhysicalDevice(VkQueueFlags flags) {
	PhysicalDevice dev;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vk, &deviceCount, nullptr);

    if (deviceCount == 0) {
        throw std::runtime_error("failed to find GPUs with Vulkan support!");
        return dev;
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(vk, &deviceCount, devices.data());

    bool bingo = false;
    for (const auto& device : devices) {
        dev.value() = device;
        if (dev.isDeviceSuitable(flags)) {
            bingo = true;
            break;
        }
    }

    if (bingo == false) {
        dev.value() = VK_NULL_HANDLE;
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    return dev;
}
