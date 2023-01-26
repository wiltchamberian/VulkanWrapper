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
        dev.dev = device;
        if (isDeviceSuitable(dev,flags)) {
            bingo = true;
            break;
        }
    }

    if (bingo == false) {
        dev.dev = VK_NULL_HANDLE;
        throw std::runtime_error("failed to find a suitable GPU!");
    }

    return dev;
}

bool VulkanInstance::isDeviceSuitable(PhysicalDevice& dev, VkQueueFlags flags) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(dev.dev, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(dev.dev, &queueFamilyCount, queueFamilies.data());

    int i = 0;
    for (const auto& queueFamily : queueFamilies) {
        VkQueueFlags ans = (queueFamily.queueFlags & flags);
        if (ans) {
            if (ans & VK_QUEUE_GRAPHICS_BIT) {
                if (!indices.graphicsFamily.has_value()) {
                    indices.graphicsFamily = i;
                }
            }
            if (ans & VK_QUEUE_COMPUTE_BIT) {
                if (!indices.computeFamily.has_value()) {
                    indices.computeFamily = i;
                }
            }
            if (ans & VK_QUEUE_TRANSFER_BIT) {
                if (!indices.transferFamily.has_value()) {
                    indices.transferFamily = i;
                }
            }
            if (ans & VK_QUEUE_SPARSE_BINDING_BIT) {
                if (!indices.sparseBindingFamily.has_value()) {
                    indices.sparseBindingFamily = i;
                }
            }
            if (ans & VK_QUEUE_PROTECTED_BIT) {
                if (!indices.protectedFamily.has_value()) {
                    indices.protectedFamily = i;
                }
            }
        }
        if (indices.isComplete(flags)) {
            dev.indices = indices;
            return true;
        }
        ++i;
    }

    return false;

}