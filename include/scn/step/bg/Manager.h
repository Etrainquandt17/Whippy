#ifndef SCN_STEP_BG_MANAGER_H
#define SCN_STEP_BG_MANAGER_H

#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace scn {
namespace step {
namespace bg {

class DecorationManager;

// TODO: members unknown; only what scn/step/gimmick/popflower/PopFlower.cpp calls is declared.
class Manager {
public:
    // TODO: an enumeration of the decoration sets.
    int maproDecorationKind() const;
    void setIsVisible(bool isVisible);
    // TODO: the return type is taken from the call that follows it in boss/mahoroabattle2/SuperEffectCtrl.
    DecorationManager& impl();
    void maproSetOffset(u32 groupNo, const hel::math::Vector2& offset);
};

}
}
}

#endif
