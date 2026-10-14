#include "scn/step/enemy/waddledee/StateWhispyAppear.h"

#include "gobj/FootState.h"
#include "hel/math/Math.h"
#include "mintglue/VectorInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/waddledee/ParamData.h"
#include "scn/step/enemy/waddledee/StateWhispyFall.h"

using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

StateWhispyAppear::StateWhispyAppear(Enemy* enemy) : StateBase(enemy), mFrame(0), mBaseY(obj().location().pos().y) {
    obj().footState().setAir();
    obj().objColl().setBodyCollStateHitOnly();
    obj().model().reqScript(14);
}

StateWhispyAppear::~StateWhispyAppear() {
    obj().objColl().bodyColl().setStateNormal();
}

void StateWhispyAppear::procAnim() {
    mFrame++;
    const ParamData& param = obj().param().waddledee();
    if (mFrame == param.mWhispyAppearFrame) {
        obj().stateChanger().setNextState<StateWhispyFall, Enemy*>(objPtr());
    }
}

void StateWhispyAppear::procMove() {
    const ParamData& param = obj().param().waddledee();
    f32 rate = static_cast<f32>(mFrame) / static_cast<f32>(param.mWhispyAppearFrame);
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    Vector3 pos = obj().location().pos();
    pos.y = mBaseY - param.mWhispyAppearHeight * Math::SinDegF(90.0f * rate);
    obj().location().setPos(pos);
}

void StateWhispyAppear::procFixPos() {}

}}}}  // namespace scn::step::enemy::waddledee
