#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cstring>
#include <vector>
#include <iostream>
#include <span>

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
  uint32_t deviceCount = 0;

  // should write another class to interface with certain vulkan systems. these vkresult checks don't need to be handled here
  VkResult statusa = vkEnumeratePhysicalDevices(
    this->instance,
    &deviceCount,
    nullptr
  );

  if (statusa != VK_SUCCESS) {
    std::cout << "Encountered issue while getting device_count. status code: " << statusa << std::endl;

    throw std::runtime_error("Encountered issue while getting device_count.");
  }

  std::cout << "Physical Vulkan device count: " << deviceCount << std::endl;

  std::vector<VkPhysicalDevice> devices(deviceCount);

  VkResult statusb = vkEnumeratePhysicalDevices(
    this->instance,
    &deviceCount,
    devices.data()
  );

  if (statusb != VK_SUCCESS) {
    std::cout << "Encountered issue while getting device_count. status code: " << statusb << std::endl;

    throw std::runtime_error("Encountered issue while getting device_count.");
  }

  if (deviceCount == 0) {
    throw std::runtime_error("No (physical) Vulkan devices found");
  }

  // Should be moved to separate helper function
  for (const VkPhysicalDevice& device : devices) {
    VkPhysicalDeviceProperties properties;
    VkPhysicalDeviceFeatures features;

    vkGetPhysicalDeviceProperties(
      device,
      &properties
    );

    vkGetPhysicalDeviceFeatures(
      device,
      &features
    );

    std::cout << "Device name: " << properties.deviceName << std::endl;

    if (
      properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU ||
      properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
    ) {
      std::cout << "Device is the right type (either a physical or integrated GPU)" << std::endl;

      if (features.geometryShader) {
        std::cout << "Device has a geometry shader" << std::endl;

        this->physicalDevice = device;

        // TODO: Implement settings. might want to use this code for other vulkan implementations other than testing.
        // Don't want to do file anything rn though, fukdat
        break;
      }
    }

    if (this->physicalDevice == VK_NULL_HANDLE) {
      throw std::runtime_error("Couldn't find a usable GPU, integrated or dedicated");
    }
  }
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
