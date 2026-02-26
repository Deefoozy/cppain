#include <vulkan/vulkan_core.h>

#include <optional>
#include <vector>
#include <iostream>
#include <ostream>

#include "Queue.h"

void Queue::getQueueFamilies(const VkPhysicalDevice& device, QueueFamilyIndex& index, const VkSurfaceKHR& surface) {
  const uint32_t queueFamilyCount = getQueueFamilyCount(device);

  std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
  getQueueFamilyProperties(device, queueFamilyCount, queueFamilies);

  bool queuesCompleted = false;

  int idx = 0;
  for (const VkQueueFamilyProperties& queueFamily : queueFamilies) {
    if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
      index.graphicsFamily = idx;
    }

    // No fkn way this means a 32 bit boolean. TODO: READ DOCS
    VkBool32 presentSupport;
    vkGetPhysicalDeviceSurfaceSupportKHR(
      device,
      idx,
      surface,
      &presentSupport
    );

    if (presentSupport) {
      index.presentFamily = idx;
    }

    if (index.isComplete()) {
      queuesCompleted = true;

      break;
    }

    idx++;
  }

  if (!queuesCompleted) {
    throw std::runtime_error("Didn't find all required queue indexes");
  }
}

uint32_t Queue::getQueueFamilyCount(const VkPhysicalDevice& device) {
  uint32_t familyCount = 0;

  vkGetPhysicalDeviceQueueFamilyProperties(device, &familyCount, nullptr);

  return familyCount;
}

uint32_t Queue::getQueueFamilyProperties(const VkPhysicalDevice& device, uint32_t queueFamilyCount, std::vector<VkQueueFamilyProperties>& queueFamilies) {
  std::cout << "Queue family count: " << queueFamilyCount << std::endl;

  vkGetPhysicalDeviceQueueFamilyProperties(
    device,
    &queueFamilyCount,
    queueFamilies.data()
  );

  return queueFamilyCount;
}
