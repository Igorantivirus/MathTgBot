#pragma once

#include "Configs/MainConfig.hpp"
#include "GeneralLocator.hpp"

namespace service
{
    static void log(const std::string& message, LogLevel level)
    {
        Services::instance().log->log(message, level);
    }
    static ResponseConfig responses()
    {
        return *Services::instance().responseConfig;
    }
    static MainConfig config()
    {
        return *Services::instance().mainConfig;
    }
}