#ifndef __SWAP_CHAIN_BUILDER_H
#define __SWAP_CHAIN_BUILDER_H

#include <optional>
#include "export.h"
#include "Surface.h"
#include "SwapChain.h"
#include "LogicalDevice.h"


class VULKAN_WRAPPER_API SwapChainBuilder {
public:
    SwapChainBuilder();
    SwapChainBuilder(LogicalDevice& dev, Surface& surface);

    SwapChain build();

    SwapChainSupportDetails& querySwapChainSupport();
    SwapChainBuilder& setLogicalDevice(LogicalDevice dev);
	SwapChainBuilder& setSurface(const Surface& surface);
    SwapChainBuilder& setSurfaceFormat(VkSurfaceFormatKHR);
    SwapChainBuilder& setSurfaceFormatCheck(VkSurfaceFormatKHR);
    SwapChainBuilder& setCreateFlags(VkSwapchainCreateFlagsKHR flgs);
    SwapChainBuilder& setMinImageCount(uint32_t imageCount);
    SwapChainBuilder& setDefaultMinImageCount();
    SwapChainBuilder& setExtent2D(VkExtent2D extent);
    SwapChainBuilder& setDefaultExtent2D();
    SwapChainBuilder& setImageArrayLayers(uint32_t layers);
    SwapChainBuilder& setImageUsageFlags(VkImageUsageFlags flags);
    SwapChainBuilder& setSharingMode(VkSharingMode mode);
    SwapChainBuilder& setQueueFamilyIndices(const std::vector<uint32_t>& indices);
    SwapChainBuilder& setSurfaceTransform(VkSurfaceTransformFlagBitsKHR bits);
    SwapChainBuilder& setCompositeAlpha(VkCompositeAlphaFlagBitsKHR flags);
    SwapChainBuilder& setPresentMode(VkPresentModeKHR presentMode);
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
    uint32_t                         imageArrayLayers;
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