#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cstdlib>
#include <iostream>

class VisApp {
public:
  void run() {
    // TODO: make myself very happy by also doing this shit multi threaded
    createWindow();

    mainLoop();

    cleanup();
  }

private:
  bool hasWindow_val = false;
  bool *hasWindow = &hasWindow_val;

  bool glfwIsReady_val = false;
  bool *glfwIsReady = &glfwIsReady_val;

  // hehe
  GLFWwindow *windows;

  void createWindow() {
    if (*this->hasWindow) {
      glfwDestroyWindow(this->windows);

      *this->hasWindow = false;
    }

    if (!*this->glfwIsReady) {
      glfwInit();

      *this->glfwIsReady = true;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    this->windows =
        glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

    *this->hasWindow = true;
  }

  void mainLoop() {
    std::cout << "Hello, World!" << std::endl;

    while (!glfwWindowShouldClose(this->windows)) {
      glfwPollEvents();
    }
  }

  void cleanup() {
    glfwDestroyWindow(this->windows);
    glfwTerminate();
  }
};

int main() {
  VisApp mainApplication;

  try {
    mainApplication.run();
    // wtf does that & do
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
