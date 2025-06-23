#include <settings.h>
#include <fstream>
#include <iostream>

Settings settings;

Settings::Settings() {
}

Settings::~Settings() {
}

void Settings::loadSettings(std::string filePath) {
    std::ifstream f(filePath);
    json data;
    m_data = json::parse(f);
    if (m_data.contains("userSettings")) {
        m_userSettings = m_data["userSettings"];
    }

    std::string jsonPathString = std::string(filePath);
    m_relativePath = jsonPathString.substr(0, jsonPathString.find_last_of("/"));
}

bool Settings::getUserSettingAsBool(std::string key) {
    return getUserSetting<bool>(key);
}

int Settings::getUserSettingAsInt(std::string key) {
    return getUserSetting<int>(key);
}

double Settings::getUserSettingAsDouble(std::string key) {
    return getUserSetting<double>(key);
}

std::string Settings::getUserSettingAsString(std::string key) {
    return getUserSetting<std::string>(key);
}

std::string Settings::getRelativePath() {
    return m_relativePath;
}