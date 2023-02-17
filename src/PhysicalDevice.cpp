#include "PhysicalDevice.h"
#include <vector>
#include <stdexcept>
#include "LogicalDevice.h"
#include "Common.h"

bool PhysicalDevice::isDeviceSuitable(VkQueueFlags flags) {
    auto indices = findFamilyQueues(flags);
    return indices.isComplete(flags);
}

SwapChainSupportDetails PhysicalDevice::querySwapChainSupport(Surface surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface.value(), &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface.value(), &formatCount, nullptr);

    if (formatCount != 0) {
        details.formats.resize(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface.value(), &formatCount, details.formats.data());
    }

    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface.value(), &presentModeCount, nullptr);

    if (presentModeCount != 0) {
        details.presentModes.resize(presentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface.value(), &presentModeCount, details.presentModes.data());
    }

    return details;
}

QueueFamilyIndices PhysicalDevice::findFamilyQueues(VkQueueFlags flags) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

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
            break;
        }
        ++i;
    }
    return indices;
}

LogicalDevice PhysicalDevice::createLogicalDevice(VkQueueFlags flags) {

    QueueFamilyIndices indices = findFamilyQueues(flags);

    VkDeviceQueueCreateInfo queueCreateInfo{};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;

    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;
    createInfo.enabledLayerCount = 0;
#if 0
    if (enableValidationLayers) {
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }
#endif

    LogicalDevice logicalDevice;
    logicalDevice.indices_ = indices;
    if (vkCreateDevice(dev, &createInfo, nullptr, &logicalDevice.dev) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    //vkGetDeviceQueue(logicalDevice.dev, indices.graphicsFamily.value(), 0, &graphicsQueue);

    return logicalDevice;

}