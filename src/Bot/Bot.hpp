#pragma once

#include <utility>

#include <tgbot/tgbot.h>

#include <ServiceLocator/GeneralLocator.hpp>
#include <ServiceLocator/ExternLog.hpp>

#include <Responsers/Responser.hpp>

class Bot
{
public:
    Bot(const char *key) : bot_(key)
    {
        bot_.getEvents().onNonCommandMessage(   std::bind(&Bot::onNonCommandMessage,    this, std::placeholders::_1));
        bot_.getEvents().onInlineQuery(         std::bind(&Bot::onInlineQuery,          this, std::placeholders::_1));

        bot_.getEvents().onCommand("start",     std::bind(&Bot::start,     this, std::placeholders::_1));
    }

    void run()
    {
        TgBot::TgLongPoll longPoll(bot_);
        externLog::log("Bot running", LogLevel::Info);
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

private:

    void onNonCommandMessage(TgBot::Message::Ptr message)
    {
        bot_.getApi().sendMessage(message->chat->id, "я в тесте!");
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

private:

    void start(TgBot::Message::Ptr message)
    {
        responser_.start(message->chat->id);
    }
};
