#include "ServiceLocator/GeneralLocator.hpp"
#include <BotApiKey.hpp>

#include <Bot/Bot.hpp>
#include <ServiceLocator/ExternService.hpp>

#if defined(_WIN32) || defined(_WIN64)
const std::string TgBot::InlineQueryResultArticle::TYPE = "article";
const std::string TgBot::InputTextMessageContent::TYPE = "text";
#endif

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    std::system("chcp 65001 > nul");
#endif

    Services::initInstance("mainConfig.json");

    Bot bot(service::config().tgApiKey);
    bot.run();

    return 0;
}
