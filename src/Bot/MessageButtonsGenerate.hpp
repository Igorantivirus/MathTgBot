#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

#include <tgbot/tgbot.h>

#include <MathWorker/StringConvert/ComplexStringConverter.hpp>

class MessageButtonsGenerate
{
public:
    TgBot::InlineKeyboardMarkup::Ptr makeSettingsKb()
    {
        static TgBot::InlineKeyboardMarkup::Ptr kb;
        if(!kb)
        {
            kb = std::make_shared<TgBot::InlineKeyboardMarkup>();
            kb->inlineKeyboard.push_back(generateButtons({
                {"Радианы", "set:angle:0"},
                {"Градусы", "set:angle:1"}
            }));
            
            kb->inlineKeyboard.push_back(generateButtons({
                {"Алгебр", "set:numt:0"},
                {"Триган", "set:numt:1"},
                {"Степен", "set:numt:2"},
                {"Полярн", "set:numt:3"}
            }));

            kb->inlineKeyboard.push_back(generateButtons({
                {"Знаки: +1", "add:prec:1"},
                {"Знаки: -1", "add:prec:-1"}
            }));
        }

        return kb;
    }

private:
    static TgBot::InlineKeyboardButton::Ptr getBytton(const std::string_view text, const std::string_view callback)
    {
        auto res = std::make_shared<TgBot::InlineKeyboardButton>();
        res->text = text;
        res->callbackData = callback;
        return res;
    }
    static std::vector<TgBot::InlineKeyboardButton::Ptr> generateButtons(const std::unordered_map<std::string, std::string> &map)
    {
        std::vector<TgBot::InlineKeyboardButton::Ptr> row;
        for (auto &[a, b] : map)
            row.push_back(getBytton(a, b));
        return row;
    }
};