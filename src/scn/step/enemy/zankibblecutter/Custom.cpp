#include "scn/step/enemy/zankibblecutter/Custom.h"

#include "scn/step/Component.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/core/PermSoundSE.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/CaptureReceiver.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Nururi.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/ocoll/AttackType.h"
#include "scn/step/ocoll/Flag.h"
#include "snd/SERequestor.h"

using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;

namespace scn {
namespace step {
namespace enemy {
namespace zankibblecutter {

Custom::Custom(Enemy& enemy) : CustomBase(enemy) {}

bool Custom::onInit() {
    obj().captureReceiver().setCanCapture(false);
    obj().nururi().setValid(false);
    obj().objColl().bodyColl().setFlagXlu(static_cast<ocoll::Flag>(1));
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1b6));
    obj().effect().normal().requestN(static_cast<effect::Kind>(0xd5), 1);
    if (Utility::IsExtra(obj())) {
        obj().soundSE().start(0x58c);
    } else {
        obj().soundSE().start(0x594);
    }
    return false;
}

bool Custom::reqCustomDeadEffect() {
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0xd6), obj().location().pos());
    obj().comp().permSoundSE().start(0x596);
    return true;
}

bool Custom::onVacuumReceive() {
    obj().effect().normal().releaseAndVanish();
    return false;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::zankibblecutter
