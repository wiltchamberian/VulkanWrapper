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
    char** ext = new char*[extensions.size()];
    for (int i = 0;i < extensions.size();++i) {
        ext[i] = new char[extensions[i].size()+1];
        strcpy(ext[i], extensions[i].c_str());
        ext[i][extensions[i].size()] = '\0';
    }
    createInfo.ppEnabledExtensionNames = ext;

    createInfo.enabledLayerCount = layers.size();
    char** ppLayers = new char* [layers.size()];
    for (int i = 0; i < layers.size(); ++i) {
        ppLayers[i] = (char*)layers[i].c_str();
    }


    VkResult suc = vkCreateInstance(&createInfo, nullptr, &(vk.value()));
    for (int i = 0;i < extensions.size();++i) {
        delete ext[i];
    }
    delete[] ext;
    delete[] ppLayers;
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
