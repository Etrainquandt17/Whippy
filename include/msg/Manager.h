#ifndef MSG_MANAGER_H
#define MSG_MANAGER_H

namespace msg {

// TODO: members and the other functions.
class Manager {
public:
    // Named after the app::Message functions that use them; two have none.
    enum Category {
        CATEGORY_NAME,
        CATEGORY_LV_MAP,
        CATEGORY_2,
        CATEGORY_W_MAP,
        CATEGORY_STEP,
        CATEGORY_CHALLENGE,
        CATEGORY_PAUSE,
        CATEGORY_COMMON,
        CATEGORY_TITLE_MENU,
        CATEGORY_UNLOCK,
        CATEGORY_SOUND_ROOM,
        CATEGORY_THEATER_ROOM,
        CATEGORY_OPTION,
        CATEGORY_STAFF_CREDIT,
        CATEGORY_MOVIE,
        CATEGORY_RESIDENT,
        CATEGORY_ARENA,
        CATEGORY_SUBGAME_COMMON,
        CATEGORY_12,
        CATEGORY_SUBGAME_SETSUNA,
        CATEGORY_SUBGAME_GUN_SHOOT,
    };

    const wchar_t* text(Category category, const char* label);
    const wchar_t* unsafedText(Category category, const char* label);
};

}

#endif
