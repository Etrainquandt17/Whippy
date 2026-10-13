#include "scn/step/info/WarpStarPanel.h"

#include "app/Message.h"
#include "lyt/LayoutContext.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/camera/CameraAccessor.h"
#include "scn/step/chara/Location.h"
#include "scn/step/gimmick/Manager.h"
#include "scn/step/gimmick/warpstar/Manager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/info/InfoControl.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "scn/step/info/lvmap/FrameControl.h"
#include "scn/step/info/lvmap/LvMap.h"
#include "scn/step/map/KindUtil.h"
#include "scn/step/ostop/Manager.h"
#include "scn/step/sfx/CinemaScope.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace info {

#define MF_FUNCTION __ct__Q43scn4step4info13WarpStarPanelFRQ23mem10IAllocatorRCQ23lyt12PaneAccessorRQ33scn4step9Component
WarpStarPanel::WarpStarPanel(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Component& component)
    : mComponent(component)
    , mLayout(lyt::LayoutContext("step/lvmap/Main", "WarpStarBase", allocator))
    , _1A0(false)
    , _1A1(false)
    , _1A2(false)
    , _1A3(false) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 size;
    u32 hash;
    u32 rot;
    u32 i;

    asm {
        bl      after1
        opword  MF_WORD(0x7C)
        opword  0x9C1D820B
    after1:
        mflr    r22
        lwz     r26, 0x0(r22)
        stw     r26, expected
    }
    mLayout.setParent(parent);
    asm {
        bl      after2
        opword  0xC729C406
        opword  0x28733592
        opword  MF_WORD(0xA8)
        opword  0x44007881
        opword  0x0DA54603
        opword  MF_WORD(0xB4)
        opword  0x2C0B1C80
        opword  0xC03C4C81
    after2:
        mflr    r26
        lwz     r29, 0x14(r26)
        stw     r29, end
        lwz     r14, 0x8(r26)
        stw     r14, start
    }
    mLayout.pane("WarpStarName").setText(app::Message::TextLvMap("WarpStar"));
    last = end;
    size = last - start;
    hash = 0xB5;
    i = -1;
    last -= 1;
    while (i != size - 1) {
        i += 2;
        rot = hash << 4;
        rot ^= hash >> 28;
        hash = rot ^ *(u16*)(last - i);
    }
    mLayout.rootPane().setVisibility(expected != hash);
    mLayout.updateMatrix();
}
#undef MF_FUNCTION

void WarpStarPanel::updateFrame() {
    if (!_1A2) {
        mComponent.infoManager().gameStatus().warpStarPanel().warpStarInit();
        _1A2 = true;
    }
    if (mComponent.infoManager().gameStatus().isWarpStarMap() && mComponent.infoManager().infoControl().isInfoVisible()) {
        checkWarpStarPanelStart();
        checkVisible();
    }
    checkDisappear();
    mLayout.updateFrame();
}

void WarpStarPanel::warpStarInit() {
    if (mComponent.gimmickManager().warpStarManager().isExist()) {
        mComponent.gimmickManager().warpStarManager().setVisibility(false);
    }
}

void WarpStarPanel::warpStarPosSet() {
    if (mComponent.gimmickManager().warpStarManager().isExist()) {
        hel::math::Matrix34 mtx = mComponent.gimmickManager().warpStarManager().kirbyRideWorldMtx();
        _194 = mtx.getT();
    }
}

void WarpStarPanel::checkWarpStarPanelStart() {
    if (mComponent.gimmickManager().warpStarManager().isExist()
        && !mComponent.gimmickManager().warpStarManager().isVisible()) {
        mComponent.gimmickManager().warpStarManager().setVisibility(true);
        mComponent.gimmickManager().warpStarManager().startAppearAnim();
    }
}

void WarpStarPanel::checkVisible() {
    if (!_1A1 && mComponent.gimmickManager().warpStarManager().isExist()
        && mComponent.gimmickManager().warpStarManager().isVisible()) {
        bool canShow = false;
        if (mComponent.objStopManager().isNotStopped(static_cast<ostop::Flag>(0x20))
            && mComponent.heroManager().canShowWarpStarPanel()) {
            canShow = true;
        }
        bool isNear = false;
        if (isNearWarpStar() && canShow) {
            isNear = true;
        }
        if (_1A0 != isNear) {
            if (isNear) {
                if (_1A3) {
                    mLayout.rootPane().setVisibility(true);
                    _1A3 = false;
                } else {
                    panelAppear();
                }
            } else {
                if (!canShow) {
                    mLayout.rootPane().setVisibility(false);
                    _1A3 = true;
                } else {
                    panelDisappear();
                }
            }
            _1A0 = isNear;
        }
    }
}

void WarpStarPanel::checkDisappear() {
    if (!_1A1 && mComponent.gimmickManager().warpStarManager().isExist()
        && mComponent.gimmickManager().warpStarManager().isVisible()
        && mComponent.gimmickManager().warpStarManager().isDemoStarted()) {
        panelDisappear();
        if (mComponent.infoManager().gameStatus().isInfoIn()) {
            mComponent.infoManager().gameStatus().startAnimOut();
        }
        _1A1 = true;
        mComponent.cinemaScope().start(sfx::CINEMA_SCOPE_KIND_1);
        if (map::KindUtil::IsLevelMap(mComponent.context().mapKind)) {
            mComponent.infoManager().lvMap().frameControl().frameOutStart();
        }
    }
}

bool WarpStarPanel::isNearWarpStar() {
    const f32 range = 4.0f;
    for (u32 i = 0; i < mComponent.heroManager().getPlayerCount(); i++) {
        hel::math::Vector3 pos = mComponent.heroManager().getPlayerByIndex(i).location().pos();
        if (pos.x >= _194.x - range && pos.x <= range + _194.x && pos.y >= _194.y - range && pos.y <= range + _194.y) {
            return true;
        }
    }
    return false;
}

void WarpStarPanel::panelAppear() {
    mLayout.rootPane().setVisibility(true);
    mLayout.play("Start", "Wait");
}

void WarpStarPanel::panelDisappear() {
    mLayout.play("End");
}

void WarpStarPanel::constraintPos() {
    hel::math::Vector2 pos = mComponent.cameraAccessor().toLayoutPos(camera::KIND_0, _194);
    mLayout.rootPane().setTrans(pos.toVector3());
}

}
}
}
