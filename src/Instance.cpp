#include "Instance.h"
#include "PhysicalDevice.h"
#include "Surface.h"
#include <vector>
#include <stdexcept>


PhysicalDevice VulkanInstance::selectPhysicalDevice(VkQueueFlags flags, Surface surface, SwapChainSupportDetails support, const std::vector<std::string>& extensions, PhysicalDeviceFilter filter) {
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
        VkPhysicalDeviceProperties deviceProperties;
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
        bingo = true;
        if (filter != nullptr && !filter(deviceProperties, deviceFeatures)) {
            bingo = false;
        }
        if (!dev.isDeviceSuitable(flags, surface, support)) {
            bingo = false;
        }
        if (bingo) {
            break;
        }
    }

    if (bingo == false) {
        dev.value() = VK_NULL_HANDLE;
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    return dev;
}

void VulkanInstance::clearUp() {
    vkDestroyInstance(vk, nullptr);
    vk = VK_NULL_HANDLE;
}
