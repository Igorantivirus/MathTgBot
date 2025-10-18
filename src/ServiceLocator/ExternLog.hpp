#pragma once

#include "GeneralLocator.hpp"

namespace externLog
{
    static void log(const std::string& message, LogLevel level)
    {
        Services::instance().log->log(message, level);
    }
}