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

#include "Common.hpp"

class HelloTriangleApplication
{
public:
    void run();

private:
    void initWindow();

    void initVulkan();

    void pickPhysicalDevice();

    bool isDeviceSuitable(VkPhysicalDevice device);

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

    void createLogicalDevice();

    void mainLoop();

    void cleanup();

    void createInstance();

    bool checkValidationLayerSupport();

    void createSurface();

    std::vector<const char *> getRequiredExtensions();

    void printExtensionInfo();

    // swap chain

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats);

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> &availablePresentModes);

    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

    void createSwapChain();

    void createImageViews();

    /*
     *******************
     * member variables
     *******************
     */

    // Swap chain is a queue of images
    VkSwapchainKHR swapChain;

    // These are images in the swap chain
    std::vector<VkImage> swapChainImages;

    VkFormat swapChainImageFormat;

    VkExtent2D swapChainExtent;

    // To use any VkImage, including those in the swap chain, in the render pipeline
    // we have to create a VkImageView object.
    // VkImageView describes how to access the image and which part of the image to access,
    // for example if it should be treated as a 2D texture depth texture without any mipmapping levels.
    std::vector<VkImageView> swapChainImageViews;

    // window
    GLFWwindow *window;

    // surface
    VkSurfaceKHR surface;

    // vulkan instance
    VkInstance instance;

    // The graphics card that we'll end up selecting will be stored here.
    // This object will be implicitly destroyed when the VkInstance is destroyed. No need to add cleanup.
    VkPhysicalDevice physicalDevice{VK_NULL_HANDLE};

    VkDevice device{VK_NULL_HANDLE};

    VkQueue graphicsQueue{VK_NULL_HANDLE};
    VkQueue presentQueue{VK_NULL_HANDLE};

    static const uint32_t WIDTH{800};
    static const uint32_t HEIGHT{600};
    inline static const std::vector<const char *> validationLayers{"VK_LAYER_LUNARG_standard_validation"};
    inline static const std::vector<const char *> deviceExtensions{VK_KHR_SWAPCHAIN_EXTENSION_NAME};
};

#endif