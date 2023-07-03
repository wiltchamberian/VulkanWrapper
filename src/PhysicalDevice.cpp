#include "PhysicalDevice.h"
#include <vector>
#include <stdexcept>
#include "LogicalDevice.h"
#include "Common.h"

bool PhysicalDevice::isDeviceSuitable(VkQueueFlags flags) {
    auto indices = findQueueFamilies(flags);
    return indices.isComplete(flags);
}

SwapChainSupportDetails PhysicalDevice::querySwapChainSupport(Surface surface) {
    SwapChainSupportDetails details;

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface.value(), &details.capabilities.value());

    uint32_t formatCount = 0;
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

QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkQueueFlags flags) {
    QueueFamilyIndices indices;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(dev, &queueFamilyCount, queueFamilies.data());

    int j = 0;
    const int queueFlagsBitsNum = 8;
    indices.indexMap.resize(queueFlagsBitsNum);
    for (const auto& queueFamily : queueFamilies) {
        VkQueueFlags ans = (queueFamily.queueFlags & flags);
        VkQueueFlags ds = 1;
        for (int i = 0; i < queueFlagsBitsNum; ++i) {
            ds = 1 << i;
            if ((ans & ds) != 0) {
                if (!indices.indexMap[i].has_value()) {
                    indices.indexMap[i] = j;
                }
            }
        }
        if (indices.isComplete(flags)) {
            break;
        }
        ++j;
    }
    return indices;
}

LogicalDevice PhysicalDevice::createLogicalDevice(VkQueueFlags flags, VkPhysicalDeviceFeatures deviceFeatures) {
    QueueFamilyIndices indices = findQueueFamilies(flags);

    std::vector<VkDeviceQueueCreateInfo> vec;
    const int queueFlagsBitsNum = 8;
    for (int i = 0; i < queueFlagsBitsNum; ++i) {
        VkQueueFlags bit = 1 << i;
        if (flags & bit) {
            if (indices.indexMap[i].has_value()) {
                VkDeviceQueueCreateInfo queueCreateInfo{};
                queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
                queueCreateInfo.queueFamilyIndex = indices.indexMap[i].value();
                queueCreateInfo.queueCount = 1;
                //TODO: set priority by human
                float queuePriority = 1.0f;
                queueCreateInfo.pQueuePriorities = &queuePriority;
                vec.push_back(queueCreateInfo);
            }
        }
    }

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = vec.data();
    createInfo.queueCreateInfoCount = vec.size();

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
    logicalDevice.indices = indices;
    if (vkCreateDevice(dev, &createInfo, nullptr, &logicalDevice.dev) != VK_SUCCESS) {
        throw std::runtime_error("failed to create logical device!");
    }

    return logicalDevice;

}