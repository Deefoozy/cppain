#ifndef CPPAIN_QUEUE_H
#define CPPAIN_QUEUE_H

#include <optional>
#include <vector>

struct QueueFamilyIndex {
  std::optional<uint32_t> graphicsFamily;

  [[nodiscard]] bool isComplete() const {
    return (
      this->graphicsFamily.has_value()
    );
  }
};

class Queue {
public:
  static void getQueueFamilies(const VkPhysicalDevice & device, QueueFamilyIndex& index);
  static uint32_t getQueueFamilyCount(const VkPhysicalDevice & device);
  static uint32_t getQueueFamilyProperties(const VkPhysicalDevice & device, uint32_t queueFamilyCount, std::vector<VkQueueFamilyProperties>& queueFamilies);
};

#endif // CPPAIN_QUEUE_H
