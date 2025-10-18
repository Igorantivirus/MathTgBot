#pragma once

#include <MathWorker/StringConvert/ComplexStringConverter.hpp>

struct OutputSettings
{
    mathWorker::ComplexOutputType complexType = mathWorker::ComplexOutputType::algebraic;
    mathWorker::AngleOutputType angleType = mathWorker::AngleOutputType::degrees;
    unsigned char precession = 6;
};