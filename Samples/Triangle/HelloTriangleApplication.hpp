#ifndef HELLO_TRIANGLE_APPLICATION_HPP
#define HELLO_TRIANGLE_APPLICATION_HPP

#define GLFW_INCLUDE_VULKAN
// #include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <string.h>
#include <optional>

class HelloTriangleApplication
{
public:
    void run();

private:
    struct QueueFamilyIndices
    {
        // std::optional is a wrapper that contains no value until you assign something to it.
        std::optional<uint32_t> graphicsFamily;
        bool isComplete()
        {
            return graphicsFamily.has_value();
        }
    };

    void initWindow();

    void initVulkan();

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void createLogicalDevice();

    void mainLoop();

    void cleanup();

    void createInstance();

    bool checkValidationLayerSupport();

    // window
    GLFWwindow *window;

    // vulkan instance
    VkInstance instance;

    // The graphics card that we'll end up selecting will be stored here.
    // This object will be implicitly destroyed when the VkInstance is destroyed. No need to add cleanup.
    VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};

    VkDevice device{VK_NULL_HANDLE};

    VkQueue graphicsQueue{VK_NULL_HANDLE};
};

#endif