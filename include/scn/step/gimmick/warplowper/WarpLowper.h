#ifndef SCN_STEP_GIMMICK_WARPLOWPER_WARPLOWPER_H
#define SCN_STEP_GIMMICK_WARPLOWPER_WARPLOWPER_H

#include "g3d/CharaModel.h"
#include "g3d/ResFileAccessor.h"
#include "hel/math/Vector2.h"
#include "mem/ExplicitScopedPtr.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/Stop.h"
#include "scn/step/ostop/Requestor.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace g3d {
class Root;
}

namespace scn {
namespace step {

class Component;

namespace map {
struct BinGmkGeneralEntry;
}

namespace gimmick {
namespace warplowper {

struct Param {
    f32 _0;
    u32 _4;
    f32 _8;
    f32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    f32 _20;
};

class WarpLowper {
public:
    WarpLowper(const map::BinGmkGeneralEntry& entry, Component& component);
    ~WarpLowper();

    void registerToRoot(g3d::Root& root);
    void registerToRootFore(g3d::Root& root);
    void procBegin();
    void updateFrame();
    void onFrameEnd();
    void updateUseGPU();
    bool isHit(const hel::math::Vector2& pos) const;
    void onEntered();
    bool isDiscardCopy() const;
    u32 stepShift() const;
    u32 portalNo() const;
    const hel::math::Vector2& pos() const;
    void setGuard(bool guard);
    bool isAppearAlready() const;

private:
    void mfRequestEffect();
    bool mfDemoStartCheck() const;
    bool mfGetIsBroken() const;
    void mfStartWaitMain();
    void onAnimStart();
    void mfStartDemo();
    void mfProcessDemo();
    void mfUpdateSRT();

    ParamAccessor<Param> mParam;
    Component& mComponent;
    hel::math::Vector2 mPos;
    u32 _14;
    u32 _18;
    u32 _1C;
    mem::ExplicitScopedPtr<g3d::ResFileAccessor> mResFile;
    mem::ExplicitScopedPtr<g3d::CharaModel> mModel;
    Effect _30;
    Effect _3CC;
    snd::SERequestor mSE;
    u32 _7DC;
    bool _7E0;
    bool _7E1;
    bool _7E2;
    bool _7E3;
    bool _7E4;
    s32 _7E8;
    Stop mStop;
    ostop::Requestor mObjStop;
    u32 _860;
    u32 _864;
    f32 _868;
    util::FrameCounter _86C;
    bool _874;
    bool _875;
};

}
}
}
}

#endif
