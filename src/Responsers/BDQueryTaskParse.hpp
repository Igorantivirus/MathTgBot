#pragma once

#include <string>

#include <MathWorker/StringConvert/ComplexStringConverter.hpp>

#include <StringUtility.hpp>

#include "UsersDB.hpp"

class BDQueryTaskParse
{
public:

    bool processTask(const std::string& task, const std::int64_t id, UsersDB& db)
    {
        auto params = StringUtility::split(task, ':');
        if(params.size() != 3)
            return false;

        bool res = false;

        if(params[0] == "set")
        {
            if(params[1] == "angle")
                res = db.changeUserAngleType(id, static_cast<mathWorker::AngleOutputType>(params[2][0] - '0'));
            else if(params[1] == "numt")
                res = db.changeUserNumberType(id, static_cast<mathWorker::ComplexOutputType>(params[2][0] - '0'));
        }
        else if(params[0] == "add")
        {
            if(params[1] == "prec")
                res = db.addToPrecession(id, static_cast<unsigned char>(std::atoi(params[2].data())));
        }
        return res;
    }

};