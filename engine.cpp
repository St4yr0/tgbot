//
// Created by Alexey Kolesnik on 15/12/2017.
//

#include "api.hpp"
#include "keyboard.hpp"

using namespace std;
using namespace TgBot;

bool WAITING_MESSAGE = false;
unsigned long numOfWords1 = 0;


void onCommandStart(Bot& bot, Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Hi! "
            "You are to send a link to your pull request. "
            "The time you send it would be saved!");
}

void onCommandEnd(Bot& bot, Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Bye");
}


void onCommandSendALink(Bot& bot, Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "I'm ready to get your link");
    ::WAITING_MESSAGE = true;
}


void onAnyMessage(Bot& bot, Message::Ptr message) {

    printf("User wrote %s\n", message->text.c_str());

    if (StringTools::startsWith(message->text, "/start")) {
        return;
    }

    if (StringTools::startsWith(message->text, "/end")) {
        return;
    }

    if (StringTools::startsWith(message->text, "/sendALink")) {
        return;
    }

    if (::WAITING_MESSAGE) {
        fstream file("PullLink.txt", ostream::app);
        time_t t = time(nullptr);
        string link = message->from->username + ' ' + message->text + "Time: " + asctime(localtime(&t));
        if (link.size() > numOfWords1)
            ::numOfWords1 = link.size();
        file << link;
        file.close();
        WAITING_MESSAGE = false;
    }

    if (StringTools::startsWith(message->text, "/getLinks")) {
        return;
    }
}

void onCommandGetLinks(Bot& bot, Message::Ptr message) {
    bot.getApi().sendMessage(message->chat->id, "Here's the links with the time of delivery: ");
    fstream file("PullLink.txt");
    while(!file.eof()) {
        std::string buf;
        buf.reserve(::numOfWords1);
        file.getline(&buf[0], '\n');

        if (!buf.empty())
            bot.getApi().sendMessage(message->chat->id, buf);
    }
    file.close();
}

map<string, function<void(Bot&, Message::Ptr)>> getAllCommands() {
    std::map<std::string, std::function<void(Bot&, Message::Ptr)>> commands = {
            {"start", onCommandStart},
            {"end", onCommandEnd},
            {"sendALink", onCommandSendALink},
            {"getLinks", onCommandGetLinks},
            {"keyboard", onCommandKeyboard}
    };

    return commands;
};
