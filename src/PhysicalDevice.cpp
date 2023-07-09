#include "PhysicalDevice.h"
#include <vector>
#include <set>
#include <stdexcept>
#include "LogicalDevice.h"
#include "Surface.h"
#include "Common.h"
#include "Tools.h"

bool PhysicalDevice::isDeviceSuitable(VkQueueFlags flags, Surface surface, const std::vector<std::string>& extensions) {
    QueueFamilyIndices indices = findQueueFamilies(flags, surface);
    bool extensionsSupported = checkDeviceExtensionSupport(extensions);
    bool swapChainSupported = false;
    if (extensionsSupported) {
        SwapChainSupportDetails details = querySwapChainSupport(surface);
        swapChainSupported = !details.formats.empty() && !details.presentModes.empty();
    }

    return indices.isComplete(flags) && extensionsSupported && swapChainSupported;
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

QueueFamilyIndices PhysicalDevice::findQueueFamilies(VkQueueFlags flags, Surface surface) {
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
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(dev, j, surface.value(), &presentSupport);
        if (presentSupport) {
            indices.indexMap[help::log2((uint64_t)(QUEUE_PRESENT_BIT))] = j;
        }
        if (indices.isComplete(flags)) {
            break;
        }
        ++j;
    }
    return indices;
}

bool PhysicalDevice::checkDeviceExtensionSupport(const std::vector<std::string>& extensions) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(dev, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(extensions.begin(), extensions.end());

    for (const auto& extension : availableExtensions) {
        requiredExtensions.erase(extension.extensionName);
    }

    return requiredExtensions.empty();

}

bool PhysicalDevice::checkSwapChainSupport(const SwapChainSupportDetails & details, Surface surface) {
    // 自定义比较器
    struct CustomComparator {
        bool operator()(const VkSurfaceFormatKHR& a, const VkSurfaceFormatKHR& b) const {
            return ((a.format < b.format) || (a.colorSpace < b.colorSpace)) && (!(a.format > b.format));
        }
    };
    
    SwapChainSupportDetails supportDetails = querySwapChainSupport(surface);
    std::set< VkSurfaceFormatKHR, CustomComparator> formats(details.formats.begin(),details.formats.end());
    std::set< VkPresentModeKHR> presentModes(details.presentModes.begin(), details.presentModes.end());
    //std::set< VkSurfaceCapabilitiesKHR> capabilities;
    //if (details.capabilities.has_value()) {
    //    capabilities.insert(details.capabilities.value());
    //} 
    for (int i = 0; i < supportDetails.formats.size(); ++i) {
        formats.erase(supportDetails.formats[i]);
    }
    for (int i = 0; i < supportDetails.presentModes.size(); ++i) {
        presentModes.erase(supportDetails.presentModes[i]);
    }
    //if (supportDetails.capabilities.has_value()) {
    //    capabilities.erase(supportDetails.capabilities.value());
    //}
    return formats.empty() && presentModes.empty()/* && capabilities.empty()*/;
}

VkSurfaceCapabilitiesKHR PhysicalDevice::queryPhysicalDeviceSurfaceCapabilities(Surface surface) {
    VkSurfaceCapabilitiesKHR cap{};
    if (surface.isValid()) {
        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(dev, surface.value(), &cap);
    }
    return cap;
}

std::vector<VkSurfaceFormatKHR> PhysicalDevice::queryPhysicalDeviceSurfaceFormats(Surface surface) {
    std::vector<VkSurfaceFormatKHR> formats;
    formats.clear();
    if (surface.isValid()) {
        uint32_t formatCount = 0;
        vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface.value(), &formatCount, nullptr);
        if (formatCount != 0) {
            formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(dev, surface.value(), &formatCount, formats.data());
        }
    }
    return formats;
}

std::vector<VkPresentModeKHR> PhysicalDevice::queryPhysicalDeviceSurfacePresentModes(Surface surface) {
    std::vector<VkPresentModeKHR> presents;
    if (surface.isValid()) {
        uint32_t presentModeCount = 0;
        vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface.value(), &presentModeCount, nullptr);
        if (presentModeCount != 0) {
            presents.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(dev, surface.value(), &presentModeCount, presents.data());
        }
    }
    return presents;
}

LogicalDevice PhysicalDevice::createLogicalDevice(VkQueueFlags flags, VkPhysicalDeviceFeatures deviceFeatures, const std::vector<std::string>& extensions) {
    std::vector<VkDeviceQueueCreateInfo> vec;
    std::set<uint32_t> uniqueQueueFamilies;
    const int queueFlagsBitsNum = 8;
    for (int i = 0; i < queueFlagsBitsNum; ++i) {
        VkQueueFlags bit = 1 << i;
        if (flags & bit) {
            if (indices.indexMap[i].has_value()) {
                uniqueQueueFamilies.insert(indices.indexMap[i].value());
            }
        }
    }

    for (uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;
        //TODO: set priority by human
        float queuePriority = 1.0f;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        vec.push_back(queueCreateInfo);
    }

    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.pQueueCreateInfos = vec.data();
    createInfo.queueCreateInfoCount = vec.size();

    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = 0;
    createInfo.enabledLayerCount = 0;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    std::vector<const char*> deviceExtensions(extensions.size());
    for (int i = 0; i < deviceExtensions.size(); ++i) {
        deviceExtensions[i] = extensions[i].c_str();
    }
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
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