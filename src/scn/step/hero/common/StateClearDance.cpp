#include "scn/step/hero/common/StateClearDance.h"
#include "gobj/Move.h"
#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/SceneChanger.h"
#include "scn/step/hero/Flash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/InitiativeUtil.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "scn/step/sfx/Wipe.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateClearDance::StateClearDance(Hero* hero)
    : StateBase(hero)
    , mIsAnimEnd(false)
    , mFrame(0) {
    obj().stateChecker().setDemo(true);
    obj().model().script().start(0x28);
    obj().objColl().setXlu();
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().move().resetVelocity();
    obj().flash().setValid(false);
    if (IndiviUtil::IsKirby(obj().kind())) {
        obj().wearBack().setBack();
    }
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().mapColl().setValid(false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().setCanCatchItem(false);
    obj().setCanReactGimmick(false);
    if (obj().comp().infoManager().gameStatus().isInfoIn()) {
        obj().comp().infoManager().gameStatus().startAnimOut();
    }
    InitiativeUtil::TryTake(obj());
}

StateClearDance::~StateClearDance() {}

void StateClearDance::procAnim() {
    if (!mIsAnimEnd && obj().model().isAllEnd()) {
        mIsAnimEnd = true;
    }
    if (mIsAnimEnd == true) {
        mFrame++;
        if (InitiativeUtil::IsMine(obj())) {
            if (mFrame == 40) {
                hel::math::Vector2 center = obj().comp().mainCamera().getWorldRect().getCenter();
                center.y = 0.75f + obj().location().pos().y;
                obj().comp().wipe().requestWipeOut(static_cast<sfx::WipeKind>(1), center.toVector3(), 0, 100);
            }
            if (mFrame == 145) {
                obj().comp().sceneChanger().changeBossClear();
            }
        }
    }
}

void StateClearDance::procMove() {}

void StateClearDance::procFixPos() {}

}}}}  // namespace scn::step::hero::common
