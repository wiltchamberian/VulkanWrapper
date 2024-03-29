#ifndef __SWAP_CHAIN_BUILDER_H
#define __SWAP_CHAIN_BUILDER_H

#include <optional>
#include "export.h"
#include "Surface.h"
#include "SwapChain.h"
#include "LogicalDevice.h"


class VULKAN_WRAPPER_API SwapChainBuilder {
public:
    SwapChainBuilder(LogicalDevice& dev, Surface& surface);

    SwapChain build();

    SwapChainSupportDetails& querySwapChainSupport();
    SwapChainBuilder& setLogicalDevice(LogicalDevice dev);
	SwapChainBuilder& setSurface(const Surface& surface);
    SwapChainBuilder& setSurfaceFormat(VkSurfaceFormatKHR, VkSurfaceFormatKHR defaultFormat);
    [[deprecated]]
    SwapChainBuilder& setSurfaceFormatCheck(VkSurfaceFormatKHR);
    SwapChainBuilder& setCreateFlags(VkSwapchainCreateFlagsKHR flgs);
    SwapChainBuilder& setMinImageCount(uint32_t imageCount);
    SwapChainBuilder& setDefaultMinImageCount();
    SwapChainBuilder& setImageExtent(VkExtent2D extent, VkExtent2D defaultExtent);
    SwapChainBuilder& setImageArrayLayers(uint32_t layers);
    SwapChainBuilder& setImageUsageFlags(VkImageUsageFlags flags);
    SwapChainBuilder& setImageSharingMode(VkSharingMode mode);
    SwapChainBuilder& setQueueFamilyIndices(const std::vector<uint32_t>& indices);
    SwapChainBuilder& setPreTransform(VkSurfaceTransformFlagBitsKHR bits);
    SwapChainBuilder& setCompositeAlpha(VkCompositeAlphaFlagBitsKHR flags);
    SwapChainBuilder& setPresentMode(VkPresentModeKHR presentMode, VkPresentModeKHR defaultMode);
    [[deprecated]]
    SwapChainBuilder& setPresentModeCheck(VkPresentModeKHR presentMode);
    SwapChainBuilder& setClipped(VkBool32 clip);
    SwapChainBuilder& setOldSwapChain(SwapChain old);
private:
    void queryPhysicalDeviceSurfaceCapabilities();
    void queryPhysicalDeviceSurfaceFormats();
    void queryPhysicalDeviceSurfacePresentModes();
    LogicalDevice                    logicalDev;
    VkSwapchainCreateFlagsKHR        createflags;
	Surface                          surface;
    std::optional<uint32_t>          minImageCount;
    std::optional<VkSurfaceFormatKHR>surfaceFormat;
    VkExtent2D                       imageExtent;
    uint32_t                         imageArrayLayers = 0;
    VkImageUsageFlags                imageUsage;
    VkSharingMode                    imageSharingMode;
    std::vector<uint32_t>            queueFamilyIndices;
    VkSurfaceTransformFlagBitsKHR    preTransform;
    VkCompositeAlphaFlagBitsKHR      compositeAlpha;
    std::optional<VkPresentModeKHR>  presentMode;
    VkBool32                         clipped;
    SwapChain                        oldSwapchain;

    SwapChainSupportDetails          details;
};

#endif