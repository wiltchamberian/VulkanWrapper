// Console.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Wrapper.h"
#include "vulkan/vulkan.h"
#include "Vertex.h"

#define GLFW_INCLUDE_VULKAN
#include "glfw/glfw3.h"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "glfw/glfw3native.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <algorithm>

#include <Windows.h>

const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 1.0f, 1.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

std::string GetExecutablePath() {
    WCHAR buffer[MAX_PATH];
    GetModuleFileName(nullptr, buffer, MAX_PATH);
    
    int length = WideCharToMultiByte(CP_UTF8, 0, buffer, -1, nullptr, 0, nullptr, nullptr);
    if (length == 0) {
        // Error handling
        return "";
    }

    char* buf = new char[length];
    WideCharToMultiByte(CP_UTF8, 0, buffer, -1, buf, length, nullptr, nullptr);

    std::string result(buf);
    delete[] buf;

    size_t siz = result.size();
    for (int i = 0; i < siz; ++i) {
        if (result[siz - i - 1] == '\\') {
            result.resize(siz - i);
            break;
        }
    }

    return result;
}

bool physicalDeviceFilter(VkPhysicalDeviceProperties& properties, VkPhysicalDeviceFeatures& features) {
    return properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU 
        && features.drawIndirectFirstInstance
        && features.logicOp
        && features.shaderUniformBufferArrayDynamicIndexing
        && features.shaderSampledImageArrayDynamicIndexing
        && features.shaderStorageBufferArrayDynamicIndexing
        && features.shaderStorageImageArrayDynamicIndexing
        ;
}

std::vector<std::string> getLayers() {
    std::vector<std::string> r;
    r.push_back("VK_LAYER_KHRONOS_validation");
    return r;
}

std::vector<std::string> getExtensions() {
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<std::string> extensions;
    for (int i = 0; i < glfwExtensionCount; ++i) {
        extensions.push_back(std::string(glfwExtensions[i]));
    }
    if (true) {
        //without this ,debugMessenger cant be created sucessfully
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        //extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);//old version
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

VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
    return VK_FALSE;
}



class HelloTriangleApplication {
public:
    HelloTriangleApplication() {

    }
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    
    bool framebufferResized = false;
private:
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
    GLFWwindow* window = nullptr;
    HINSTANCE hInstance;
    HWND hwnd;

    VulkanInstance instance;
    DebugMessenger dbMessenger;
    PhysicalDevice phyDevice;
    LogicalDevice  device;
    Surface surface;
    SwapChain swapChain;
    std::vector<FrameBuffer> swapChainFramebuffers;
    std::vector<ImageView> swapChainImageViews;
    RenderPass renderPass;
    Pipeline pipeline;
    PipelineLayout layout;

    CommandPool pool;
    std::vector<CommandBuffer> cmdBuffers;

    Buffer vertexBuffer;
    DeviceMemory vertexBufferMemory;

    SwapChainBuilder swapChainBuilder;
    ImageViewBuilder imgViewBuilder;

    //drawFrame
    const int MAX_FRAMES_IN_FLIGHT = 2;
    std::vector<Semaphore> imageAvailableSemaphores;
    std::vector<Semaphore> renderFinishedSemaphores;
    std::vector<Fence> inFlightFences;
    

    uint32_t currentFrame = 0;

    void initWindow() {
        assert(glfwInit() == GLFW_TRUE);

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
        glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
            if (app != nullptr) {
                app->framebufferResized = true;
            }
            
            }
        );
    }

    void CreateSwapChain() {
        swapChainBuilder.setLogicalDevice(device);
        swapChainBuilder.setSurface(surface);
        SwapChainSupportDetails details = swapChainBuilder.querySwapChainSupport();
        swapChainBuilder.setSurfaceFormat({ VK_FORMAT_B8G8R8A8_SRGB ,VK_COLOR_SPACE_SRGB_NONLINEAR_KHR }, details.formats[0]);
        swapChainBuilder.setPresentMode(VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_FIFO_KHR);
        swapChainBuilder.setImageExtent(details.capabilities.value().currentExtent, getExtent(window, details.capabilities.value()));
        swapChainBuilder.setMinImageCount(std::min<uint32_t>(details.capabilities.value().minImageCount + 1, details.capabilities.value().maxImageCount));
        swapChainBuilder.setImageArrayLayers(1);
        swapChainBuilder.setImageUsageFlags(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
        swapChainBuilder.setPreTransform(details.capabilities.value().currentTransform);
        swapChainBuilder.setCompositeAlpha(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR);
        swapChainBuilder.setClipped(VK_TRUE);
        swapChainBuilder.setOldSwapChain(SwapChain());
        //if you use VK_SHARING_MODE_CONCURRENT only the present and graphics queue are different
        swapChainBuilder.setImageSharingMode(VK_SHARING_MODE_EXCLUSIVE);

        QueueFamilyIndices indices = phyDevice.findQueueFamilies(QUEUE_GRAPHICS_BIT | QUEUE_PRESENT_BIT, surface);
        std::vector<uint32_t> queueFamilyIndicesVec = indices.exportIndices();
        swapChainBuilder.setQueueFamilyIndices(queueFamilyIndicesVec);

        swapChain = swapChainBuilder.build();
    }

    void CreateImageView() {
        imgViewBuilder.setDevice(device);
        std::vector<VkImage> imgs = swapChain.getImages();
        swapChainImageViews.resize(imgs.size());
        int32_t imgSize = imgs.size();
        VkImageSubresourceRange range{};
        range.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        range.baseMipLevel = 0;
        range.levelCount = 1;
        range.baseArrayLayer = 0;
        range.layerCount = 1;
        for (size_t i = 0; i < imgSize; i++) {
            swapChainImageViews[i] = imgViewBuilder.setImage(imgs[i])
                .setImageViewType(VK_IMAGE_VIEW_TYPE_2D)
                .setFormat(swapChain.getSurfaceFormat().format)
                .setComponentMapping(VkComponentMapping(VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY,
                    VK_COMPONENT_SWIZZLE_IDENTITY))
                .setImageSubresourceRange(range)
                .build();
        }
    }

    void CreateFrameBuffers() {
        //create framebuffers
        FrameBufferBuilder fbBuilder(device);
        for (size_t i = 0; i < swapChain.getImages().size(); i++) {
            fbBuilder.setRenderPass(renderPass)
                .setWidth(swapChain.getExtent().width)
                .setHeight(swapChain.getExtent().height)
                .setLayers(1)
                .setAttachments({ swapChainImageViews[i] });
            swapChainFramebuffers.push_back(fbBuilder.build());
        }
    }

    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags flags) {
        VkPhysicalDeviceMemoryProperties memProperties = phyDevice.queryPhysicalDeviceMemoryProperties();
        for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
            if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & flags) == flags) {
                return i;
            }
        }

        throw std::runtime_error("failed to find suitable memory type!");
    }

    void CreateVertexBuffer() {
        BufferBuilder bufferBuilder(device);
        bufferBuilder.SetSize(sizeof(vertices[0]) * vertices.size())
            .SetUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
            .SetSharingMode(VK_SHARING_MODE_EXCLUSIVE);
        vertexBuffer = bufferBuilder.build();

        VkMemoryRequirements memRequirements = vertexBuffer.getMemoryRequirements();
        
        MemoryAllocator allocator(device);
        allocator.SetAllocationSize(memRequirements.size)
            .SetMemoryTypeIndex(findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT));
    
        vertexBufferMemory = allocator.allocateMemory();
        vertexBuffer.bindMemory(vertexBufferMemory, 0);
        
        vertexBufferMemory.copyMemory(vertices.data(), 0, sizeof(vertices[0]) * vertices.size(), 0);
    }

    void recreateSwapChain() {
        int width = 0, height = 0;
        glfwGetFramebufferSize(window, &width, &height);
        while (width == 0 || height == 0) {
            glfwGetFramebufferSize(window, &width, &height);
            glfwWaitEvents();
        }
        device.waitIdle();
        cleanUpSwapChain();
        CreateSwapChain();
        CreateImageView();
        CreateFrameBuffers();
    }

    void cleanUpSwapChain() {
        for (auto framebuffer : swapChainFramebuffers) {
            framebuffer.cleanUp();
        }
        for (auto imageView : swapChainImageViews) {
            imageView.cleanUp();
        }

        swapChain.cleanUp();
    }

    void initVulkan() { 
        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
        debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        debugCreateInfo.pfnUserCallback = debugCallback;
        debugCreateInfo.pUserData = nullptr;
        instance = InstanceBuilder().setExtensions(getExtensions()).setLayers(getLayers()).
            setDebugInfo(debugCreateInfo).build();

        //debug related, this is independent from the debugCreateInfo in VulkanInstance build
        DebugMessengerBuilder dbBuilder(instance);
        dbMessenger = dbBuilder.build();
#if 0
        VkDebugReportCallbackCreateInfoEXT debug_create{};
        debug_create.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_create.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
        debug_create.pfnCallback = nullptr;
        VkResult debugReport = vkCreateDebugReportCallbackEXT(instance.value(), &debug_create, nullptr, nullptr);
#endif 

        //windows
        hInstance = GetModuleHandle(nullptr);
        hwnd = glfwGetWin32Window(window);
        surface = SurfaceBuilder(instance,hInstance, hwnd).build();

        phyDevice = instance.selectPhysicalDevice(
            QUEUE_GRAPHICS_BIT| QUEUE_PRESENT_BIT, 
            surface,
            { VK_KHR_SWAPCHAIN_EXTENSION_NAME }, physicalDeviceFilter);
        device = phyDevice.createLogicalDevice(QUEUE_GRAPHICS_BIT |
            QUEUE_PRESENT_BIT, {}, { VK_KHR_SWAPCHAIN_EXTENSION_NAME });

        CreateSwapChain();
        CreateImageView();
        

        //create shaders
        std::string exePath = GetExecutablePath();
        std::string vertexShaderPath = exePath + "../rc/shaders/test/shader_vert.spv";
        std::string fragShaderPath = exePath + "../rc/shaders/test/shader_frag.spv";
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

        //build render pass
        VkAttachmentDescription colorAttachment{};
        colorAttachment.format = swapChain.getSurfaceFormat().format;
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

        VkSubpassDependency dependency{};
        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        dependency.dstSubpass = 0;
        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.srcAccessMask = 0;
        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
        renderPass = RenderPassBuilder(device).setAttachments({ colorAttachment })
            .setSubpassDescriptions({ subpass })
            .setSubpassDependencies({ dependency })
            .build();

        //build pipline
        PipelineBuilder pipelineBuilder(device);

        VkViewport viewport{};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)swapChain.getExtent().width;
        viewport.height = (float)swapChain.getExtent().height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = swapChain.getExtent();

        layout = PipelineLayoutBuilder(device).build();

        VkPipelineColorBlendAttachmentState colorBlendAttachment{};
        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        colorBlendAttachment.blendEnable = VK_FALSE;

        pipeline = pipelineBuilder.setShaders({ vertex, frag })
            .setDynamicStates({ VK_DYNAMIC_STATE_VIEWPORT,VK_DYNAMIC_STATE_SCISSOR })
            //VkPipelineInputAssemblyStateCreateInfo
            .setPrimitiveTopology(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST)
            .setPrimitiveRestartEnable(VK_FALSE)
            .setAssemblyStateCreateFlags(0)
            //viewportStateCreateInfo
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
            .setColorBlendAttachments({ colorBlendAttachment })
            .setColorBlendLogicOpEnable(VK_FALSE)
            .setColorBlendLogicOp(VK_LOGIC_OP_COPY)
            .setColorBlendConstants(0,0,0,0)
            //layout
            .setPipelineLayout(layout)
            //renderpass
            .setRenderPass(renderPass)
            //vertex
            .setVertexInputBindingDescriptions(Vertex::getBindingDescriptions() )
            .setVertexInputAttributeDescriptions(Vertex::getAttributeDescriptions())
            .build();

        //create framebuffers
        CreateFrameBuffers();

        //create command buffers
        QueueFamilyIndices queueFamilyIndices = phyDevice.findQueueFamilies(QUEUE_GRAPHICS_BIT | QUEUE_PRESENT_BIT, surface);
        CommandPoolBuilder poolBuilder(device);
        poolBuilder.setCommandPoolCreateFlags(VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
        poolBuilder.setQueueFamilyIndex(queueFamilyIndices.getIndex(QUEUE_GRAPHICS_BIT));
        pool = poolBuilder.build();

        cmdBuffers.resize(MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            cmdBuffers[i] = pool.allocBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
        }

        CreateVertexBuffer();

        //createSemaphores
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        SemaphoreBuilder semaphoreBuilder(device);
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            imageAvailableSemaphores[i] = semaphoreBuilder.build();
            renderFinishedSemaphores[i] = semaphoreBuilder.build();
            inFlightFences[i] = FenceBuilder(device)
                .setFenceCreateFlags(VK_FENCE_CREATE_SIGNALED_BIT)
                .build();
        }
        

    }

    void recordCommandBuffer(uint32_t imageIndex) {
        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = 0 /*VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT*/; // Optional
        beginInfo.pInheritanceInfo = nullptr; // Optional
        cmdBuffers[currentFrame].begin(beginInfo);
       
        VkRenderPassBeginInfo renderPassInfo{};
        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        renderPassInfo.renderPass = renderPass.value();
        renderPassInfo.framebuffer = swapChainFramebuffers[imageIndex].value();
        renderPassInfo.renderArea.offset = { 0, 0 };
        renderPassInfo.renderArea.extent = swapChain.getExtent();
        VkClearValue clearColor = { {{0.0f, 0.0f, 0.0f, 1.0f}} };
        renderPassInfo.clearValueCount = 1;
        renderPassInfo.pClearValues = &clearColor;

        cmdBuffers[currentFrame].beginRenderPass(renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        cmdBuffers[currentFrame].bindPipeline(pipeline, VK_PIPELINE_BIND_POINT_GRAPHICS);
        
        //bind vertex buffer
        cmdBuffers[currentFrame].bindVertexBuffer(vertexBuffer, 0);

        VkExtent2D ext = swapChain.getExtent();
        VkViewport viewport{.x = 0.0f, .y = 0.0f ,.width = static_cast<float>(ext.width),
        .height = static_cast<float>(ext.height), .minDepth = 0.0f, .maxDepth = 1.0f};
        cmdBuffers[currentFrame].setViewPort(viewport);
       
        VkRect2D scissor{};
        scissor.offset = { 0, 0 };
        scissor.extent = ext;
        cmdBuffers[currentFrame].setScissor(scissor);

        cmdBuffers[currentFrame].draw(3, 1, 0, 0); //similar as glDrawBuffers

        cmdBuffers[currentFrame].endRenderPass();
        cmdBuffers[currentFrame].end();
    }

    void drawFrame() {
        inFlightFences[currentFrame].wait(UINT64_MAX);
        
        Fence fence;
        uint32_t imageIndex;
        
        VkResult result =  swapChain.acquireNextImageKHR(UINT64_MAX, imageAvailableSemaphores[currentFrame], fence, imageIndex);
        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            recreateSwapChain();
            return;
        }
        else if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR){
            throw std::runtime_error("failed to acquire swap chain!");
        }
        //only reset the fence if we are submitting work
        inFlightFences[currentFrame].reset();

        cmdBuffers[currentFrame].reset();
        recordCommandBuffer(imageIndex);

        DeviceQueue queue = device.getDeviceQueue(QUEUE_GRAPHICS_BIT, 0);
        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame].value()};
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &cmdBuffers[currentFrame].value();

        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame].value()};
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;
        queue.submit(submitInfo, inFlightFences[currentFrame]);

        VkPresentInfoKHR presentInfo{};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;
        VkSwapchainKHR swapChains[] = { swapChain.value()};
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;
        presentInfo.pImageIndices = &imageIndex;
        presentInfo.pResults = nullptr; // Optional

        DeviceQueue presentQueue = device.getDeviceQueue(QUEUE_PRESENT_BIT);
        result = presentQueue.presentKHR(presentInfo);
        if (result == VK_ERROR_OUT_OF_DATE_KHR 
            || result == VK_SUBOPTIMAL_KHR
            || framebufferResized) {
            framebufferResized = false;
            recreateSwapChain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
            drawFrame();
        }
    }

    void cleanup() {

        //clearUpSwapChain();
        vertexBuffer.cleanUp();
        vertexBufferMemory.free();
        //pipeline.cleanUp();
        layout.cleanUp();
        for (int i = 0; i < MAX_FRAMES_IN_FLIGHT; ++i) {
            imageAvailableSemaphores[i].cleanUp();
            renderFinishedSemaphores[i].cleanUp();
            inFlightFences[i].cleanUp();
        }
        
        pool.cleanUp();

        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<HelloTriangleApplication*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

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



