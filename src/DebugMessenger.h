#pragma once
#include "export.h"
#include "vulkan/vulkan.h"
#include "Instance.h"
#include <iostream>

class VULKAN_WRAPPER_API DebugMessenger {
public:
    VkDebugUtilsMessengerEXT& value() {
        return messenger;
    }
    bool isValid() const {
        return messenger != VK_NULL_HANDLE;
    }
private:
    VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
};

class VULKAN_WRAPPER_API DebugMessengerBuilder {
public:
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }
    DebugMessengerBuilder(VulkanInstance inst)
        : instance(inst)
        ,messageSeverity(VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT 
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT 
        | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
        ,messageType(VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT 
        | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT 
        | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT)
        ,pfnUserCallback(debugCallback)
    {


    }
    DebugMessenger build();
    void setDebugUtilsMessengerCreateFlags(VkDebugUtilsMessengerCreateFlagsEXT flag);
    void setDebugUtilsMessageSeverityFlags(VkDebugUtilsMessageSeverityFlagsEXT flg);
    void setUserCallback(PFN_vkDebugUtilsMessengerCallbackEXT cb);
    void setUserData(void* data);
private:
    VkDebugUtilsMessengerCreateFlagsEXT     flags;
    VkDebugUtilsMessageSeverityFlagsEXT     messageSeverity;
    VkDebugUtilsMessageTypeFlagsEXT         messageType;
    PFN_vkDebugUtilsMessengerCallbackEXT    pfnUserCallback;
    void*                                   pUserData = nullptr;

    VulkanInstance                          instance;
};




