#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/enemy/cappy/StateAttack.h"

#include "g3d/NodeAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mintglue/VectorInline.h"
#include "ocoll/Owner.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "scn/step/enemy/cappy/ParamData.h"
#include "scn/step/enemy/cappyhat/StateThrow.h"
#include "scn/step/enemy/common/StateWait.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setGround();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
}

void StateAttack::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().cappy();
    mFrame++;
    if (mFrame == param.mAttackStopFrame) {
        obj().model().anim().setFrameRate(0.0f);
    } else if (mFrame == param.mAttackStopFrame + param.mAttackStopLength) {
        obj().model().anim().setFrameRate(1.0f);
    }
    if (obj().model().isAllEnd()) {
        custom.setSearchHat(true);
        custom.setValidTurn(false);
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(objPtr());
        obj().model().model().nodes().at(2).setVisibility(false);
    }
}

void StateAttack::procMove() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const ParamData& param = obj().param().cappy();
    if (mFrame == param.mAttackThrowFrame + param.mAttackStopLength) {
        obj().model().model().nodes().at(3).setVisibility(true);
        hel::math::Vector2 pos = obj().location().pos().getXY();
        pos.y += param.mHatOffsetY * Utility::GetModelScaleBySizeType(obj());
        obj().setPotentialCount(1);
        Desc desc(static_cast<map::BinEnemyKind>(0x65), map::BinEnemyVariation_0, obj().level(), obj().dirType(), obj().size(), false,
                  false, pos);
        util::ObjRefHandle<Enemy> hat = obj().comp().enemyManager().request(desc);
        if (hat.isAlive()) {
            if (obj().objGenerator() != 0) {
                ogen::Generator& generator = *obj().objGenerator();
                hat->setObjGenerator(generator);
            }
            custom.setValidTurn(false);
            custom.setCap(false);
            hat->move().setSpeedV(param.mHatSpeedV);
            hat->stateChanger().setNextState<cappyhat::StateThrow, Enemy*, u64>(hat.operator->(), obj().objColl().owner().uid());
        }
        obj().soundSE().start(0x2A9);
    }
}

void StateAttack::procFixPos() {
    Utility::HitFloorCheck(obj());
}

}
}
}
}
