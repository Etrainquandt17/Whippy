#ifndef SCN_STEP_BOSS_ARENACTRL_H
#define SCN_STEP_BOSS_ARENACTRL_H

#include "scn/step/arena/Manager.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace boss {

class ArenaCtrl {
public:
    ArenaCtrl(Component& component);

    void setNextScene(bool isFade);
    void setNextSceneWithAdditionalDelay(u32 delay);
    void update();
    void stopTime();
    void startTime();

private:
    Component& mComponent;
    bool mIsNextScene;
    bool mIsFade;
    u32 mDelay;
    arena::EntryManager::EntryId mEntryId;
};

}
}
}

#endif
