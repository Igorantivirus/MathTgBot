#pragma once

#include "GeneralLocator.hpp"

namespace service
{
    static void log(const std::string& message, LogLevel level)
    {
        Services::instance().log->log(message, level);
    }
    static ResponseConfig config()
    {
        return *Services::instance().config;
    }
}