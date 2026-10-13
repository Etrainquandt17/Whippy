#ifndef SCN_STEP_GIMMICK_LVMAPDOOR_LVMAPDOOR_H
#define SCN_STEP_GIMMICK_LVMAPDOOR_LVMAPDOOR_H

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mint/Runner.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/Model.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/Stop.h"
#include "scn/step/info/lvmap/StageSphere.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace lvmapdoor {

class Manager;

struct Param {
    u32 _0;
    u32 _4;
    u8 _8[0x8];
    f32 _10;
};

class LvMapDoor {
public:
    void procAnim();
    void cameraOutCheck();
    void returnDemoDoorInit();
    void unlockDemoDoorInit();
    void clearedDoorInit();
    void updateDoorInOut();
    void setDoorCloseAnim();
    void setDoorNearAnim();
    void setDoorWaitAnim();
    void setBossNormalWaitAnim();
    bool isFirstDoorDemo();
    void reqUnlockEffect1();
    void reqUnlockEndEffect1();
    void reqBossInvalidWaitEffect();
    void setZoom(f32, f32);
    void stageSphereControl();
    static hel::math::Vector3 GetModelPos(hel::math::Vector2 pos);

    void unlockAnim();
    void reqUnlockEffect1_WoodBreak();
    void reqUnlockEffect2();
    void reqUnlockEffect3_GrowSmoke();
    void reqUnlockEffect3_MagmaHit(u32);
    void reqUnlockEffect3_Aurora();
    void reqUnlockEffect3_Magma();
    void stopUnlockEffect2();
    void stopUnlockEffect3();
    void reqCommonEffect();
    void onVisibleStageBoard();
    void infoAnimIn();
    u32 setZoom(f32, f32, f32, f32);
    void setDistance(f32);
    void setTargetDistance(f32);
    void setTargetFrame(int);
    void setCameraTargetDoor();
    void unsetCameraTargetDoor();
    void reqQuake(camera::QuakeKind kind);
    void unsetZoom(u32);
    void setCamRotDegX(f32, f32);
    void unsetCamRotDegX(u32);
    void setRotRateBGX(f32);
    bool isInDoor();
    void flagStart();
    bool isBossUnlock();
    int getLevel();

    Component& comp();
    Manager& manager();
    snd::SERequestor& soundSE() { return _1968; }
    bool isDoorAnimEnd() const { return _1913; }

    void reqOpenEffect1();
    void setForbidShowLvMapDoorInfo(bool forbid);
    info::lvmap::StageSphere& stageSphere();
    void hideDoorInfoForce();

private:
    void mfSetupCommonEffect();
    void mfUpdateSoundSE();

    // TODO: 0x54C is a pointer followed by the Model it points to, some wrapper
    // like util::PlacementNew whose validity test is an inline function.
    bool has54C() const { return _54C != 0; }

    ParamAccessor<Param> mParam;
    Component& mComponent;
    Manager& mManager;
    hel::math::Vector2 _10;
    int _18;
    u32 _1C;
    int _20;
    bool _24;
    util::FrameCounter _28;
    Model _30;
    Model _1E4;
    Model _398;
    Model* _54C;
    u8 _550[0xAA0 - 0x550];
    Effect _AA0;
    Effect _E3C;
    Effect _11D8;
    Effect _1574;
    u8 _1910;
    bool _1911;
    bool _1912;
    bool _1913;
    bool _1914;
    bool _1915;
    bool _1916;
    bool _1917;
    u8 _1918[0x191C - 0x1918];
    mint::Runner mRunner;
    snd::SERequestor _1968;
    Stop mStop;
    info::lvmap::StageSphere mStageSphere;
    u8 _2170;
    bool _2171;
    u8 _2172[0x2174 - 0x2172];
    u32 _2174;
    bool _2178;
    u8 _2179[0x2194 - 0x2179];
    bool _2194;
    bool _2195;
    u8 _2196;
    bool _2197;
};

}
}
}
}

#endif
