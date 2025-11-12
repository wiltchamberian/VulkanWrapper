#include "InstanceBuilder.h"
#include <stdexcept>

VulkanInstance InstanceBuilder::build() {
	VulkanInstance vk;

    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = appName.c_str();
    appInfo.applicationVersion = appVersion;
    appInfo.pEngineName = engineName.c_str();
    appInfo.engineVersion = engineVersion;
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    createInfo.enabledExtensionCount = extensions.size();
    if (createInfo.enabledExtensionCount > 0) {
        char** ext = new char* [createInfo.enabledExtensionCount];
        for (int i = 0; i < extensions.size(); ++i) {
            ext[i] = const_cast<char*>(extensions[i].c_str());
        }
        createInfo.ppEnabledExtensionNames = ext;
    }
    
    if (!checkValidationSupport(layers)) {
        throw std::runtime_error("validationlayersrequested,butnotavailable!");
    }

    createInfo.enabledLayerCount = layers.size();
    if (createInfo.enabledLayerCount > 0) {
        char** ppLayers = new char* [createInfo.enabledLayerCount];
        for (int i = 0; i < layers.size(); ++i) {
            ppLayers[i] = const_cast<char*>(layers[i].c_str());
        }
        createInfo.ppEnabledLayerNames = ppLayers;
    }

    if (debugInfo.sType == VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT) {
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)(&debugInfo);
    }

    VkResult suc = vkCreateInstance(&createInfo, nullptr, &(vk.value()));
    delete[] createInfo.ppEnabledExtensionNames;
    delete[] createInfo.ppEnabledLayerNames;
    if (suc != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    return vk;
}

InstanceBuilder& InstanceBuilder::setAppName(const std::string& str) {
	appName = str;
    return *this;
}

InstanceBuilder& InstanceBuilder::setAppVersion(int major, int minor, int patch) {
	appVersion = VK_MAKE_VERSION(major, minor, patch);
    return *this;
}

InstanceBuilder& InstanceBuilder::setEngineVersion(int major, int minor, int patch) {
    engineVersion = VK_MAKE_VERSION(major, minor, patch);
    return *this;
}

InstanceBuilder& InstanceBuilder::setEngineName(const std::string& str) {
    engineName = str;
    return *this;
}

InstanceBuilder& InstanceBuilder::setExtensions(const std::vector<std::string>& Extensions) {
    extensions = Extensions;
    return *this;
}

InstanceBuilder& InstanceBuilder::setLayers(const std::vector<std::string>& layers) {
    this->layers = layers;
    return *this;
}

InstanceBuilder& InstanceBuilder::setDebugInfo(const VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo) {
    this->debugInfo = debugCreateInfo;
    return *this;
}

bool InstanceBuilder::checkValidationSupport(const std::vector<std::string>& layers) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
  
    std::vector<VkLayerProperties>availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (int i = 0; i < layers.size(); ++i) {
        bool layerFound = false;
        for (int j = 0; j < availableLayers.size(); ++j) {
            if (layers[i] == availableLayers[j].layerName) {
                layerFound = true;
                break;
            }
        }
        if (!layerFound) {
            return false;
        }
    }
    return true;
}