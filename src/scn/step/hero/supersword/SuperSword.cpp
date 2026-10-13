#define DYNAMICS_DESC_MEMBERS
#include "scn/step/hero/supersword/SuperSword.h"
#include "g3d/ResFileRepository.h"
#include "gobj/G3DAnimDataReposDesc.h"
#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/AbilityCustomBaseInfo.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/SuperSwordParam.h"
#include "scn/step/hero/modeldesc/Dynamics.h"
#include "scn/step/hero/super/Utility.h"
#include "scn/step/hero/supersword/StateAttack.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

SuperSword::SuperSword(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mHatDynamics() {
    super::Utility::InitFuel(hero);
}

SuperSword::~SuperSword() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x18);
    }
}

void SuperSword::setup() {
    g3d::ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    g3d::ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/supersword/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x18, motion);
    {
        gobj::GearModelDesc desc;
        desc.mName = "TopL";
        desc._4C = true;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 2;
        const char* names[] = { "TopL", "StarJ" };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().hat().set("step/chara/hero/kirby/supersword/Hat", desc);
    }
    {
        static gobj::GearAnimDesc desc;
        static gobj::G3DAnimDataReposDesc dataDesc;
        static const gobj::G3DAnimDataReposDesc::Entry entries[] = { { "Main", 0 } };
        desc._C = 0;
        dataDesc._4 = 1;
        dataDesc._0 = 1;
        dataDesc._8 = entries;
        reinterpret_cast<gobj::G3DAnimDataReposDesc&>(desc) = dataDesc;
        mHero.model().hat().setAnim("step/chara/hero/kirby/supersword/Hat", desc);
    }
    const SuperSwordParam& param = mHero.param().superSword();
    mHatDynamics._0 = param._0;
    modeldesc::Dynamics::NodeParam param0 = param._4[0];
    static dynamics::DescNode descNode0;
    modeldesc::Dynamics::SetDescNode(descNode0, param0);
    mHatDynamics.setDescNode(0, descNode0);
    modeldesc::Dynamics::NodeParam param1 = param._4[1];
    static dynamics::DescNode descNode1;
    modeldesc::Dynamics::SetDescNode(descNode1, param1);
    mHatDynamics.setDescNode(1, descNode1);
    modeldesc::Dynamics::NodeParam param2 = param._4[2];
    static dynamics::DescNode descNode2;
    modeldesc::Dynamics::SetDescNode(descNode2, param2);
    mHatDynamics.setDescNode(2, descNode2);
    modeldesc::Dynamics::NodeParam param3 = param._4[3];
    static dynamics::DescNode descNode3;
    modeldesc::Dynamics::SetDescNode(descNode3, param3);
    mHatDynamics.setDescNode(3, descNode3);
    mHatDynamics.mNodeNum = 4;
    mHatDynamics.mName = "HatTail1DJ";
    mHero.model().hat().addDynamics(mHatDynamics);
    {
        gobj::GearModelDesc desc;
        desc._4D = true;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 8;
        const char* names[] = {
            "SuperSwordM", "MoonSwordM", "ShinaiM", "ChineseKnifM", "MetaSwordM", "HarisenM", "TunaM", "RotL",
        };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().weapon().set("step/chara/hero/kirby/supersword/SuperSword", desc);
    }
    {
        static gobj::GearAnimDesc desc;
        static gobj::G3DAnimDataReposDesc dataDesc;
        static const gobj::G3DAnimDataReposDesc::Entry entries[] = { { "Carry", 0 } };
        desc._C = 7;
        dataDesc._4 = 1;
        dataDesc._0 = 1;
        dataDesc._8 = entries;
        reinterpret_cast<gobj::G3DAnimDataReposDesc&>(desc) = dataDesc;
        mHero.model().weapon().setAnim("step/chara/hero/kirby/supersword/SuperSword", desc);
    }
    for (u32 i = 0; i < 7; i++) {
        mHero.model().weapon().setNodeVisibility(i, false);
    }
    mHero.model().weapon().setNodeVisibility(0, true);
    mHero.model().hat().anim().start(0, true);
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x525), 1);
    mIsSetup = true;
}

// TODO: the original carries six MetaFortress checks whose mixing steps tools/metafortress_c.py leaves as
// instructions; this is the game's own code only.
bool SuperSword::tryToChangeState() {
    if (StateAttack::TryToChangeState(&mHero)) {
        return true;
    }
    return false;
}

void SuperSword::onShowHero() {
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x525), 1);
    super::Utility::OnShowHero(mHero);
}

void SuperSword::onHideHero() {
    mHero.model().hat().effect().releaseAndVanish();
    super::Utility::OnHideHero(mHero);
}

void SuperSword::procAnim() {
    super::Utility::SuperLeakFuel(mHero);
}

bool SuperSword::isDepleted() const {
    return mHero.abilityManager().getFuel() == 0;
}

}
}
}
}
