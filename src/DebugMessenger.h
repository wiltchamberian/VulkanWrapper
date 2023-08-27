#ifndef __DEBUG_MESSENGER_H
#define __DEBUG_MESSENGER_H
#include "export.h"
#include "vulkan/vulkan.h"
#include "Instance.h"
#include <iostream>

class VULKAN_WRAPPER_API DebugMessenger {
public:
    friend class DebugMessengerBuilder;
    VkDebugUtilsMessengerEXT& value() {
        return messenger;
    }
    bool isValid() const {
        return messenger != VK_NULL_HANDLE;
    }
    void cleanUp();
private:
    VkDebugUtilsMessengerEXT messenger = VK_NULL_HANDLE;
    VulkanInstance  instance;
};



#endif




