#include "DebugMessenger.h"

void DebugMessenger::cleanUp() {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance.value(), "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance.value(), messenger, nullptr);
    }
}



DebugMessenger DebugMessengerBuilder::build() {
    DebugMessenger dm;
    
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance.value(), "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        VkDebugUtilsMessengerCreateInfoEXT ci;
        ci.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        ci.messageSeverity = messageSeverity;
        ci.messageType = messageType;
        ci.pfnUserCallback = debugCallback;
        VkResult res = func(instance.value(), &ci, nullptr, &dm.value());
        if (res == VK_SUCCESS) {
            dm.instance = instance;
            return dm;
        }
        else {
            dm.value() = VK_NULL_HANDLE;
        }
    }
    return dm;

}

DebugMessengerBuilder& DebugMessengerBuilder::setMessengerCreateFlags(VkDebugUtilsMessengerCreateFlagsEXT flag) {
    flags = flag;
    return *this;
}

DebugMessengerBuilder& DebugMessengerBuilder::setMessageSeverityFlags(VkDebugUtilsMessageSeverityFlagsEXT flg) {
    messageSeverity = flg;
    return *this;
}

DebugMessengerBuilder& DebugMessengerBuilder::setMessageTypeFlags(VkDebugUtilsMessageTypeFlagsEXT flg) {
    messageType = flg;
    return *this;
}

DebugMessengerBuilder& DebugMessengerBuilder::setUserCallback(PFN_vkDebugUtilsMessengerCallbackEXT cb) {
    pfnUserCallback = cb;
    return *this;
}

DebugMessengerBuilder& DebugMessengerBuilder::setUserData(void* data) {
    pUserData = data;
    return *this;
}