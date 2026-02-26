#ifndef CPPAIN_VISAPP_H
#define CPPAIN_VISAPP_H

#include "Queue.h"

class VisApp {
public:
  void run();
private:
  VkInstance instance = nullptr;
  GLFWwindow* windows = nullptr;
  VkDevice device = nullptr;
  VkQueue graphicsQueue = nullptr;

  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  QueueFamilyIndex queueIndex {};

  void createWindow();

  void initVulkan();

  void assignPhysicalDevice();

  void createDevice();

  void getQueue();

  void mainLoop() const;

  void cleanup() const;
};

#endif //CPPAIN_VISAPP_H