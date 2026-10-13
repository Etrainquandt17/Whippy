#include "scn/step/enemy/scarfy/StateFlyUpDown.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/scarfy/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateFlyUpDown::StateFlyUpDown(Enemy* enemy) : StateBase(enemy), mAngle(0.0f), mBaseY(enemy->location().pos().y) {
    obj().footState().setAir();
    obj().model().reqScript(4);
    obj().brainCtrl().toValid();
}

StateFlyUpDown::~StateFlyUpDown() {}

void StateFlyUpDown::procAnim() {
    Utility::TurnHero(obj());
}

void StateFlyUpDown::procMove() {
    const ParamData& param = obj().param().scarfy();
    mAngle += param.mFlyUpDownAngleSpeed;
    if (mAngle >= 360.0f) {
        mAngle -= 360.0f;
    }
    f32 offset = param.mFlyUpDownHeight * hel::math::Math::SinDegF(mAngle);
    hel::math::Vector3 pos = obj().location().pos();
    pos.y = mBaseY + offset;
    obj().location().setPos(pos);
}

void StateFlyUpDown::procFixPos() {
    const ParamData& param = obj().param().scarfy();
    if (obj().mapColl().result().mIsHitRoof) {
        mAngle = 90.0f;
        f32 offset = param.mFlyUpDownHeight * hel::math::Math::SinDegF(mAngle);
        mBaseY = obj().location().pos().y - offset;
    }
    if (obj().mapColl().result().mIsHitFloor) {
        mAngle = 270.0f;
        f32 offset = param.mFlyUpDownHeight * hel::math::Math::SinDegF(mAngle);
        mBaseY = obj().location().pos().y - offset;
    }
}

}
}
}
}
