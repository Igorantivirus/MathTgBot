#pragma once

#include <span>
#include <string>
#include <string_view>
#include <utility>

#include <MathWorker/MathWorker.hpp>

#include <StringUtility.hpp>
#include "Responsers/OutputSettings.hpp"
#include "UsersDB.hpp"
#include "BDQueryTaskParse.hpp"

class Responser
{
public:
    Responser()
    {
        db_.openFile("file.db");
    }

    void start(const std::int64_t id)
    {
        db_.addUserByID(id, OutputSettings{});
    }

    //@result {Label, return text}
    std::pair<std::string, std::string> onInlineMessage(const std::string& message, const std::int64_t id)
    {
        if(message.empty() || message.back() != '=')
            return std::make_pair<std::string, std::string>("", "");

        auto params = StringUtility::split(message, '\n');
        mathWorker::ComplexStringConverter converter;
        
        std::string label = process(params, converter);
        std::string text = message + label;
        return std::make_pair(label, text);
    }

    OutputSettings printSettings(const std::int64_t id)
    {
        return db_.getUserById(id);
    }

    bool processQuery(const std::string& str, const std::int64_t id)
    {
        return tasker_.processTask(str, id, db_);
    }

private:

    UsersDB db_;
    BDQueryTaskParse tasker_;

private:

    std::string process(const std::vector<std::string_view>& params, const mathWorker::ComplexStringConverter& converter)
    {
        try
        {
            const std::span<const std::string_view> spn{params.begin(), params.end() - 1};
            std::string_view stringToParse = params.back();
            stringToParse.remove_suffix(1);
            return clearProcessMath(stringToParse, spn, converter);
        }
        catch (const mathWorker::ParseException &e)
        {
            return std::string("Math error: ") + e.what();
        }
        catch (const std::exception &e)
        {
            return std::string("Bot error: ") + e.what();
        }
        catch (...)
        {
            return "Unknown error.";
        }
    }
    std::string clearProcessMath(const std::string_view expression, const std::span<const std::string_view> additional, const mathWorker::ComplexStringConverter& converter) noexcept(false)
    {
        mathWorker::Signature signature = mathWorker::generator::mathSignature();
        mathWorker::BaseTokenizer tokenizer{signature};
        mathWorker::MathParser parser(tokenizer);
        mathWorker::DirectSignatureConnector connector(signature);

        for (const auto &i : additional)
            connector.addTerm(std::string(i));

        return parser.parse(expression)->replace(signature.getVariableContext())->calculate(signature)->toString(converter);
    }

};