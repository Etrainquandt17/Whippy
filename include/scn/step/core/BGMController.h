#ifndef SCN_STEP_CORE_BGMCONTROLLER_H
#define SCN_STEP_CORE_BGMCONTROLLER_H

#include "types.h"

namespace scn {
namespace step {
namespace core {

// TODO: name the categories.
enum BGMCategory {
    BGM_CATEGORY_0,
};

class BGMController {
public:
    BGMController();
    ~BGMController();

    void setIsPlayEnable(bool isPlayEnable);
    void request(BGMCategory category, u32 id, bool flag);
    void unrequest(BGMCategory category);
    void pause(BGMCategory category);
    void pause(BGMCategory category, u32 frame);
    void unpause(BGMCategory category);
    void unpause(BGMCategory category, u32);

private:
    u32 _0[0x1A];
};

}
}
}

#endif
