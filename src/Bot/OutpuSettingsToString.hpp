#pragma once

#include "StringUtility.hpp"
#include <array>
#include <string>

#include <Responsers/OutputSettings.hpp>
#include <ServiceLocator/ExternService.hpp>
#include <StringUtility.hpp>

template <class... Args>
std::string format_rt(std::string_view fmt, Args&&... args) {
    // Бросает std::format_error при плохом формате/несоответствии типов.
    return std::vformat(fmt, std::make_format_args(std::forward<Args>(args)...));
}

namespace Convert
{
    static std::string toString(const mathWorker::ComplexOutputType v)
    {
        const std::array<std::string, 4> converter = 
        {
            service::config().algebraic,
            service::config().trigonometric,
            service::config().indicative,
            service::config().polar
        };
        return converter[static_cast<std::size_t>(v)];
    }
    static std::string toString(const mathWorker::AngleOutputType v)
    {
        return v == mathWorker::AngleOutputType::degrees ? service::config().degr : service::config().rads;
    }

    static std::string toString(const OutputSettings& s)
    {
        return StringUtility::rtFormat
        (
            service::config().settings, 
            {std::to_string(static_cast<int>(s.precession)), toString(s.angleType), toString(s.complexType)}    
        );
    }
}