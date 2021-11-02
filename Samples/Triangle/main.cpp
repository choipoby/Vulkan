#define GLFW_INCLUDE_VULKAN
// #include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <string.h>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

// validation
const std::vector<const char*> validationLayers = {
    "VK_LAYER_LUNARG_standard_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    void initWindow() {
        // initializes the GLFW library.
        glfwInit();

        // Because GLFW was originally designed to create an OpenGL context,
        // we need to tell it to not create an OpenGL context with a subsequent call
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        // Because handling resized windows takes special care that we'll look into later,
        // disable it for now with another window hint call
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // creating the actual window. initialize the window
        window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
    }

    void initVulkan() {
        // initialize the Vulkan library by creating an instance
        // The instance is the connection between your application and the Vulkan library
        // and creating it involves specifying some details about your application to the driver.
        createInstance();
    }

    void mainLoop() {
        // To keep the application running until either an error occurs or the window is closed,
        // we need to add an event loop to the mainLoop function as follows:
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        // The VkInstance should be only destroyed right before the program exits
        vkDestroyInstance(instance, nullptr);

        // Once the window is closed,
        // we need to clean up resources by destroying it and terminating GLFW itself.
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void createInstance() {

        // check validation layer support
        if (enableValidationLayers && !checkValidationLayerSupport()) {
            throw std::runtime_error("validation layers requested, but not available!");
        }

        // A lot of information in Vulkan is passed through structs instead of function parameters
        // and we'll have to fill in one more struct to provide sufficient information for creating an instance

        // fill in a struct with some information about our application
        // This data is technically optional, but it may provide
        // some useful information to the driver in order to optimize our specific application
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // This next struct is not optional and
        // tells the Vulkan driver which global extensions and validation layers we want to use.
        // Global here means that they apply to the entire program and not a specific device
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        if (enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
            createInfo.ppEnabledLayerNames = validationLayers.data();
        } else {
            createInfo.enabledLayerCount = 0;
        }

        // Extensions: specify the desired global extensions
        // Vulkan is a platform agnostic API,
        // which means that you need an extension to interface with the window system.
        // GLFW has a handy built-in function that returns the extension(s)
        // it needs to do that which we can pass to the struct
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // Layers
        createInfo.enabledLayerCount = 0;

        // now, create a Vulkan instance with above configurations
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }

        // extensions
        uint32_t extensionCount = 0;
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
        std::vector<VkExtensionProperties> extensions(extensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
        std::cout << "available extensions:\n";
        for (const auto& extension : extensions) {
            std::cout << '\t' << extension.extensionName << '\n';
        }
    }

    bool checkValidationLayerSupport() {
        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
        std::cout << "Layer:" << std::endl;
        for (const auto& layerProperties : availableLayers) {
            std::cout << "\t" << layerProperties.layerName << std::endl;
        }

        for (const char* layerName : validationLayers) {
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                return false;
            }
        }

        return true;
    }


    // window
    GLFWwindow* window;


    // vulkan instance
    VkInstance instance;


};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
