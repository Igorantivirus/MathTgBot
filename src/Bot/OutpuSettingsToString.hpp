#pragma once

#include "StringUtility.hpp"
#include <array>
#include <string>

#include <Responsers/OutputSettings.hpp>
#include <ServiceLocator/ExternService.hpp>
#include <StringUtility.hpp>

namespace Convert
{
    static std::string toString(const mathWorker::ComplexOutputType v)
    {
        const std::array<std::string, 4> converter = 
        {
            service::responses().algebraic,
            service::responses().trigonometric,
            service::responses().indicative,
            service::responses().polar
        };
        return converter[static_cast<std::size_t>(v)];
    }
    static std::string toString(const mathWorker::AngleOutputType v)
    {
        return v == mathWorker::AngleOutputType::degrees ? service::responses().degr : service::responses().rads;
    }

    static std::string toString(const OutputSettings& s)
    {
        return StringUtility::rtFormat
        (
            service::responses().settings, 
            {std::to_string(static_cast<int>(s.precession)), toString(s.angleType), toString(s.complexType)}    
        );
    }
}