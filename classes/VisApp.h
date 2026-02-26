#ifndef CPPAIN_VISAPP_H
#define CPPAIN_VISAPP_H

#include "Queue.h"

class VisApp {
public:
  void run();
private:
  QueueFamilyIndex queueIndex {};

  GLFWwindow* windows = nullptr;

  VkInstance instance = nullptr;
  VkDevice device = nullptr;
  VkQueue graphicsQueue = nullptr;
  VkQueue presentQueue = nullptr;
  VkSurfaceKHR surface = nullptr;
  VkPhysicalDevice physicalDevice = nullptr;

  void createWindow();

  void initVulkan();

  void assignPhysicalDevice();

  void createDevice();

  void getQueues();

  void createSurface();

  void mainLoop() const;

  void cleanup() const;
};

#endif //CPPAIN_VISAPP_H