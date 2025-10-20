#pragma once

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

struct MainConfig
{
    std::string tgApiKey;
    std::string responseConfig;
    std::string dataBaseFile;
    std::string logFile;
    bool prinToConsole = {};

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MainConfig, tgApiKey, responseConfig, dataBaseFile, logFile, prinToConsole)

    static MainConfig load(const std::string &config_path)
    {
        std::ifstream config_file(config_path);
        if (!config_file.is_open())
            throw std::runtime_error("Cannot open config file: " + config_path);
        nlohmann::json config = nlohmann::json::parse(config_file);
        return config.template get<MainConfig>();
    }

};
