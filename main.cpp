//window creation (imports Vulkan SDK as well)
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

//when don't you?
#include <iostream>

//for exception handling
#include <stdexcept>
#include <cstdlib>

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
  GLFwindow* window;

  void initWindow() {
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Test Window", nullptr, nullptr);
  }

  void initVulkan() {

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

//quick try catch
  try{
    app.run();
  } catch (const std::exception& e) {
    std::cerr <<e.what() << stad::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
