#pragma once

#include "export.h"
#include <string>

EXPORT_FUNCTION void start(std::string jsonPath, int argc, char* argv[]);
EXPORT_FUNCTION void setWidgets();
EXPORT_FUNCTION void init(int argc, char* argv[]);
EXPORT_FUNCTION void run();
EXPORT_FUNCTION void destroy();