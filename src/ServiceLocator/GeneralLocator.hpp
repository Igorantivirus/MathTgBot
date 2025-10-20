#pragma once

#include <memory>

#include "Logger.hpp"
#include "Configs/ResponseConfig.hpp"
#include "Configs/MainConfig.hpp"

class Services
{
public:
    Services(const Services& other) = delete;
    Services(Services&& other) = delete;

    static void initInstance(const char* fileName)
    {
        instance().mainConfig.reset(new MainConfig{MainConfig::load(fileName)});
        
        Services::instance().responseConfig.reset(new ResponseConfig{ResponseConfig::load(instance().mainConfig->responseConfig)});
        Services::instance().log.reset(new Logger{instance().mainConfig->logFile, instance().mainConfig->prinToConsole});
    }

    static Services& instance()
    {
        static Services locator;
        return locator;
    }

    std::shared_ptr<Logger> log;
    std::shared_ptr<ResponseConfig> responseConfig;
    std::shared_ptr<MainConfig> mainConfig;

private:

    Services() = default;

};