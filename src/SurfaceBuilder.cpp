#include "SurfaceBuilder.h"
#include <stdexcept>

SurfaceBuilder::SurfaceBuilder(const VulkanInstance& instance)
:khr{}
,instance(instance)
{
	khr.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
}

Surface SurfaceBuilder::build() {
	Surface surface;
	if (vkCreateWin32SurfaceKHR(instance.value(), &khr, nullptr, &surface.value()) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
	else {
		surface.instance = instance;
	}
	return surface;
}

SurfaceBuilder& SurfaceBuilder::setFlags(VkWin32SurfaceCreateFlagsKHR flags) {
	khr.flags = flags;
	return *this;
}

SurfaceBuilder& SurfaceBuilder::setHINSTANCE(HINSTANCE hInstance) {
	khr.hinstance = hInstance;
	return *this;
}

SurfaceBuilder& SurfaceBuilder::setHWND(HWND hwnd) {
	khr.hwnd = hwnd;
	return *this;
}
