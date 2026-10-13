#include "scn/step/enemy/scarfy/StateFaceChange.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/MeshFlip.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/ParamData.h"
#include "scn/step/enemy/scarfy/StateAngerChase.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

StateFaceChange::StateFaceChange(Enemy* enemy) : StateBase(enemy), mIsEnd(false), mIsFlipped(false), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
}

StateFaceChange::~StateFaceChange() {}

void StateFaceChange::procAnim() {
    if (static_cast<u32>(obj().model().anim().currentG3DAnimIndex()) == 3 &&
        obj().model().anim().frame() >= obj().param().scarfy().mFaceChangeFlipFrame && !mIsFlipped) {
        obj().model().meshFlip().flip(1);
        obj().objColl().bodyColl().setAttackTypeOver(static_cast<ocoll::AttackType>(0x19e));
        hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).onAngerFlag();
        mIsFlipped = true;
    }
    if (obj().model().isAllEnd()) {
        mIsEnd = true;
        obj().move().setSpeedV(obj().param().scarfy().mFaceChangeSpeedV);
        obj().model().reqScript(9);
        obj().model().meshFlip().flip(1);
    }
}

void StateFaceChange::procMove() {
    if (mIsEnd == true) {
        mFrame++;
        if (mFrame >= obj().param().scarfy().mFaceChangeAccelFrame) {
            obj().move().airAccelFall(!obj().target().isRightDir(), obj().param().scarfy().mFaceChangeAccel,
                                      obj().param().scarfy().mFaceChangeFall);
            if (mFrame == obj().param().scarfy().mFaceChangeEndFrame) {
                obj().stateChanger().setNextState<StateAngerChase, Enemy*>(objPtr());
            }
        }
    }
}

}}}}  // namespace scn::step::enemy::scarfy
