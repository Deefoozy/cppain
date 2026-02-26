#include <vulkan/vulkan_core.h>

#include "Queue.h"

#include "LogicalD.h"

void LogicalD::createDevice(
  const VkPhysicalDevice &physicalDevice,
  const QueueFamilyIndex &queueIndex,
  VkDevice *device
) {
  constexpr float queuePriority = 1.0f;

  // TODO: Create config json file that contains config info for all VkCreateInfo structs we have here.
  // ^ This also means more specific configuration. Like being able to configure which queue types are required etc.
  VkDeviceQueueCreateInfo queueCreateInfo {};
  queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
  queueCreateInfo.queueFamilyIndex = queueIndex.graphicsFamily.value();
  queueCreateInfo.queueCount = 1;
  queueCreateInfo.pQueuePriorities = &queuePriority;

  VkPhysicalDeviceFeatures physicalDeviceFeatures {};

  VkDeviceCreateInfo deviceCreateInfo {};
  deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
  deviceCreateInfo.queueCreateInfoCount = 1;
  deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

  deviceCreateInfo.enabledExtensionCount = 0;
  deviceCreateInfo.enabledLayerCount = 0;

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, device)) {

  }
}
