#ifndef CPPAIN_PHYSICALD_H
#define CPPAIN_PHYSICALD_H

class PhysicalD {
public:
  static uint32_t getPhysicalDCount(const VkInstance& instance);
  static uint32_t getPhysicalDs(const VkInstance& instance, std::vector<VkPhysicalDevice>& physicalDs);
  static bool deviceIsViable(const VkPhysicalDevice& physicalD);
  static void selectDevice(VkPhysicalDevice& physicalDevice, std::vector<VkPhysicalDevice>& physicalDs);
};

#endif // CPPAIN_PHYSICALD_H
