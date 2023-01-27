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
    createInfo.enabledLayerCount = 0;

    VkResult suc = vkCreateInstance(&createInfo, nullptr, &vk.vk);
    for (int i = 0;i < extensions.size();++i) {
        delete[] ext[i];
    }
    delete[] ext;
    if (suc != VK_SUCCESS) {
        throw std::runtime_error("failed to create instance!");
    }

    return vk;
}

void InstanceBuilder::setAppName(const std::string& str) {
	appName = str;
}

void InstanceBuilder::setAppVersion(int major, int minor, int patch) {
	appVersion = VK_MAKE_VERSION(major, minor, patch);
}

void InstanceBuilder::setExtensions(const std::vector<std::string>& Extensions) {
    extensions = Extensions;
}
