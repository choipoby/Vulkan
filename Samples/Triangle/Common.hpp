#ifndef COMMON_HPP
#define COMMON_HPP
#include <vulkan/vulkan.h>

struct QueueFamilyIndices
{
    // std::optional is a wrapper that contains no value until you assign something to it.
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;
    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails
{
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

#endif