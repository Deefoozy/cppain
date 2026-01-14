#include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE

#include <cstdlib>
#include <iostream>

#include "classes/VisApp.h"

int main() {
  try {
    VisApp mainApplication;

    mainApplication.run();
    // wtf does that & do
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;

    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
