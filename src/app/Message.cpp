#include "app/Message.h"

#include "app/Application.h"
#include "msg/Manager.h"

namespace app {

const wchar_t* Message::TextName(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_NAME, label);
}

const wchar_t* Message::TextLvMap(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_LV_MAP, label);
}

const wchar_t* Message::TextWMap(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_W_MAP, label);
}

const wchar_t* Message::TextStep(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_STEP, label);
}

const wchar_t* Message::TextChallenge(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_CHALLENGE, label);
}

const wchar_t* Message::TextPause(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_PAUSE, label);
}

const wchar_t* Message::TextCommon(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_COMMON, label);
}

const wchar_t* Message::TextTitleMenu(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_TITLE_MENU, label);
}

const wchar_t* Message::TextUnlock(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_UNLOCK, label);
}

const wchar_t* Message::TextSoundRoom(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_SOUND_ROOM, label);
}

const wchar_t* Message::TextTheaterRoom(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_THEATER_ROOM, label);
}

const wchar_t* Message::TextOption(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_OPTION, label);
}

const wchar_t* Message::TextStaffCredit(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_STAFF_CREDIT, label);
}

const wchar_t* Message::TextMovie(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_MOVIE, label);
}

const wchar_t* Message::TextResident(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_RESIDENT, label);
}

const wchar_t* Message::TextArena(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_ARENA, label);
}

const wchar_t* Message::TextSubgameCommon(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_SUBGAME_COMMON, label);
}

const wchar_t* Message::TextSubgameSetsuna(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_SUBGAME_SETSUNA, label);
}

const wchar_t* Message::TextSubgameGunShoot(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().text(msg::Manager::CATEGORY_SUBGAME_GUN_SHOOT, label);
}

const wchar_t* Message::UnsafedTextPause(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().unsafedText(msg::Manager::CATEGORY_PAUSE, label);
}

const wchar_t* Message::UnsafedTextChallenge(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().unsafedText(msg::Manager::CATEGORY_CHALLENGE, label);
}

const wchar_t* Message::UnsafedTextStaffCredit(const char* label) {
    return hel::common::ExplicitSingleton<Application>::object_->messageManager().unsafedText(msg::Manager::CATEGORY_STAFF_CREDIT, label);
}

}
