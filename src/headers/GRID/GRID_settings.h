#pragma once

#include "export.h"
#include <string>

class EXPORT GRID_Settings {
public:
    static bool getUserSettingAsBool(std::string key);
    static int getUserSettingAsInt(std::string key);
    static double getUserSettingAsDouble(std::string key);
    static std::string getUserSettingAsString(std::string key);

    static std::string getRelativePath();
};