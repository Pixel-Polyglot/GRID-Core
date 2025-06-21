#include "GRID/GRID.h"
#include <version.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
      LPSTR msg = nullptr;
      FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, GetLastError(), 0, (LPSTR)&msg, 0, nullptr);
      std::cerr << "Failed to load library: " << appPath << "\n" << "Windows error: " << (msg ? msg : "Unknown error") << std::endl;
      LocalFree(msg);
    #else
      std::cout << "Failed to load library: " << dlerror() << " " << appPath.c_str() << std::endl;
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

  window.init("GPU", glm::ivec2(800, 600), 4, 5);
  window.enableVsync(true);

  ui.init(window.getWindow(), 4, 5);

  appInit(argc, argv);

  appSetWidgets();

  while (!glfwWindowShouldClose(window.getWindow())) {
    glfwPollEvents();
    appRun();
    ui.render();
    glfwSwapBuffers(window.getWindow());
    window.setDeltaTime();
  }

  appDestroy();
  ui.destroy();
  window.destroy();
}
