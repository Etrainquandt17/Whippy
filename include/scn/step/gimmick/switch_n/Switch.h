#ifndef SCN_STEP_GIMMICK_SWITCH_N_SWITCH_H
#define SCN_STEP_GIMMICK_SWITCH_N_SWITCH_H

#include "hel/common/FixedStringIN.h"
#include "hel/math/Vector2.h"
#include "ocoll/Hit.h"
#include "ocoll/NodeDesc.h"
#include "ocoll/Owner.h"
#include "ocoll/SearchAttack.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/Model.h"
#include "scn/step/gimmick/ParamAccessor.h"
#include "scn/step/gimmick/Stop.h"
#include "snd/SERequestor.h"
#include "types.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {

class Component;

namespace map {
struct BinGmkGeneralEntry;
}
}
}

namespace g3d {
class Root;
}

namespace scn {
namespace step {

namespace gimmick {
namespace switch_n {

struct Param {
    hel::math::Vector2 _0;
    hel::math::Vector2 _8;
    f32 _10;
    f32 _14;
    f32 _18;
};

class Switch {
public:
    Switch(const map::BinGmkGeneralEntry& entry, Component& component, const char* name);
    virtual ~Switch();
    virtual bool isChangeToOn();
    virtual bool isChangeToOff();
    virtual void onChangeOffToOn();
    virtual void onChangeToOn();
    virtual void onChangeOnToOff();
    virtual void onChangeToOff();

    void registerToRoot(g3d::Root& root);
    void updateFrame();
    void objCollReact();
    bool checkHit() const;
    void sendSwitchOn();
    void sendSwitchOff();
    void sendSwitchToggle();
    void hitOn();
    void hitOff();
    void searchAttackOn();
    void searchAttackOff();
    bool isStartCount() const;
    void startCount(u32 frame);
    void stopCount();
    bool isCountEnd() const;
    ocoll::NodeDesc mfGetOCNodeDesc(f32);

private:
    ParamAccessor<Param> mParam;
    Component& mComponent;
    hel::math::Vector2 mPos;
    u32 _18;
    // TODO: may be a FixedString<40>, which hel/common/FixedString.h cannot construct inline yet.
    hel::common::FixedStringIN<char, 40> mName;
    Model mModel;
    Stop mStop;
    Effect mEffect;
    snd::SERequestor _5FC;
    ocoll::Owner mOwner;
    ocoll::Hit mHit;
    ocoll::SearchAttack mSearchAttack;
    bool _C68;
    bool _C69;
    bool _C6A;
    util::FrameCounter _C6C;
    s32 _C74;
    bool _C78;
};

}
}
}
}

#endif
