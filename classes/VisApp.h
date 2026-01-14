#ifndef CPPAIN_VISAPP_H
#define CPPAIN_VISAPP_H

class VisApp {
public:
  void run();
private:
  VkInstance instance = nullptr;
  GLFWwindow *windows = nullptr;

  void createWindow();

  void initVulkan();

  void mainLoop() const;

  void cleanup() const;
};

#endif //CPPAIN_VISAPP_H