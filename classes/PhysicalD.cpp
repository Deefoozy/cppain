#include <vulkan/vulkan_core.h>

#include <vector>
#include <iostream>

#include "PhysicalD.h"

uint32_t PhysicalD::getPhysicalDCount(const VkInstance& instance) {
  uint32_t deviceCount = 0;

  const VkResult status = vkEnumeratePhysicalDevices(
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

uint32_t PhysicalD::getPhysicalDs(const VkInstance& instance, uint32_t deviceCount, std::vector<VkPhysicalDevice>& physicalDs) {
  std::cout << "Physical Vulkan device count: " << deviceCount << std::endl;

  const VkResult status = vkEnumeratePhysicalDevices(
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

      return;
    }
  }

  if (physicalDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("Couldn't find a usable GPU, integrated or dedicated");
  }
}
