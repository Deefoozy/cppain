#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <vector>
#include <iostream>

#include "PhysicalD.h"
#include "VisApp.h"

void VisApp::run() {
  createWindow();

  initVulkan();

  assignPhysicalDevice();

  mainLoop();

  cleanup();
}

void VisApp::createWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API); // Do not open with OpenGL
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  this->windows = glfwCreateWindow(
    800,
    600,
    "Vulkan window",
    nullptr,
    nullptr // OpenGL specific
  );
}

void VisApp::assignPhysicalDevice() {
  const uint32_t deviceCount = PhysicalD::getPhysicalDCount(this->instance);

  if (deviceCount == 0) {
    throw std::runtime_error("No (physical) Vulkan devices found");
  }

  std::vector<VkPhysicalDevice> devices(deviceCount);

  PhysicalD::getPhysicalDs(this->instance, devices);

  PhysicalD::selectDevice(this->physicalDevice, devices);
}

void VisApp::initVulkan() {
  VkApplicationInfo appInfo{};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "CpPain";

  // Can I get version info from cmake perhaps? updating this manually seems like a fkn chore
  appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 69);

  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);

  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo{};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  uint32_t glfwExtensionCount = 0;

  // Seems like a pointer to a pointer.
  const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;

  createInfo.enabledLayerCount = 0;

  const VkResult result = vkCreateInstance(&createInfo, nullptr, &this->instance);

  if (result != VK_SUCCESS) {
    std::cout << "cry." << std::endl;

    throw std::runtime_error("Couldn't create instance. git good idiot.");
  }
}

void VisApp::mainLoop() const {
  std::cout << "Hello, World!" << std::endl;

  while (!glfwWindowShouldClose(this->windows)) {
    glfwPollEvents();
  }
}

void VisApp::cleanup() const {
  vkDestroyInstance(instance, nullptr);

  glfwDestroyWindow(this->windows);
  glfwTerminate();
}
