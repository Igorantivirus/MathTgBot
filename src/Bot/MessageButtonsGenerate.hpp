#pragma once

#include <tgbot/tgbot.h>

#include <MathWorker/StringConvert/ComplexStringConverter.hpp>

#include <Responsers/OutputSettings.hpp>

class MessageButtonsGenerate
{
public:
    TgBot::InlineKeyboardMarkup::Ptr makeSettingsKb(const OutputSettings &s)
    {
        auto kb = std::make_shared<TgBot::InlineKeyboardMarkup>();

        kb->inlineKeyboard.push_back(generateDegreeSettingsButtons());
        return kb;
    }

private:
    std::vector<TgBot::InlineKeyboardButton::Ptr> generateDegreeSettingsButtons()
    {
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;

        auto toRad = std::make_shared<TgBot::InlineKeyboardButton>();
        toRad->text = "Выводить радианы";
        toRad->callbackData = "set:angle:0";

        auto toDeg = std::make_shared<TgBot::InlineKeyboardButton>();
        toDeg->text = "Выводить градусы";
        toDeg->callbackData = "set:angle:1";

        row.push_back(toRad);
        row.push_back(toDeg);
        return row;
    }
};