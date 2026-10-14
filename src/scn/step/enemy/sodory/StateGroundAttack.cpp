#include "scn/step/enemy/sodory/StateGroundAttack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/common/ParamData.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "snd/SERequestor.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

StateGroundAttack::StateGroundAttack(Enemy* enemy) : StateBase(enemy), mIsRightDir(obj().target().isRightDir()) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(8);
    Utility::TurnHero(obj());
    custom.setDirection();
    custom.setFrame();
}

StateGroundAttack::~StateGroundAttack() {
    obj().target().setIsRightDir(mIsRightDir);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setDirection();
    obj().objColl().clearAttack();
    obj().soundSE().stop();
    obj().effect().state().releaseAndVanish();
}

void StateGroundAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateGroundAttack::procMove() {
    obj().move().groundDecel(obj().param().common().mDecel);
}

}}}}  // namespace scn::step::enemy::sodory
