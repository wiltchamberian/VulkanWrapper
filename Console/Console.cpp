// Console.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Wrapper.h"

#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw3.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

std::vector<std::string> getExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<std::string> extensions;
    for (int i = 0; i < glfwExtensionCount; ++i) {
        extensions.push_back(std::string(glfwExtensions[i]));
    }
    return extensions;
}

VkExtent2D getExtent(GLFWwindow* window, VkSurfaceCapabilitiesKHR capabilities){
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    VkExtent2D actualExtent = {
        static_cast<uint32_t>(width),
        static_cast<uint32_t>(height)
    };

    actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
    actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

    return actualExtent;
}


class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* window = nullptr;
    VulkanInstance instance;
    PhysicalDevice phyDevice;
    LogicalDevice  device;
    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() { 
        instance = InstanceBuilder().setExtensions(getExtensions()).build();
        Surface surface = SurfaceBuilder(instance).build();

        phyDevice = instance.selectPhysicalDevice(
            QUEUE_GRAPHICS_BIT| QUEUE_PRESENT_BIT, 
            surface,
            { VK_KHR_SWAPCHAIN_EXTENSION_NAME });
        device = phyDevice.createLogicalDevice(QUEUE_GRAPHICS_BIT |
            QUEUE_PRESENT_BIT, {}, { VK_KHR_SWAPCHAIN_EXTENSION_NAME });

        SwapChainBuilder builder(device, surface);
        SwapChainSupportDetails details = builder.querySwapChainSupport();
        builder.setSurfaceFormat({ VK_FORMAT_B8G8R8A8_SRGB ,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR }, details.formats[0]);
        builder.setPresentMode(VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR);
        builder.setExtent2D(details.capabilities.value().currentExtent, getExtent(window, details.capabilities.value()));

        SwapChain chain = builder.build();

        ImageViewBuilder imgViewBuilder(device);
        std::vector<VkImage> imgs = chain.getImages();
        std::vector<ImageView> imgViews(imgs.size());
        int32_t imgSize = imgs.size();
        VkImageSubresourceRange range{};
        range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        range.baseMipLevel = 0;
        range.levelCount = 1;
        range.baseArrayLayer = 0;
        range.layerCount = 1;
        for (size_t i = 0; i <imgSize; i++) {
            imgViews[i] = imgViewBuilder.setImage(imgs[i])
                .setImageViewType(VK_IMAGE_VIEW_TYPE_2D)
                .setFormat(chain.getSurfaceFormat().format)
                .setComponentMapping(VkComponentMapping(VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY))
                .setImageSubresourceRange(range)
                .build();
        }

        //create shaders
        std::string vertexShaderPath = "./shaders/test/shader_vert.spv";
        std::string fragShaderPath = "./shaders/test/shader_frag.spv";
        auto vertexCode = help::readFile(vertexShaderPath);
        auto fragCode = help::readFile(fragShaderPath);
        Shader vertex = ShaderStageBuilder(device).setShaderCode(vertexCode)
            .setFuncName("main")
            .setStageFlags(VK_SHADER_STAGE_VERTEX_BIT)
            .build();
        Shader frag = ShaderStageBuilder(device).setShaderCode(fragCode)
            .setFuncName("main")
            .setStageFlags(VK_SHADER_STAGE_FRAGMENT_BIT)
            .build();

        PipelineBuilder pipelineBuilder;

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)chain.getExtent().width;
        viewport.height = (float)chain.getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = chain.getExtent();

        PipelineLayout layout = PipelineLayoutBuilder(device).build();
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = chain.getSurfaceFormat().format;
        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

        VkAttachmentReference colorAttachmentRef{};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
        VkSubpassDescription subpass{};
        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        subpass.colorAttachmentCount = 1;
        subpass.pColorAttachments = &colorAttachmentRef;

        RenderPass pass = RenderPassBuilder(device).setAttachments({ colorAttachment })
            .setSubpassDescriptions({ subpass })
            .build();
        Pipeline pipeline = pipelineBuilder.setShaders({ vertex, frag })
            .setDynamicStates({ VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR })
            .setPrimitiveTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
            .setPrimitiveRestartEnable(VK_FALSE)
            .setViewports({ viewport })
            .setScissors({scissor})
            //rasterization
            .setDepthClampEnable(VK_FALSE)
            .setRasterizerDiscardEnable(VK_FALSE)
            .setPolygonMode(VK_POLYGON_MODE_FILL)
            .setLineWidth(1.0)
            .setCullMode(VK_CULL_MODE_BACK_BIT)
            .setFrontFace(VK_FRONT_FACE_CLOCKWISE)
            .setDepthBiasEnable(VK_TRUE)
            //multisample
            .setSampleShadingEnable(VK_FALSE)
            .setRasterizationSamples(VK_SAMPLE_COUNT_1_BIT)
            .setMinSampleShading(1.0)
            .setSampleMask(nullptr)
            .setAlphaToCoverageEnable(VK_FALSE)
            .setAlphaToOneEnable(VK_FALSE)
            //ColorBlendState
            .setColorBlendLogicOpEnable(VK_FALSE)
            .setColorBlendLogicOp(VK_LOGIC_OP_COPY)
            .setColorBlendConstants(0,0,0,0)
            //layout
            .setPipelineLayout(layout)
            //renderpass
            .setRenderPass(pass)
            .build();

        //framebuffers
        std::vector<FrameBuffer> swapChainFramebuffers;
        FrameBufferBuilder fbBuilder(device);
        for (size_t i = 0; i < chain.getImages().size(); i++) {
            fbBuilder.setRenderPass(pass)
                .setWidth(chain.getExtent().width)
                .setHeight(chain.getExtent().height)
                .setLayers(1)
                .setAttachments(imgViews);
            swapChainFramebuffers.push_back(fbBuilder.build());
        }
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main2() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::cout << extensionCount << " extensions supported\n";

    glm::mat4 matrix;
    glm::vec4 vec;
    auto test = matrix * vec;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}



