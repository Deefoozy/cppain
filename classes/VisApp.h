#ifndef CPPAIN_VISAPP_H
#define CPPAIN_VISAPP_H

class VisApp {
public:
  void run();
private:
  bool hasWindow_val = false;
  bool *hasWindow = &hasWindow_val;

  bool glfwIsReady_val = false;
  bool *glfwIsReady = &glfwIsReady_val;

  GLFWwindow *windows = nullptr;

  void createWindow();

  void mainLoop() const;

  void cleanup() const;
};

#endif //CPPAIN_VISAPP_H