//
// Created by Alexey Kolesnik on 17/12/2017.
//

#include "api.hpp"
#include "keyboard.hpp"

// Файл, для демонстрации работы с клавиатурой

using namespace std;
using namespace TgBot;

bool WAITING_MESSAGE_KEYBOARD = false;


// Функция для демонстрации работы с Inline Keyboard
// https://core.telegram.org/bots/2-0-intro
// Для вызова необходимо прислать сообщение /keyboard
void onCommandKeyboard(Bot& bot, Message::Ptr message)
{
    // Создаем объект клавиатуры
    InlineKeyboardMarkup::Ptr keyboard(new InlineKeyboardMarkup);

    // создаем новую строку в клавиалуре
    // обычный вектор
    vector<InlineKeyboardButton::Ptr> row0;

    // создаем кнопку
    InlineKeyboardButton::Ptr buttonOne(new InlineKeyboardButton);
    // текс кнопки
    buttonOne->text = "Ready to recieve a link";
    // текстовый идентификатор кнопки
    // при нажатии на кнопку будет приходить именно этот текст
    // смотри функцию getAllCallbacks
    buttonOne->callbackData = "id_button_one";

    InlineKeyboardButton::Ptr buttonTwo(new InlineKeyboardButton);
    // чтобы вывести русский текст, надо использовать функцию fromLocale
    buttonTwo->text = "Here's students' pull requests: ";
    buttonTwo->callbackData = "id_button_two";

    // добавляем кнопки на строку
    row0.push_back(buttonOne);
    row0.push_back(buttonTwo);

    // добавляем строку кнопок в клавиатуру
    keyboard->inlineKeyboard.push_back(row0);


//    // создаем еще строку в клавиатуре
//    vector<InlineKeyboardButton::Ptr> row1;
//
//    InlineKeyboardButton::Ptr buttonThree(new InlineKeyboardButton);
//    buttonThree->text = ("Button 3 on the second line");
//    buttonThree->callbackData = "id_button_three";
//
//    row1.push_back(buttonThree);
//    keyboard->inlineKeyboard.push_back(row1);

    // отсылаем сообщение вместе с клавиатурой
//    bot.getApi().sendMessage(message->chat->id, "Keyboard is showed!", false, 0, keyboard, "Markdown");
}

unsigned long numOfWords = 0;
// Функция вызывается каждый раз, когда нажимают на кнопку 1
// (а точнее с callbackData == id_button_one)
void onClickButtonOne(Bot& bot, CallbackQuery::Ptr query) {
    ::WAITING_MESSAGE_KEYBOARD = true;
//    Message::Ptr message;
//    if (StringTools::startsWith(message->text, "https")) {
//        if (message->text.find("github")) {
//            fstream file("PullLink.txt");
//            time_t t = time(nullptr);
//            string link = message->from->username + ' ' + message->text + "Time: " + asctime(localtime(&t));
//            if (link.size() > numOfWords)
//                ::numOfWords = link.size();
//            file << link;
//            file.close();
//        }
//    }
}

// Функция вызывается каждый раз, когда нажимают на кнопку 2 и 3
void onClickButtonTwo(Bot& bot, CallbackQuery::Ptr query) {
    Message::Ptr message;
    onCommandGetLinks(bot, message);
//    Message::Ptr message;
//    bot.getApi().sendMessage(message->chat->id, "Here's the links with the time of delivery: ");
//    fstream file("PullLink.txt");
//    while(!file.eof()) {
//        std::string buf;
//        buf.reserve(::numOfWords);
//        file.getline(&buf[0], '\n');
//
//        if (!buf.empty())
//            bot.getApi().sendMessage(message->chat->id, buf);
//    }
//    file.close();
}

void onnAnyMessage(Bot& bot, Message::Ptr message) {
    if (::WAITING_MESSAGE_KEYBOARD) {
        fstream file("PullLink.txt", ostream::app);
        time_t t = time(nullptr);
        string link = message->from->username + ' ' + message->text + "Time: " + asctime(localtime(&t));
        if (link.size() > numOfWords)
            ::numOfWords = link.size();
        file << link;
        file.close();
        ::WAITING_MESSAGE_KEYBOARD = false;
    }

}
// Регистрируем наши кнопки
std::map<std::string, std::function<void(Bot&, CallbackQuery::Ptr)>> getAllCallbacks()
{
    // Ключом является идентификатор кнопки
    // значением является функция-обработчик кнопки
    // т.е. при нажатии на кнопку с идентификатором, произойдет вызов соответствующей функции
    // Например, при нажании на кнопку с идентификатором id_button_one вызовется функция onClickButtonOne
    std::map<std::string, std::function<void(Bot&, CallbackQuery::Ptr)>> callbacks =
            {
                    {"id_button_one", onClickButtonOne},
                    {"id_button_two", onClickButtonTwo},
            };

    return callbacks;
}

