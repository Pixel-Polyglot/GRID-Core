#pragma once

#include <string>
#include <iostream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Settings {
public:
    Settings();
    ~Settings();

    void loadSettings(std::string filePath);

    bool getUserSettingAsBool(std::string key);
    int getUserSettingAsInt(std::string key);
    double getUserSettingAsDouble(std::string key);
    std::string getUserSettingAsString(std::string key);

    std::string getRelativePath();

    template<typename T>
    T getSetting(std::string key) {
        if (!m_data.contains(key)) {
            std::cout << "Setting: " << key << " does not exist" << std::endl;
            return T{};
        }
        return m_data.at(key).get<T>();
    }

private:
    template<typename T>
    T getUserSetting(std::string key) {
        if (m_userSettings.is_null()) {
            std::cout << "No user settings loaded" << std::endl;
            return T{};
        } else {
            if (!m_userSettings.contains(key)) {
                std::cout << "User setting: " << key << " does not exist" << std::endl;
                return T{};
            }
            return m_userSettings.at(key).get<T>();
        }
    }

    std::string m_relativePath;

    json m_data;
    json m_userSettings;
};

extern Settings settings;