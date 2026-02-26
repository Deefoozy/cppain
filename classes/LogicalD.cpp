#include <vulkan/vulkan_core.h>

#include <set>
#include <stdexcept>

#include "Queue.h"

#include "LogicalD.h"

void LogicalD::createDevice(
  const VkPhysicalDevice &physicalDevice,
  const QueueFamilyIndex &queueIndex,
  VkDevice *device
) {
  constexpr float queuePriority = 1.0f;

  std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
  const std::set<uint32_t> queueFamilies = queueIndex.as_set();

  uint32_t queueCount = 0;
  for (uint32_t queueFamily : queueFamilies) {
    // TODO: Create config json file that contains config info for all VkCreateInfo structs we have here.
    VkDeviceQueueCreateInfo queueCreateInfo {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = queueFamily;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &queuePriority;

    queueCreateInfos.push_back(queueCreateInfo);
    queueCount++;
  }

  VkPhysicalDeviceFeatures physicalDeviceFeatures {};

  VkDeviceCreateInfo deviceCreateInfo {};
  deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
  deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
  deviceCreateInfo.queueCreateInfoCount = queueCount;
  deviceCreateInfo.pEnabledFeatures = &physicalDeviceFeatures;

  deviceCreateInfo.enabledExtensionCount = 0;
  deviceCreateInfo.enabledLayerCount = 0;

  if (vkCreateDevice(physicalDevice, &deviceCreateInfo, nullptr, device) != VK_SUCCESS) {
    throw std::runtime_error("Couldn't create logical D");
  }
}
