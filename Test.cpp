#include "app.cpp"

void App::run(){
  initWindow();
  initVulkan();
  mainLoop();
}

// main loop for the app
void App:mainLoop()
