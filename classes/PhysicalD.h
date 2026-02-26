#ifndef CPPAIN_PHYSICALD_H
#define CPPAIN_PHYSICALD_H

class PhysicalD {
private:
  static const std::vector<const char*> requiredDeviceExtensions;
public:
  static uint32_t getPhysicalDCount(const VkInstance& instance);
  static void getPhysicalDs(const VkInstance& instance, uint32_t deviceCount, std::vector<VkPhysicalDevice>& physicalDs);
  static bool deviceIsViable(const VkPhysicalDevice& physicalD);
  static void selectDevice(VkPhysicalDevice& physicalDevice, std::vector<VkPhysicalDevice>& physicalDs);
  static bool checkExtensionSupport(const VkPhysicalDevice& physicalD);
  static uint32_t getExtensionCount(const VkPhysicalDevice& physicalD);
  static void getExtensions(const VkPhysicalDevice& physicalD, uint32_t extensionCount, std::vector<VkExtensionProperties>& availableExtensions);
};

#endif // CPPAIN_PHYSICALD_H
