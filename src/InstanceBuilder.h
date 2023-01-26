#pragma once

#include "export.h"
#include "Instance.h"
#include <string>
#include <vector>

class VULKAN_WRAPPER_API InstanceBuilder {
public:
	VulkanInstance build();
	void setAppName(const std::string& str);
	void setAppVersion(int major, int minor, int patch);
	void setExtensions(const std::vector<std::string>& extensions);
private:
	uint32_t appVersion = VK_MAKE_VERSION(1,0,0);
	std::string appName = "application";
	uint32_t engineVersion = VK_MAKE_VERSION(1,0,0);
	std::string engineName = "engine";
	std::vector<std::string> extensions;

};


