#pragma once

#include "export.h"

EXPORT_FUNCTION void start(const char* jsonPath, int argc, char* argv[]);
EXPORT_FUNCTION void setWidgets();
EXPORT_FUNCTION void init(int argc, char* argv[]);
EXPORT_FUNCTION void run();
EXPORT_FUNCTION void destroy();