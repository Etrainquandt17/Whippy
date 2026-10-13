#ifndef APP_SAVEINFO_H
#define APP_SAVEINFO_H

#include "types.h"

namespace app {

// TODO: name the values.
enum SaveInfoLayoutKind {
    SAVE_INFO_LAYOUT_KIND_0,
    SAVE_INFO_LAYOUT_KIND_1,
};

class SaveInfo {
public:
    void start(SaveInfoLayoutKind kind);
    bool isDisplayNow() const;
};

}

#endif
