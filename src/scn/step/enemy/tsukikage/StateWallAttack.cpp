#include "scn/step/enemy/tsukikage/StateWallAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

StateWallAttack::StateWallAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    if (obj().dirType() == static_cast<map::BinEnemyDirType>(3)) {
        obj().model().reqScript(13);
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4a5), 0);
        obj().model().rotCtrl().initRotH(90.0f);
    } else {
        obj().model().reqScript(12);
        obj().effect().state().requestN(static_cast<effect::Kind>(0x4a4), 0);
        obj().model().rotCtrl().initRotH(90.0f);
    }
    obj().model().rotCtrl().setValid(false);
}

StateWallAttack::~StateWallAttack() {
    obj().model().rotCtrl().setValid(true);
}

void StateWallAttack::procAnim() {
    const ParamData& param = obj().param().tsukikage();
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isWall()) {
        mFrame++;
        if (mFrame == param.mShurikenFrame) {
            obj().soundSE().start(0x2ee);
            hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).requestShuriken();
        }
        if (obj().model().isAllEnd()) {
            obj().brainCtrl().toValid();
        }
    } else {
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::tsukikage
