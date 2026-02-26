#ifndef CPPAIN_LOGICALD_H
#define CPPAIN_LOGICALD_H

#include "Queue.h"

class LogicalD {
public:
  static void createDevice(const VkPhysicalDevice &physicalDevice, const QueueFamilyIndex &queueIndex, VkDevice* device);
};

#endif // CPPAIN_LOGICALD_H
