#ifndef __SWAP_CHAIN_BUILDER_H
#define __SWAP_CHAIN_BUILDER_H

#include "Surface.h"
#include "SwapChain.h"
#include "LogicalDevice.h"

class VULKAN_WRAPPER_API SwapChainBuilder {
public:
    SwapChain build();
    SwapChainBuilder& setLogicalDevice(LogicalDevice dev);
	SwapChainBuilder& setSurface(const Surface& surface);
	SwapChainBuilder& setFormat(VkFormat format);
    SwapChainBuilder& setCreateFlags(VkSwapchainCreateFlagsKHR flgs);
    SwapChainBuilder& setMinImageCount(uint32_t imageCount);
    SwapChainBuilder& setColorSpace(VkColorSpaceKHR space);
    SwapChainBuilder& setExtent2D(VkExtent2D extent);
    SwapChainBuilder& setImageArrayLayers(uint32_t layers);
    SwapChainBuilder& setImageUsageFlags(VkImageUsageFlags flags);
    SwapChainBuilder& setSharingMode(VkSharingMode mode);
    SwapChainBuilder& setQueueFamilyIndices(const std::vector<uint32_t>& indices);
    SwapChainBuilder& setSurfaceTransform(VkSurfaceTransformFlagBitsKHR bits);
    SwapChainBuilder& setCompositeAlpha(VkCompositeAlphaFlagBitsKHR flags);
    SwapChainBuilder& setPresentMode(VkPresentModeKHR presentMode);
    SwapChainBuilder& setClipped(VkBool32 clip);
    SwapChainBuilder& setOldSwapChain(SwapChain old);
private:
    LogicalDevice                    logicalDev;
    VkSwapchainCreateFlagsKHR        createflags;
	Surface                          surface;
    uint32_t                         minImageCount;
    VkFormat                         imageFormat;
    VkColorSpaceKHR                  imageColorSpace;
    VkExtent2D                       imageExtent;
    uint32_t                         imageArrayLayers;
    VkImageUsageFlags                imageUsage;
    VkSharingMode                    imageSharingMode;
    std::vector<uint32_t>            queueFamilyIndices;
    VkSurfaceTransformFlagBitsKHR    preTransform;
    VkCompositeAlphaFlagBitsKHR      compositeAlpha;
    VkPresentModeKHR                 presentMode;
    VkBool32                         clipped;
    SwapChain                        oldSwapchain;
};

#endif