#include "scn/step/enemy/pacto/StateDive.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/pacto/Custom.h"
#include "scn/step/enemy/pacto/ParamData.h"
#include "scn/step/enemy/pacto/StateBack.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

StateDive::StateDive(Enemy* enemy) : StateBase(enemy), mFrame(0), mSoundWait(0), mIsBite(false) {
    obj().model().reqScript(7);
    obj().soundSE().start(0x2b2);
}

void StateDive::procMove() {
    const ParamData& param = obj().param().pacto();
    if (!mIsBite) {
        if (obj().model().isAllEnd()) {
            mFrame++;
            if (static_cast<f32>(mFrame) < param.mDiveDist / param.mDiveSpeed) {
                f32 rot = Utility::GetRotByDirType(obj());
                hel::math::Vector2 dir(hel::math::Math::SinDegF(rot), hel::math::Math::CosDegF(rot));
                dir *= param.mDiveDist
                       * hel::math::Math::SinDegF(90.0f * static_cast<f32>(mFrame) / (param.mDiveDist / param.mDiveSpeed));
                dir += hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).initPos();
                obj().location().setPos(dir.toVector3());
            } else {
                mIsBite = true;
                mFrame = 0;
                obj().model().reqScript(8);
                mSoundWait = param.mBiteSoundWait;
                obj().soundSE().start(0x2af);
            }
        }
    } else {
        mFrame++;
        if (mFrame == param.mBiteFrame) {
            obj().model().reqScript(0);
            obj().stateChanger().setNextState<StateBack, Enemy*>(objPtr());
        }
    }
    if (mSoundWait > 0) {
        mSoundWait--;
        if (mSoundWait == 0) {
            obj().soundSE().start(0x2b0);
        }
    }
}

void StateDive::procObjCollReact() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!mIsBite && custom.chkCaptureHero()) {
        mIsBite = true;
        mFrame = 0;
        obj().model().reqScript(8);
        mSoundWait = obj().param().pacto().mBiteSoundWait;
        obj().soundSE().start(0x2af);
    }
}

}}}}  // namespace scn::step::enemy::pacto
