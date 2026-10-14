#include "scn/step/enemy/wapod/Custom.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/core/PermEffect.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/wapodpod/Custom.h"
#include "snd/SERequestor.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mWapodpodUid(0), mWapodpodVariation(0), mIsVacuum(false), mInitPosY(obj().location().pos().y),
      mTurnFrame(0) {}

bool Custom::onInit() {
    f32 scale = Utility::GetModelScaleBySizeType(obj());
    obj().objColl().clearBodyColl();
    obj().objColl().addBodyColl(0, 0.5f * scale, Vector2(0.0f, 0.7f * scale));
    obj().mapColl().changeActorShape(mcoll::detail::ShapeDiamondContext::CreateBaseBottom(0.35f, 0.49f, 0.5f));
    return false;
}

bool Custom::onVacuumReceive() {
    mIsVacuum = true;
    return false;
}

bool Custom::onDamaged() {
    if (!mIsVacuum) {
        obj().effect().normal().requestN(static_cast<effect::Kind>(0x556), 1);
    }
    return false;
}

void Custom::onDead() {
    ObjRefHandle<Enemy> pod = obj().comp().enemyManager().getEnemyByOCollOwnerUID(mWapodpodUid);
    if (pod.isAlive()) {
        pod->setPotentialCount(2);
        DynamicCastToRef<wapodpod::Custom, ICustom>(pod->custom()).setIsExist(false);
    }
}

void Custom::setWapodpodUid(u64 uid) {
    mWapodpodUid = uid;
    ObjRefHandle<Enemy> pod = obj().comp().enemyManager().getEnemyByOCollOwnerUID(mWapodpodUid);
    if (pod.isAlive()) {
        DynamicCastToRef<wapodpod::Custom, ICustom>(pod->custom()).setIsExist(true);
        mWapodpodVariation = pod->variation();
    }
}

u32 Custom::wapodpodVariation() const {
    return mWapodpodVariation;
}

f32 Custom::initPosY() const {
    return mInitPosY;
}

void Custom::turn() {
    if (Utility::IsPlayerExist(obj())) {
        f32 playerX = Utility::GetNearestPlayerPos(obj()).x;
        bool isRight = playerX > obj().location().pos().x;
        if (isRight != obj().target().isRightDir()) {
            if (++mTurnFrame == 30) {
                obj().target().setIsRightDir(isRight);
            }
        } else {
            mTurnFrame = 0;
        }
    }
}

void Custom::landHitDead() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.isHit()) {
        obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x556),
                                                    obj().location().pos() + Vector3(0.0f, 0.5f, 0.0f));
        obj().dead();
    }
}

void Custom::fixPosInValid() {
    ObjRefHandle<Enemy> pod = obj().comp().enemyManager().getEnemyByOCollOwnerUID(mWapodpodUid);
    if (pod.isAlive()) {
        DynamicCastToRef<wapodpod::Custom, ICustom>(pod->custom()).setIsFixPos(false);
    }
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::wapod
