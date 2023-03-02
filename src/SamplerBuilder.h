#pragma once
#include "sampler.h"
#include "LogicalDevice.h"

class SamplerBuilder {
public:
	Sampler build();

private:
	void setDevice(LogicalDevice dev);
    void setSamplerCreateFlags(VkSamplerCreateFlags flags);
    void setMagFilter(VkFilter filter);
    void setMinFilter(VkFilter filter);
    void setMipmapMode(VkSamplerMipmapMode mode);
    void setAddressModeU(VkSamplerAddressMode mode);
    void setAddressModeV(VkSamplerAddressMode mode);
    void setAddressModeW(VkSamplerAddressMode mode);
    void setMipLodBias(float bias);
    void setAnisotropyEnable(VkBool32 enable);
    void setMaxAnisotropy(float anisotropy);
    void setCompareEnable(VkBool32 compareEnable);
    void setCompareOp(VkCompareOp op);
    void setMinLod(float lod);
    void setMaxLod(float lod);
    void setBorderColor(VkBorderColor color);
    void setUnNormalizedCoordinates(VkBool32 enable);

	LogicalDevice dev;
	VkSamplerCreateInfo ci = {};
};