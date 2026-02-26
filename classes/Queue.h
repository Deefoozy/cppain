#ifndef CPPAIN_QUEUE_H
#define CPPAIN_QUEUE_H

#include <optional>
#include <set>
#include <vector>

struct QueueFamilyIndex {
  std::optional<uint32_t> graphicsFamily;
  std::optional<uint32_t> presentFamily;

  [[nodiscard]] bool isComplete() const {
    return (
      this->graphicsFamily.has_value() &&
      this->presentFamily.has_value()
    );
  }

  [[nodiscard]] std::set<uint32_t> as_set() const {
    return {
      this->graphicsFamily.value(),
      this->presentFamily.value()
    };
  }
};

class Queue {
public:
  static void getQueueFamilies(const VkPhysicalDevice & device, QueueFamilyIndex& index, const VkSurfaceKHR& surface);
  static uint32_t getQueueFamilyCount(const VkPhysicalDevice & device);
  static uint32_t getQueueFamilyProperties(const VkPhysicalDevice & device, uint32_t queueFamilyCount, std::vector<VkQueueFamilyProperties>& queueFamilies);
};

#endif // CPPAIN_QUEUE_H
