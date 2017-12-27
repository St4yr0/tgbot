#pragma once

#include <functional>
#include <map>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <tgbot/tgbot.h>


std::string readToken(const std::string& filename);

void initBot(TgBot::Bot& bot);


// Обязательно, требуется реализовать эту функцию.
std::map<std::string, std::function<void(TgBot::Bot&, TgBot::CallbackQuery::Ptr)>> getAllCallbacks();

// Обязательно, требуется реализовать эту функцию.
std::map<std::string, std::function<void(TgBot::Bot&, TgBot::Message::Ptr)>> getAllCommands();

// Обязательно, требуется реализовать эту функцию.
void onAnyMessage(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onCommandGetLinks(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onCommandSendALink(TgBot::Bot& bot, TgBot::Message::Ptr message);

