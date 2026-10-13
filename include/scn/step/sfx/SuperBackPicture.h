#ifndef SCN_STEP_SFX_SUPERBACKPICTURE_H
#define SCN_STEP_SFX_SUPERBACKPICTURE_H

#include "scn/step/effect/Kind.h"

namespace hel {
namespace math {
class Direction3;
}
}

namespace scn {
namespace step {

class Component;

namespace sfx {

// TODO: members unknown; only what scn/step/sfx/MintSuperBackPicture.cpp calls is declared.
class SuperBackPicture {
public:
    SuperBackPicture(Component& component);
    ~SuperBackPicture();

    void update();
    void setIsRightDir(bool isRightDir);
    void requestEffect(effect::Kind kind);
    void requestEffect(effect::Kind kind, const hel::math::Direction3& dir);
    void releaseEffect();
    void requestEffect2(effect::Kind kind);
    void requestEffect2(effect::Kind kind, const hel::math::Direction3& dir);
    void releaseEffect2();
    void requestEffectNonStop(effect::Kind kind);
    void requestEffectNonStop(effect::Kind kind, const hel::math::Direction3& dir);
    void releaseEffectNonStop();
    void requestEffectNonStop2(effect::Kind kind);
    void requestEffectNonStop2(effect::Kind kind, const hel::math::Direction3& dir);
    void releaseEffectNonStop2();
};

}
}
}

#endif
