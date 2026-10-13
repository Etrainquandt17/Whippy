#include "scn/step/boss/common/StateAppear.h"

#include "gobj/Target.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/VacuumReceiver.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/carryitem/Manager.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Manager.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateAppear::StateAppear(Boss* boss) : StateBase(boss), mZoomID(0), mCount(0) {
    obj().model().setVisibility(false);
    obj().objColl().bodyColl().setStateXlu();
    hel::math::Vector3 pos = obj().location().pos();
    hel::math::Vector3 heroPos = obj().comp().heroManager().getMainPlayerPos();
    if (!Utility::IsVariationBossRush(obj())) {
        f32 sign = pos.x - heroPos.x < 0.0f ? -1 : 1;
        hel::math::Vector2 offs = obj().custom()->getFirstOffs();
        offs.x *= sign;
        pos += offs.toVector3();
        obj().location().setPos(pos);
        obj().mapColl().reset();
    }
    obj().target().setIsRightDir(heroPos.x > pos.x);
}

StateAppear::~StateAppear() {
    if (mZoomID != 0) {
        obj().comp().cameraController().unsetZoom(mZoomID);
    }
    obj().model().setVisibility(true);
    obj().model().resetScale();
    obj().objColl().bodyColl().setStateNormal();
    obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_2);
}

void StateAppear::procAnim() {
    if (obj().isGeneratorExist()) {
        obj().vacuumReceiver().setIsValid(true);
        obj().vacuumReceiver().setIsResist(true);
        obj().custom()->onStart();
        return;
    }
    if (mCount < 160) {
        mCount++;
        if (mCount == 1) {
            if (canZoom()) {
                mZoomID = obj().comp().cameraController().setZoom(obj().location().pos().getXY(), 7.5f);
            }
            hel::math::Vector3 pos = obj().location().pos();
            pos.y += 1.25f;
            obj().effect().fore().requestP(static_cast<effect::Kind>(0x122), pos);
            obj().soundSE().normal().start(0x5AF);
        }
        switch (mCount) {
        case 10:
        case 30:
        case 50:
        case 60:
        case 70:
        case 78:
        case 84:
        case 90:
        case 95:
        case 100:
        case 105:
        case 110:
        case 114:
        case 118:
        case 122:
        case 126:
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
            break;
        }
        if (mCount == 130) {
            obj().model().setVisibility(true);
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(5));
            obj().soundSE().normal().start(0x5AE);
            obj().model().reqScript(1);
            obj().custom()->onAppear();
        }
        if (mCount == 160) {
            obj().objColl().bodyColl().setStateNormal();
            obj().objColl().bodyColl().setResistLv(ocoll::HIT_RESIST_LV_6);
            obj().invincible().setPermNoFlash();
            obj().guard().setType(GUARD_TYPE_6);
        }
    } else if (obj().model().isAllEnd()) {
        obj().vacuumReceiver().setIsValid(true);
        obj().vacuumReceiver().setIsResist(true);
        obj().custom()->onStart();
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

bool StateAppear::canZoom() {
    if (obj().comp().bossManager().getBossCount() >= 2) {
        return false;
    }
    if (Utility::IsArena(obj())) {
        return true;
    }
    if (obj().comp().heroManager().getPlayerCount() >= 2u) {
        return false;
    }
    u32 count;
    {
        hel::geo::Rect rect = obj().comp().cameraController().getLockRectTarget();
        rect.margeUnion(obj().comp().mainCamera().getViewRect());
        count = obj().comp().carryItemManager().countExistObjInRect(rect);
    }
    u32 zoomCount;
    {
        hel::geo::Rect rect = obj().comp().cameraController().getZoomTargetRect(obj().location().pos().getXY(), 7.5f);
        zoomCount = obj().comp().carryItemManager().countExistObjInRect(rect);
    }
    return count == zoomCount;
}

}
}
}
}
