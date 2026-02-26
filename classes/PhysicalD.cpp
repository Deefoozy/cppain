#include <vulkan/vulkan_core.h>

#include <set>
#include <vector>
#include <iostream>

#include "PhysicalD.h"

const std::vector<const char*> PhysicalD::requiredDeviceExtensions = {
  VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

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

void PhysicalD::getPhysicalDs(const VkInstance& instance, uint32_t deviceCount, std::vector<VkPhysicalDevice>& physicalDs) {
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

  std::cout << "Device name: " << properties.deviceName << " || ";

  if (
    properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
    properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU
  ) {
    std::cout << "Device is not of the right type. (must be either a physical or integrated GPU)" << std::endl;

    return false;
  }

  if (!features.geometryShader) {
    std::cout << "Device does not have a geometry shader" << std::endl;

    return false;
  }

  if (!checkExtensionSupport(physicalD)) {
    std::cout << "Device does not suppoort all required extensions" << std::endl;

    return false;
  }

  std::cout << "Device viable." << std::endl;
  return true;
}

bool PhysicalD::checkExtensionSupport(const VkPhysicalDevice& physicalD) {
  const uint32_t extensionCount = PhysicalD::getExtensionCount(physicalD);

  std::vector<VkExtensionProperties> availableExtensions(extensionCount);

  getExtensions(physicalD, extensionCount, availableExtensions);

  std::set<std::string> tempRequiredExtensions(requiredDeviceExtensions.begin(), requiredDeviceExtensions.end());

  for (const VkExtensionProperties& extension : availableExtensions) {
    tempRequiredExtensions.erase(extension.extensionName);
  }

  return tempRequiredExtensions.empty();
}

uint32_t PhysicalD::getExtensionCount(const VkPhysicalDevice& physicalD) {
  uint32_t extensionCount = 0;

  vkEnumerateDeviceExtensionProperties(physicalD, nullptr, &extensionCount, nullptr);

  return extensionCount;
}

void PhysicalD::getExtensions(const VkPhysicalDevice& physicalD, uint32_t extensionCount, std::vector<VkExtensionProperties>& availableExtensions) {
  vkEnumerateDeviceExtensionProperties(
    physicalD,
    nullptr,
    &extensionCount,
    availableExtensions.data()
  );
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
