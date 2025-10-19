// ResponseConfig.hpp
#pragma once

#include <string>
#include <fstream>

#include <nlohmann/json.hpp>

struct ResponseConfig
{
    std::string start;
    std::string help;
    std::string mathinfo;
    std::string degr;
    std::string rads;
    std::string algebraic;
    std::string trigonometric;
    std::string indicative;
    std::string polar;
    std::string settings;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ResponseConfig, start, help, mathinfo, degr, rads, algebraic, trigonometric, indicative, polar, settings)

    static ResponseConfig load(const std::string &config_path)
    {
        std::ifstream config_file(config_path);
        if (!config_file.is_open())
            throw std::runtime_error("Cannot open config file: " + config_path);
        nlohmann::json config = nlohmann::json::parse(config_file);
        return config.template get<ResponseConfig>();
    }

};
