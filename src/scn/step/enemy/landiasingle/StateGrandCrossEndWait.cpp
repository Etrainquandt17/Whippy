#include "scn/step/enemy/landiasingle/StateGrandCrossEndWait.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/landiasingle/Custom.h"
#include "scn/step/enemy/landiasingle/ParamData.h"
#include "scn/step/enemy/landiasingle/StateWait.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

StateGrandCrossEndWait::StateGrandCrossEndWait(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(7);
    obj().move().resetVelocity();
    custom.setFlagActionEnd();
    obj().model().rotCtrl().setValid(false);
}

StateGrandCrossEndWait::~StateGrandCrossEndWait() {
    obj().model().unsetCustomMtx();
    obj().model().rotCtrl().setValid(true);
}

void StateGrandCrossEndWait::procAnim() {
    const ParamData& param = obj().param().landiasingle();
    if (mFrame < param._140) {
        mFrame++;
        f32 t = static_cast<f32>(mFrame) / static_cast<f32>(param._140);
        f32 rate = 1.5f * t + t * (-0.5f * t * t);
        setCustomMtx(rate);
    } else {
        obj().stateChanger().setNextState<StateWait, Enemy*, bool>(objPtr(), true);
    }
}

void StateGrandCrossEndWait::procMove() {}

void StateGrandCrossEndWait::procFixPos() {}

// TODO: the original loads the y of each offset ahead of the vector's address and the two zeros (three lines each).
void StateGrandCrossEndWait::setCustomMtx(f32 rate) {
    Direction3 dir;
    dir.mFront = Vector3::BASIS_Z;
    dir.mFront.rotate(Vector3::AXIS_X, 0.017453292f * (-360.0f * rate));
    dir.mLeft = Vector3::BASIS_X;
    dir.restructFrontLeft();
    Matrix34 toCenter = Matrix34::CreateTrans(Vector3(0.0f, obj().location().toCenter().y, 0.0f));
    Matrix34 fromCenter = Matrix34::CreateTrans(Vector3(0.0f, -obj().location().toCenter().y, 0.0f));
    Matrix34 rot(dir, Vector3::ZERO);
    obj().model().setCustomMtx(toCenter * rot * fromCenter);
}

}}}}  // namespace scn::step::enemy::landiasingle
