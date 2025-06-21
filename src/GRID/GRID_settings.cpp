#include <GRID/GRID_settings.h>
#include <settings.h>

bool GRID_Settings::getUserSettingAsBool(const char* key) {
    return settings.getUserSettingAsBool(key);
}

int GRID_Settings::getUserSettingAsInt(const char* key) {
    return settings.getUserSettingAsInt(key);
}

double GRID_Settings::getUserSettingAsDouble(const char* key) {
    return settings.getUserSettingAsDouble(key);
}

std::string GRID_Settings::getUserSettingAsString(const char* key) {
    return settings.getUserSettingAsString(key);
}

std::string GRID_Settings::getRelativePath() {
    return settings.getRelativePath();
}