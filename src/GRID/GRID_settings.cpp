#include <GRID/GRID_settings.h>
#include <settings.h>

bool GRID_Settings::getUserSettingAsBool(std::string key) {
    return settings.getUserSettingAsBool(key);
}

int GRID_Settings::getUserSettingAsInt(std::string key) {
    return settings.getUserSettingAsInt(key);
}

double GRID_Settings::getUserSettingAsDouble(std::string key) {
    return settings.getUserSettingAsDouble(key);
}

std::string GRID_Settings::getUserSettingAsString(std::string key) {
    return settings.getUserSettingAsString(key);
}

std::string GRID_Settings::getRelativePath() {
    return settings.getRelativePath();
}