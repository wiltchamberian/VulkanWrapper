#pragma once
#include "sampler.h"
#include "LogicalDevice.h"

class SamplerBuilder {
public:
	Sampler build();

private:
    SamplerBuilder& setDevice(LogicalDevice dev);
    SamplerBuilder& setSamplerCreateFlags(VkSamplerCreateFlags flags);
    SamplerBuilder& setMagFilter(VkFilter filter);
    SamplerBuilder& setMinFilter(VkFilter filter);
    SamplerBuilder& setMipmapMode(VkSamplerMipmapMode mode);
    SamplerBuilder& setAddressModeU(VkSamplerAddressMode mode);
    SamplerBuilder& setAddressModeV(VkSamplerAddressMode mode);
    SamplerBuilder& setAddressModeW(VkSamplerAddressMode mode);
    SamplerBuilder& setMipLodBias(float bias);
    SamplerBuilder& setAnisotropyEnable(VkBool32 enable);
    SamplerBuilder& setMaxAnisotropy(float anisotropy);
    SamplerBuilder& setCompareEnable(VkBool32 compareEnable);
    SamplerBuilder& setCompareOp(VkCompareOp op);
    SamplerBuilder& setMinLod(float lod);
    SamplerBuilder& setMaxLod(float lod);
    SamplerBuilder& setBorderColor(VkBorderColor color);
    SamplerBuilder& setUnNormalizedCoordinates(VkBool32 enable);

	LogicalDevice dev;
	VkSamplerCreateInfo ci = {};
};