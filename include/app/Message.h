#ifndef APP_MESSAGE_H
#define APP_MESSAGE_H

namespace app {

class Message {
public:
    static const wchar_t* TextName(const char* label);
    static const wchar_t* TextLvMap(const char* label);
    static const wchar_t* TextWMap(const char* label);
    static const wchar_t* TextStep(const char* label);
    static const wchar_t* TextChallenge(const char* label);
    static const wchar_t* TextPause(const char* label);
    static const wchar_t* TextCommon(const char* label);
    static const wchar_t* TextTitleMenu(const char* label);
    static const wchar_t* TextUnlock(const char* label);
    static const wchar_t* TextSoundRoom(const char* label);
    static const wchar_t* TextArena(const char* label);
    static const wchar_t* TextTheaterRoom(const char* label);
    static const wchar_t* TextOption(const char* label);
    static const wchar_t* TextStaffCredit(const char* label);
    static const wchar_t* TextMovie(const char* label);
    static const wchar_t* TextResident(const char* label);
    static const wchar_t* TextSubgameCommon(const char* label);
    static const wchar_t* TextSubgameSetsuna(const char* label);
    static const wchar_t* TextSubgameGunShoot(const char* label);
    static const wchar_t* UnsafedTextPause(const char* label);
    static const wchar_t* UnsafedTextChallenge(const char* label);
    static const wchar_t* UnsafedTextStaffCredit(const char* label);
};

}

#endif
