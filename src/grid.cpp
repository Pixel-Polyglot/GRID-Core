#include <grid.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GRID/window.h>
#include <GRID/ui.h>
#include <GRID/renderer.h>
#include <unistd.h>
#include <limits.h>
#include <dlfcn.h>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using AppFunc = void (*)();
using AppFuncVersion = int (*)();

extern "C" void start(const char* jsonPath) __attribute__((visibility("default")));

extern "C" void start(const char* jsonPath) {
	std::cout << "GRID Core v0.1" << std::endl;

	char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));

	std::ifstream f(jsonPath);
	json data;
	try {
		data = json::parse(f);
	}
	catch (const json::parse_error& e) {
		std::cout << "Invalid JSON config: " << jsonPath << std::endl;
		return;
	}

	std::string appPath = std::string(cwd) + "/" + data["applicationLib"].get<std::string>();

	void* hAppLib = dlopen(appPath.c_str(), RTLD_LAZY);
    if (hAppLib == nullptr) {
        std::cout << "failed to load application library " << dlerror() << std::endl;
    }

	AppFunc appInit = (AppFunc) dlsym(hAppLib, "init");
	AppFunc appRun = (AppFunc) dlsym(hAppLib, "run");
	AppFunc appDestroy = (AppFunc) dlsym(hAppLib, "destroy");
	AppFunc appSetWidgets = (AppFunc) dlsym(hAppLib, "setWidgets");
	AppFuncVersion appGetVersionMajor = (AppFuncVersion) dlsym(hAppLib, "getVersionMajor");
	AppFuncVersion appGetVersionMinor = (AppFuncVersion) dlsym(hAppLib, "getVersionMinor");

    if (appInit == nullptr) {
        std::cout << "failed to load function: init" << std::endl;
    }

	if (appRun == nullptr) {
        std::cout << "failed to load function: run" << std::endl;
    }

	if (appDestroy == nullptr) {
        std::cout << "failed to load function: destroy" << std::endl;
    }

	if (appSetWidgets == nullptr) {
        std::cout << "failed to load function: setWidgets" << std::endl;
    }

	if (appGetVersionMajor == nullptr) {
        std::cout << "failed to load function: getVersionMajor" << std::endl;
    }

	if (appGetVersionMinor == nullptr) {
        std::cout << "failed to load function: getVersionMinor" << std::endl;
    }

	std::cout << "GRID Application v" << appGetVersionMajor() << "." << appGetVersionMinor() << std::endl;
	std::cout << data["name"].get<std::string>() << std::endl;

	window.init("GPU", 800, 600, 4, 5);
	window.enableVsync(true);

	ui.init(window.getWindow(), 4, 5);
	renderer.init();

	appInit();

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