#include "scn/step/boss/goliath/StateDeadEnd.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateDeadGroundChange.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shadow.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateDeadEnd::StateDeadEnd(Boss* boss) : StateBase(boss), mFrame(60) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
    obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(9));
    Vector3 pos = obj().location().pos();
    pos.y = custom.landCtrl().getFloorY() - 3.0f;
    obj().effect().state().requestP(static_cast<effect::Kind>(0x72), pos);
    obj().soundSE().normal().start(0x30E);
    obj().model().setVisibility(false);
    obj().shadow().setVisibility(false);
}

StateDeadEnd::~StateDeadEnd() {}

void StateDeadEnd::procAnim() {
    if (mFrame != 0) {
        mFrame--;
        if (mFrame == 0) {
            if (Utility::IsArena(obj())) {
                obj().comp().bossManager().arenaCtrl().setNextScene(true);
            } else {
                obj().stateChanger().setNextState<StateDeadGroundChange, Boss*>(objPtr());
            }
        }
    }
}

void StateDeadEnd::procMove() {}

void StateDeadEnd::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
