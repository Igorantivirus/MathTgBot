#pragma once

#include <tgbot/tgbot.h>

#include <ServiceLocator/GeneralLocator.hpp>
#include <ServiceLocator/ExternService.hpp>
#include <Responsers/Responser.hpp>
#include <tgbot/types/CallbackQuery.h>

#include "OutpuSettingsToString.hpp"
#include "MessageButtonsGenerate.hpp"

class Bot
{
public:
    Bot(const std::string& key) : bot_(key)
    {
        bot_.getEvents().onNonCommandMessage(std::bind(&Bot::onNonCommandMessage, this, std::placeholders::_1));
        bot_.getEvents().onInlineQuery(      std::bind(&Bot::onInlineQuery,       this, std::placeholders::_1));
        bot_.getEvents().onCallbackQuery(    std::bind(&Bot::onCallbackQuery,     this, std::placeholders::_1));

        bot_.getEvents().onCommand("help",          std::bind(&Bot::help,    this, std::placeholders::_1));
        bot_.getEvents().onCommand("start",         std::bind(&Bot::start,    this, std::placeholders::_1));
        bot_.getEvents().onCommand("settings",      std::bind(&Bot::settings, this, std::placeholders::_1));
        bot_.getEvents().onCommand("mathinfo",      std::bind(&Bot::mathinfo, this, std::placeholders::_1));
    }

    void run()
    {
        TgBot::TgLongPoll longPoll(bot_);
        service::log("Bot running", LogLevel::Info);
        while (true)
        {
            try
            {
                longPoll.start();
            }
            catch (const TgBot::TgException& e)
            {
                Services::instance().log->log(std::string("Bot error: ") + e.what(), LogLevel::Error);
            }
            catch(const std::exception& e)
            {
                Services::instance().log->log(std::string("Bot error: ") + e.what(), LogLevel::Error);
            }
            catch (...)
            {
                Services::instance().log->log("Unknown Error", LogLevel::Error);
            }
        }
    }

private:

    TgBot::Bot bot_;
    Responser responser_;
    MessageButtonsGenerate generator_;

private:

    void sendMessage(const std::int64_t id, const std::string& msg, TgBot::InlineKeyboardMarkup::Ptr kb = nullptr, bool useMd = true)
    {
        const char* type = useMd ? "Markdown" : "";
        bot_.getApi().sendMessage(id, msg, false, 0, kb, type);
    }

private:

    void onNonCommandMessage(TgBot::Message::Ptr message)
    {
        std::string res = responser_.onMessage(message->text, message->from->id);
        sendMessage(message->chat->id, res, nullptr, false);
    }

    void onInlineQuery(const TgBot::InlineQuery::Ptr& query)
    {
        auto [label, text] = responser_.onInlineMessage(query->query, query->from->id);
        if (label.empty())
            return;

        std::vector<TgBot::InlineQueryResult::Ptr> results;
        TgBot::InlineQueryResultArticle::Ptr article = std::make_shared<TgBot::InlineQueryResultArticle>();

        article->title = label;
        article->id = "1";

        TgBot::InputTextMessageContent::Ptr messageContent = std::make_shared<TgBot::InputTextMessageContent>();
        messageContent->messageText = text;
        article->inputMessageContent = messageContent;

        results.push_back(article);
        bot_.getApi().answerInlineQuery(query->id, results);
    }

    void onCallbackQuery(const TgBot::CallbackQuery::Ptr& query)
    {
        if(!responser_.processQuery(query->data, query->from->id))
            return;

        auto sets = responser_.printSettings(query->from->id);
        std::string setsStr = Convert::toString(sets);
        auto kb = generator_.makeSettingsKb();

        bot_.getApi().editMessageText(setsStr, query->message->chat->id, query->message->messageId, "", "Markdown", false, kb);
    }

private:

    void start(TgBot::Message::Ptr message)
    {
        responser_.start(message->chat->id);
        sendMessage(message->chat->id, service::responses().start);
    }
    void settings(TgBot::Message::Ptr message)
    {
        auto sets = responser_.printSettings(message->chat->id);
        std::string setsStr = Convert::toString(sets);
        
        auto kb = generator_.makeSettingsKb();
        sendMessage(message->chat->id, setsStr, kb);
    }
    void help(TgBot::Message::Ptr message)
    {
        sendMessage(message->chat->id, service::responses().help);
    }
    void mathinfo(TgBot::Message::Ptr message)
    {
        sendMessage(message->chat->id, service::responses().mathinfo);
    }
};
