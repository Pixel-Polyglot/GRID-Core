#pragma once

#include "export.h"
#include <string>

class EXPORT GRID_Settings {
public:
    static bool getUserSettingAsBool(const char* key);
    static int getUserSettingAsInt(const char* key);
    static double getUserSettingAsDouble(const char* key);
    static std::string getUserSettingAsString(const char* key);

    static std::string getRelativePath();
};