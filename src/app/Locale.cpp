#include "app/Locale.h"

#include "revolution/sc.h"

namespace app {

namespace {

#ifdef VERSION_SUKK01
const char* const T_POSTS_KR[] = {
    "KR_JPN",
    "KR_ENG",
    "KR_GER",
    "KR_FRA",
    "KR_SPA",
    "KR_ITA",
    "KR_NED",
    "KR_KOR",
};
#else
const char* const T_POSTS_US[] = {
    "US_JPN",
    "US_ENG",
    "US_GER",
    "US_FRA",
    "US_SPA",
    "US_ITA",
};
#endif

}

#ifdef VERSION_SUKK01
int Locale::GetRegion() {
    return 3;
}

int Locale::GetLanguage() {
    int language = GetSystemLanguage();
    if (language == 6) {
        language = 1;
    }
    return language;
}

int Locale::GetSystemLanguage() {
    switch (SCGetLanguage()) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 6;
    case 9:
        return 7;
    default:
        return 0;
    }
}

const char* Locale::FilePostfix() {
    return T_POSTS_KR[GetLanguage()];
}
#else
int Locale::GetRegion() {
    return 1;
}

int Locale::GetLanguage() {
    switch (SCGetLanguage()) {
    case 1:
        return 1;
    case 2:
        return 2;
    case 3:
        return 3;
    case 4:
        return 4;
    case 5:
        return 5;
    case 6:
        return 1;
    default:
        return 0;
    }
}

const char* Locale::FilePostfix() {
    return T_POSTS_US[GetLanguage()];
}
#endif

}  // namespace app
