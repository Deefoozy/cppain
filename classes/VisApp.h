#include <vector>

#ifndef CPPAIN_VISAPP_H
#define CPPAIN_VISAPP_H

class VisApp {
public:
  void run();
private:
  VkInstance instance = nullptr;
  GLFWwindow* windows = nullptr;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  void createWindow();

  void initVulkan();

  void assignPhysicalDevice();

  void mainLoop() const;

  void cleanup() const;

  static bool checkValidationLayerSupport();
};

#endif //CPPAIN_VISAPP_H