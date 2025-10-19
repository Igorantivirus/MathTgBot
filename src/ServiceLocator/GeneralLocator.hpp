#pragma once

#include <memory>

#include "Logger.hpp"
#include "ResponseConfig.hpp"

class Services
{
public:
    Services(const Services& other) = delete;
    Services(Services&& other) = delete;

    static Services& instance()
    {
        static Services locator;
        return locator;
    }

    std::shared_ptr<Logger> log;
    std::shared_ptr<ResponseConfig> config;

private:

    Services() = default;

};