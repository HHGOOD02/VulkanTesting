//window creation (imports Vulkan SDK as well)
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//when don't you?
#include <iostream>

//for exception handling
#include <stdexcept>
#include <cstdlib>

#include <vector>
#include <map>

class HelloTriangleApplication {

  const uint32_t WIDTH = 800;
  const uint32_t HEIGHT = 600;

public:
  void run() {
    
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();

  }

private:
  GLFWwindow* window;

  void initWindow() {

    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);

  }

void initVulkan() {
    
    createInstance();

    pickPhysicalDevice();

  }

void pickPhysicalDevice() {

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

    if (deviceCount == 0) {
      throw std::runtime_error("No Vulkan-compatible GPUs detected");
    }

    std::vector<VkPhysicalDevice> devices(deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

    for (const auto& device : devices) {
      if (isDeviceSuitable(device)){
        physicalDevice = device;
        break;
      }
    }

    if (physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("Failed to find Vulkan-compatible GPU");
    }

  }

bool isDeviceSuitable(VkPhysicalDevice device) {
    
    VkPhysicalDeviceProperties deviceProperties;
    VkPhysicalDeviceFeatures deviceFeatures;
    vkGetPhysicalDeviceProperties(device, &deviceProperties);
    vkGetPhysicalDeviceFeatures(device, &deviceFeatures);

    return deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && deviceFeatures.geometryShader;

    }

void pickPhysicalDevice() {

    std::multimap<int, VkPhysicalDevice> candidates;

    for (const auto& device : devices) {
      int score = rateDeviceSuitability(device);
      candidates.insert(std::make_pair(score, device));
    
    }

    if (candidates.rbegin()->first > 0) {
      physicalDevice = candidates.rbegin()->second;
    } else {
      throw std::runtime_error("failed to find Vulkan-compatible GPU");
    }

  }

  int rateDeviceSuitability(VkPhysicalDevice device) {

    int score = 0;

    if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_dISCRETE_GPU) {
      score += 1000;
    }

    score += deviceProperties.limits.maxImageDimension2D;

    if (!deviceFeatures.geometryShader) {
      return 0;
    }

    return score;

  }


private:
  VkInstance instance;

void createInstance() { 
    
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Test Triangle";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    createInfo.enabledLayerCount = 0;

    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

    if(vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
      throw std::runtime_error("failed to create instance");
    }
  }

  void mainLoop() {
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents();
    }
  }

  void cleanup() {

    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);

    glfwTerminate();
   
  }

};

int main() {
  HelloTriangleApplication app;

//quick try catch
  try{
    app.run();
  } catch (const std::exception& e) {
    std::cerr <<e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
