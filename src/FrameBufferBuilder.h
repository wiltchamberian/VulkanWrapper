#ifndef __FRAME_BUFFER_BUILDER_H
#define __FRAME_BUFFER_BUILDER_H

#include "export.h"
#include "RenderPass.h"
#include "ImageView.h"
#include "LogicalDevice.h"

class FrameBuffer;

class VULKAN_WRAPPER_API FrameBufferBuilder {
public:
    FrameBufferBuilder(const LogicalDevice& dev);
    FrameBuffer build();
    FrameBufferBuilder& setRenderPass(const RenderPass& pass);
    FrameBufferBuilder& setAttachments(const std::vector<ImageView>& attachments);
    FrameBufferBuilder& setWidth(uint32_t width);
    FrameBufferBuilder& setHeight(uint32_t height);
    FrameBufferBuilder& setLayers(uint32_t layers);
private:
    LogicalDevice dev;
    RenderPass renderPass;
    std::vector<ImageView> attachments;
    uint32_t width;
    uint32_t height;
    uint32_t layers;
};

#endif