#ifndef SCN_STEP_HERO_MINTGEAR_H
#define SCN_STEP_HERO_MINTGEAR_H

#include "gobj/GearAnim.h"
#include "gobj/MintGearAnim.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/MintEffect.h"
#include "scn/step/hero/Gear.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

// What a script holds as a "Scn.Step.Hero.Gear".
class MintGear {
public:
    static void RegisterForce(Gear& obj);
    static void Unregister();
    static MintGear Obj();
    static void SetVisibility(bool visible);
    static void SetNodeVisibility(u32 node, bool visible);
    static void LoadNode(u32 node);
    static void BindEffect();
    static void BindEffectWarp();

    void setVisibility(bool visible) const { mObj->setVisibility(visible); }
    void setNodeVisibility(u32 node, bool visible) const { mObj->setNodeVisibility(node, visible); }
    bool isAnimExist() const { return mObj->isAnimExist(); }
    gobj::GearModel& model() const { return mObj->model(); }
    gobj::MintGearAnim anim() const { return mObj->anim().mint(); }
    chara::MintEffect effect() const { return mObj->effect().mint(); }
    chara::MintEffect effectWarp() const { return mObj->effectWarp().mint(); }

private:
    Gear* mObj;
};

}
}
}

#endif
