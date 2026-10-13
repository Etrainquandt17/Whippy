#ifndef SCN_STEP_WEAPON_CAMERATARGET_H
#define SCN_STEP_WEAPON_CAMERATARGET_H

#include "hel/math/Vector2.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

class CameraTarget {
public:
    CameraTarget(Weapon& weapon);

    void updateAndRegist();
    void setValid(bool isValid);
    void setOffset(const hel::math::Vector2& offset);

private:
    Weapon& mObj;
    bool mIsValid;
    hel::math::Vector2 mOffset;
};

}
}
}

#endif
