#ifndef SCN_STEP_HERO_MODEL_H
#define SCN_STEP_HERO_MODEL_H

#include "gobj/Anim.h"
#include "gobj/Script.h"
#include "hel/math/Direction3.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/SubAnimControl.h"
#include "types.h"

namespace gobj {
class Model;
}

namespace hel {
namespace math {
class Vector3;
}
}

namespace scn {
namespace step {
namespace chara {
class ModelRotCtrl;
class Shake;
}
namespace hero {

class FloaterRotCtrl;
class SlopeFit;

class Model {
public:
    // TODO: members, once the layout around them is known
    SlopeFit& slopeFit() { return *reinterpret_cast<SlopeFit*>(reinterpret_cast<u8*>(this) + 0x364); }
    FloaterRotCtrl& floaterRotCtrl() { return *reinterpret_cast<FloaterRotCtrl*>(reinterpret_cast<u8*>(this) + 0x2E4C); }
    chara::Shake& shake() { return *reinterpret_cast<chara::Shake*>(reinterpret_cast<u8*>(this) + 0x2E14); }
    gobj::Script& script() { return *reinterpret_cast<gobj::Script*>(reinterpret_cast<u8*>(this) + 0x224); }
    chara::ScriptTrigger& scriptTrigger() {
        return *reinterpret_cast<chara::ScriptTrigger*>(reinterpret_cast<u8*>(this) + 0x280);
    }
    SubAnimControl& subAnimControl() { return mSubAnimControl; }
    gobj::Anim& anim() { return mAnim; }
    chara::ModelRotCtrl& modelRotCtrl() {
        return *reinterpret_cast<chara::ModelRotCtrl*>(reinterpret_cast<u8*>(this) + 0x290);
    }
    bool isAllEnd() const;
    void setFixDir(bool isFix);
    void setIsRightDir(bool isRightDir);
    bool isRightDir() const;
    Gear& hat() { return _378; }
    Gear& weapon() { return _CF0; }
    Gear& body() { return _1668; }
    gobj::Model& model() { return *reinterpret_cast<gobj::Model*>(reinterpret_cast<u8*>(this) + 0xC); }

    u8 _0[0x1F8];
    gobj::Anim mAnim;
    u8 _224[0x154];
    Gear _378;
    Gear _834;
    Gear _CF0;
    Gear _11AC;
    Gear _1668;
    Gear _1B24;
    Gear _1FE0;
    Gear _249C;
    Gear _2958;
    u8 _2E14[8];
    SubAnimControl mSubAnimControl;
    void resetViewOffset();
    void setViewOffset(const hel::math::Vector3& offset);
    void setSELoopNoReset();
    f32 getSign() const;
    void setAttackNoRenew();
    hel::math::Direction3 getDirection3() const;
};

}
}
}

#endif
