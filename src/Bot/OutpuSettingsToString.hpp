#pragma once

#include <array>
#include <format>
#include <string>

#include <Responsers/OutputSettings.hpp>

namespace Convert
{
    static std::string toString(const mathWorker::ComplexOutputType v)
    {
        static const std::array<std::string, 4> converter = 
        {
            "algebraic",
            "trigonometric",
            "indicative",
            "polar"
        };
        return converter[static_cast<std::size_t>(v)];
    }
    static std::string toString(const mathWorker::AngleOutputType v)
    {
        return v == mathWorker::AngleOutputType::degrees ? "degrees" : "radians";
    }

    static std::string toString(const OutputSettings& s)
    {
        return std::format("Число знаков:\t{:d}\nТип вывода углов:\t{}\nТип вывода чисел:\t{}",
            static_cast<int>(s.precession), toString(s.angleType), toString(s.complexType));
    }
}