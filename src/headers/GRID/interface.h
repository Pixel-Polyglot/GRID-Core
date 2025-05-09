#pragma once
#include <GRID/version.h>

extern "C" int getVersionMajor() __attribute__((visibility("default")));
extern "C" int getVersionMinor() __attribute__((visibility("default")));
extern "C" void setWidgets() __attribute__((visibility("default")));
extern "C" void init(int argc, char* argv[]) __attribute__((visibility("default")));
extern "C" void run() __attribute__((visibility("default")));
extern "C" void destroy() __attribute__((visibility("default")));

extern "C" int getVersionMajor() {
	return VERSION_MAJOR;
}

extern "C" int getVersionMinor() {
	return VERSION_MINOR;
}