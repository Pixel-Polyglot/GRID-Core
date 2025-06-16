#include "GRID/GRID.h"
#include <version.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer.h>
#include <ui.h>
#include <window.h>
#include <fstream>
#include <limits.h>
#include <GRID/export.h>
#include <nlohmann/json.hpp>
#include <string>
using json = nlohmann::json;

using AppFunc = void (*)();
using AppFuncInit = void (*)(int atgc, char *argv[]);
using AppFuncVersion = int (*)();

extern "C" void start(const char *jsonPath, int argc, char *argv[]) {
  std::cout << "GRID Core v" << getVersionMajor() << "." << getVersionMinor() << std::endl;

  char cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));

  std::ifstream f(jsonPath);
  json data;
  // try {
  data = json::parse(f);
/*
 catch (const json::parse_error& e) {
         std::cout << "Invalid JSON config: " << jsonPath << std::endl;
         return;
 }*/

  std::string appPath = std::string(cwd) + "/" +
  data["applicationLib"].get<std::string>();

  #ifdef _WIN32
    HMODULE hAppLib = LoadLibrary(appPath.c_str());
  #else
    void* hAppLib = dlopen(appPath.c_str(), RTLD_LAZY);
  #endif

  if (hAppLib == nullptr) {
  #ifdef _WIN32
    std::cout << "Failed to load application library" << std::endl;
  #else
    std::cout << "Failed to load application library: " << dlerror() << std::endl;
  #endif
}

AppFuncInit appInit = (AppFuncInit)dlsym(hAppLib, "init");
AppFunc appRun = (AppFunc)dlsym(hAppLib, "run");
AppFunc appDestroy = (AppFunc)dlsym(hAppLib, "destroy");
AppFunc appSetWidgets = (AppFunc)dlsym(hAppLib, "setWidgets");

if (appInit == nullptr) {
  std::cout << "Failed to load function: init" << std::endl;
}

if (appRun == nullptr) {
  std::cout << "Failed to load function: run" << std::endl;
}

if (appDestroy == nullptr) {
  std::cout << "Failed to load function: destroy" << std::endl;
}

if (appSetWidgets == nullptr) {
  std::cout << "Failed to load function: setWidgets" << std::endl;
}

// std::cout << "GRID Application v" << appGetVersionMajor() << "." <<
// appGetVersionMinor() << std::endl;
std::cout << data["name"].get<std::string>() << std::endl;

window.init("GPU", 800, 600, 4, 5);
window.enableVsync(true);

ui.init(window.getWindow(), 4, 5);
renderer.init();

appInit(argc, argv);

appSetWidgets();

while (!glfwWindowShouldClose(window.getWindow())) {
  glfwPollEvents();
  appRun();
  ui.render();
  glfwSwapBuffers(window.getWindow());
}

appDestroy();
renderer.destroy();
ui.destroy();
window.destroy();
}
