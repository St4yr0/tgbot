//
// Created by Alexey Kolesnik on 17/12/2017.
//

#pragma once

#include <functional>
#include <map>
#include <string>
#include <tgbot/tgbot.h>

void onCommandKeyboard(TgBot::Bot& bot, TgBot::Message::Ptr message);

void onClickButtonOne(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query);

void onClickButtonTwo(TgBot::Bot& bot, TgBot::CallbackQuery::Ptr query);

void onnAnyMessage(TgBot::Bot& bot, TgBot::Message::Ptr message);