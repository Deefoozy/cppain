#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <vector>
#include <iostream>

#include "PhysicalD.h"

uint32_t PhysicalD::getPhysicalDCount(const VkInstance& instance) {
  uint32_t deviceCount = 0;

  // should write another class to interface with certain vulkan systems. these vkresult checks don't need to be handled here
  VkResult status = vkEnumeratePhysicalDevices(
    instance,
    &deviceCount,
    nullptr
  );

  if (status != VK_SUCCESS) {
    std::cout << "Encountered issue while getting device_count. status code: " << status << std::endl;

    throw std::runtime_error("Encountered issue while getting device_count.");
  }

  return deviceCount;
}

uint32_t PhysicalD::getPhysicalDs(const VkInstance& instance, std::vector<VkPhysicalDevice>& physicalDs) {
  uint32_t deviceCount = PhysicalD::getPhysicalDCount(instance);

  std::cout << "Physical Vulkan device count: " << deviceCount << std::endl;

  VkResult status = vkEnumeratePhysicalDevices(
    instance,
    &deviceCount,
    physicalDs.data()
  );

  if (status != VK_SUCCESS) {
    std::cout << "Encountered issue while getting device_count. status code: " << status << std::endl;

    throw std::runtime_error("Encountered issue while getting device_count.");
  }

  return deviceCount;
}

bool PhysicalD::deviceIsViable(const VkPhysicalDevice& physicalD) {
  VkPhysicalDeviceProperties properties;
  VkPhysicalDeviceFeatures features;

  vkGetPhysicalDeviceProperties(
    physicalD,
    &properties
  );

  vkGetPhysicalDeviceFeatures(
    physicalD,
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

      return true;
    }
  }

  return false;
}

void PhysicalD::selectDevice(VkPhysicalDevice& physicalDevice, std::vector<VkPhysicalDevice>& physicalDs) {
  for (const VkPhysicalDevice& device : physicalDs) {
    if (deviceIsViable(device)) {
      physicalDevice = device;
    }
  }
}
