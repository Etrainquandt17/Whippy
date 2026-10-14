#include "scn/step/enemy/elec/StateChase.h"

#include "gobj/FootState.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/elec/ParamData.h"
#include "scn/step/enemy/elec/StateAttack.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace elec {

StateChase::StateChase(Enemy* enemy) : StateBase(enemy), mFrame(0), mNearFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(9);
    obj().model().setFrameRate(0.5f);
}

void StateChase::procMove() {
    const ParamData& param = obj().param().elec();
    if (mFrame > param.mChaseWaitFrame) {
        u32 level = obj().level();
        if (level > 2) {
            level = 2;
        }
        Vector3 pos = obj().location().pos();
        Vector3 dir = Utility::GetNearestPlayerPos(obj()).toVector3() - pos;
        f32 length = dir.length();
        if (dir.isZeroLoose(0.00001f)) {
            dir = Vector3::ZERO;
        } else {
            dir.normalize();
        }
        dir *= param.mLevel[level].mChaseSpeed;
        pos += dir;
        if (length < param.mChaseNearDist) {
            mNearFrame++;
            if (mNearFrame >= param.mChaseNearFrame) {
                obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
            }
        } else {
            mNearFrame = 0;
        }
        obj().location().setPos(pos);
    } else {
        mFrame++;
    }
}

}}}}  // namespace scn::step::enemy::elec
