#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <iostream>

#include "VisApp.h"

void VisApp::run() {
  createWindow();

  mainLoop();

  cleanup();
}

void VisApp::createWindow() {
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

void VisApp::mainLoop() const {
  std::cout << "Hello, World!" << std::endl;

  while (!glfwWindowShouldClose(this->windows)) {
    glfwPollEvents();
  }
}

void VisApp::cleanup() const {
  glfwDestroyWindow(this->windows);
  glfwTerminate();
}
