#include "DebugMessenger.h"

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
            return dm;
        }
        else {
            dm.value() = VK_NULL_HANDLE;
        }
    }
    return dm;

}

void DebugMessengerBuilder::setDebugUtilsMessengerCreateFlags(VkDebugUtilsMessengerCreateFlagsEXT flag) {
    flags = flag;
}

void DebugMessengerBuilder::setDebugUtilsMessageSeverityFlags(VkDebugUtilsMessageSeverityFlagsEXT flg) {
    messageSeverity = flg;
}

void DebugMessengerBuilder::setUserCallback(PFN_vkDebugUtilsMessengerCallbackEXT cb) {
    pfnUserCallback = cb;
}

void DebugMessengerBuilder::setUserData(void* data) {
    pUserData = data;
}