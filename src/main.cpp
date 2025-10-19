#include <BotApiKey.hpp>

#include <Bot/Bot.hpp>
#include <ServiceLocator/ExternService.hpp>

#define LOG_FILE "log.log"
#define CONFIG_FILE "responseConfig.json"

#if defined(_WIN32) || defined(_WIN64)
const std::string TgBot::InlineQueryResultArticle::TYPE = "article";
const std::string TgBot::InputTextMessageContent::TYPE = "text";
#endif

int main()
{
#if defined(_WIN32) || defined(_WIN64)
    std::system("chcp 65001 > nul");
#endif

    Services::instance().config.reset(new ResponseConfig{ResponseConfig::load(CONFIG_FILE)});
    Services::instance().log.reset(new Logger{LOG_FILE, true});

    Bot bot(TG_BOT_API_KEY);
    bot.run();

    return 0;
}
