#include "FrameBufferBuilder.h"
#include "FrameBuffer.h"
#include <stdexcept>

FrameBufferBuilder::FrameBufferBuilder(const LogicalDevice& d)
:dev(d)
,width(0)
,height(0)
,layers(0)
{


}
FrameBuffer FrameBufferBuilder::build() {
	FrameBuffer fb;
    size_t siz = attachments.size();
    VkFramebufferCreateInfo framebufferInfo{};
    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    framebufferInfo.renderPass = renderPass.value();
    framebufferInfo.attachmentCount = siz;
    std::vector<VkImageView> views(siz);
    for (int i = 0; i < siz; ++i) {
        views[i] = attachments[i].value();
    }
    framebufferInfo.pAttachments = views.data();
    framebufferInfo.width = width;
    framebufferInfo.height = height;
    framebufferInfo.layers = layers;

    if (vkCreateFramebuffer(dev.value(), &framebufferInfo, nullptr, &fb.value()) != VK_SUCCESS) {
        throw std::runtime_error("failed to create framebuffer!");
    }
    else {
        fb.dev = this->dev;
    }
    return fb;
}

FrameBufferBuilder& FrameBufferBuilder::setRenderPass(const RenderPass& pass) {
    renderPass = pass;
    return *this;
}

FrameBufferBuilder& FrameBufferBuilder::setAttachments(const std::vector<ImageView>& vec) {
    attachments = vec;
    return *this;
}

FrameBufferBuilder& FrameBufferBuilder::setWidth(uint32_t w) {
    width = w;
    return *this;
}

FrameBufferBuilder& FrameBufferBuilder::setHeight(uint32_t h) {
    height = h;
    return *this;
}

FrameBufferBuilder& FrameBufferBuilder::setLayers(uint32_t l) {
    layers = l;
    return *this;
}