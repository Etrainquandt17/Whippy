#include "scn/step/enemy/lupa/CliffChecker.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/lupa/ParamData.h"
#include "scn/step/map/LandManager.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

CliffChecker::CliffChecker(Enemy& enemy) : mObj(enemy), mIsCliff(false), mDirV(1.0f), mAccelDir(1.0f) {}

CliffChecker::~CliffChecker() {}

void CliffChecker::changeDirType(bool isUp) {
    mDirV = isUp ? 1.0f : -1.0f;
}

void CliffChecker::setAccelDirRight(bool isRight) {
    mAccelDir = isRight ? 1.0f : -1.0f;
}

void CliffChecker::update() {
    const ParamData& param = mObj.param().lupa();
    mIsCliff = false;
    hel::math::Vector2 pos = mObj.location().pos().getXY();
    if (mDirV < 0.0f) {
        pos.y += param.mShapeTop;
    }
    pos.y += 0.05f * mDirV;
    hel::math::Vector2 check = pos + hel::math::Vector2(0.0f, -0.5f * mDirV);
    if (mObj.comp().mapLandManager().native().isExistLand(check) || mObj.comp().mapLandManager().native().isExistMoveLand(check)) {
        pos.x += 0.5f * mAccelDir;
        if (pos.x < 0.0f || mObj.comp().mapLandManager().native().gridWidth() < pos.x) {
            return;
        }
        if (mObj.comp().mapLandManager().native().isExistLand(pos) || mObj.comp().mapLandManager().native().isExistMoveLand(pos)) {
            return;
        }
        pos.y -= 0.5f * mDirV;
        if (mObj.comp().mapLandManager().native().isExistLand(pos) || mObj.comp().mapLandManager().native().isExistMoveLand(pos)) {
            return;
        }
        mIsCliff = true;
    }
}

bool CliffChecker::isCliff() const {
    return mIsCliff;
}

}
}
}
}
