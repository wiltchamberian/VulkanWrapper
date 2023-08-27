#include "DebugMessenger.h"

void DebugMessenger::cleanUp() {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance.value(), "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance.value(), messenger, nullptr);
    }
}