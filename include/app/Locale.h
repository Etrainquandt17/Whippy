#ifndef APP_LOCALE_H
#define APP_LOCALE_H

#include "types.h"

namespace app {

class Locale {
public:
    // TODO: both return enumerations that have no header yet. Region 2 with
    // system language 6 selects the files with the postfix "EU_NED".
    static int GetRegion();
    static int GetLanguage();
#ifdef VERSION_SUKK01
    static int GetSystemLanguage();
#endif
    static const char* FilePostfix();
};

}  // namespace app

#endif
