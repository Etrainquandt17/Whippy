#include "scn/step/weapon/CameraTarget.h"

#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/weapon/Weapon.h"

namespace scn {
namespace step {
namespace weapon {

CameraTarget::CameraTarget(Weapon& weapon) : mObj(weapon), mIsValid(false), mOffset() {}

void CameraTarget::updateAndRegist() {
    if (mIsValid) {
        hel::math::Vector2 pos = mObj.location().pos().getXY();
        pos += mOffset;
        mObj.comp().cameraController().addCameraTarget(pos);
    }
}

void CameraTarget::setValid(bool isValid) {
    mIsValid = isValid;
}

void CameraTarget::setOffset(const hel::math::Vector2& offset) {
    mOffset = offset;
}

}
}
}
