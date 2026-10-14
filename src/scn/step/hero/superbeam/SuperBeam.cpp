#define DYNAMICS_DESC_MEMBERS
#include "scn/step/hero/superbeam/SuperBeam.h"
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
#include "scn/step/hero/SuperBeamParam.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/modeldesc/Dynamics.h"
#include "scn/step/hero/super/Utility.h"
#include "scn/step/hero/superbeam/StateAttack.h"

using g3d::ResFileAccessor;

namespace scn {
namespace step {
namespace hero {
namespace superbeam {

SuperBeam::SuperBeam(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , mIsSetup(false)
    , mHatDynamicsL()
    , mHatDynamicsR() {
    super::Utility::InitFuel(hero);
}

SuperBeam::~SuperBeam() {
    if (mIsSetup) {
        mHero.model().mAnim.unregisterResFile(0x1A);
    }
}

void SuperBeam::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/superbeam/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(0x1A, motion);
    {
        gobj::GearModelDesc desc;
        desc.mName = "TopL";
        desc._4C = true;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 2;
        const char* names[] = { "TopL", "StarAllJ" };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().hat().set("step/chara/hero/kirby/superbeam/Hat", desc);
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
        mHero.model().hat().setAnim("step/chara/hero/kirby/superbeam/Hat", desc);
    }
    const SuperBeamParam& param = mHero.param().superBeam();
    mHatDynamicsL._0 = param._0;
    mHatDynamicsR._0 = param._0;
    modeldesc::Dynamics::NodeParam param0 = param._4[0];
    static dynamics::DescNode descNode0;
    modeldesc::Dynamics::SetDescNode(descNode0, param0);
    mHatDynamicsL.setDescNode(0, descNode0);
    mHatDynamicsR.setDescNode(0, descNode0);
    modeldesc::Dynamics::NodeParam param1 = param._4[1];
    static dynamics::DescNode descNode1;
    modeldesc::Dynamics::SetDescNode(descNode1, param1);
    mHatDynamicsL.setDescNode(1, descNode1);
    mHatDynamicsR.setDescNode(1, descNode1);
    modeldesc::Dynamics::NodeParam param2 = param._4[2];
    static dynamics::DescNode descNode2;
    modeldesc::Dynamics::SetDescNode(descNode2, param2);
    mHatDynamicsL.setDescNode(2, descNode2);
    mHatDynamicsR.setDescNode(2, descNode2);
    modeldesc::Dynamics::NodeParam param3 = param._4[3];
    static dynamics::DescNode descNode3;
    modeldesc::Dynamics::SetDescNode(descNode3, param3);
    mHatDynamicsL.setDescNode(3, descNode3);
    mHatDynamicsR.setDescNode(3, descNode3);
    modeldesc::Dynamics::NodeParam param4 = param._4[4];
    static dynamics::DescNode descNode4;
    modeldesc::Dynamics::SetDescNode(descNode4, param4);
    mHatDynamicsL.setDescNode(4, descNode4);
    mHatDynamicsR.setDescNode(4, descNode4);
    mHatDynamicsL.mNodeNum = 5;
    mHatDynamicsR.mNodeNum = 5;
    mHatDynamicsL.mName = "LHat1DJ";
    mHatDynamicsR.mName = "RHat1DJ";
    mHero.model().hat().addDynamics(mHatDynamicsL);
    mHero.model().hat().addDynamics(mHatDynamicsR);
    {
        gobj::GearModelDesc desc;
        desc._4D = true;
        gobj::NodeReposDesc nodes;
        nodes.mCount = 3;
        const char* names[] = { "TopL", "AllL", "BeamL" };
        nodes.mNames = names;
        desc.mNodes = nodes;
        mHero.model().weapon().set("step/chara/hero/kirby/superbeam/Stick", desc);
    }
    {
        static gobj::GearAnimDesc desc;
        static gobj::G3DAnimDataReposDesc dataDesc;
        static const gobj::G3DAnimDataReposDesc::Entry entries[] = {
            { "Carry", 0 },
            { "SuperAbilityGet", 0 },
            { "SuperAttack", 0 },
            { "BeamBallControl", 0 },
        };
        desc._C = 1;
        dataDesc._4 = 4;
        dataDesc._0 = 1;
        dataDesc._8 = entries;
        reinterpret_cast<gobj::G3DAnimDataReposDesc&>(desc) = dataDesc;
        mHero.model().weapon().setAnim("step/chara/hero/kirby/superbeam/Stick", desc);
    }
    mHero.model().hat().anim().start(0, true);
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x3F), 1);
    mIsSetup = true;
}

bool SuperBeam::tryToChangeState() {
    return StateAttack::TryToChangeState(&mHero);
}

void SuperBeam::onShowHero() {
    mHero.model().hat().effect().requestN(static_cast<effect::Kind>(0x3F), 1);
    super::Utility::OnShowHero(mHero);
}

void SuperBeam::onHideHero() {
    mHero.model().hat().effect().releaseAndVanish();
    super::Utility::OnHideHero(mHero);
}

void SuperBeam::procAnim() {
    super::Utility::SuperLeakFuel(mHero);
}

bool SuperBeam::isDepleted() const {
    return mHero.abilityManager().getFuel() == 0;
}

void SuperBeam::onStateEndCleanUp() {
    if (mHero.model().weapon().isAnimExist()) {
        if (!mHero.wearBack().isBack()) {
            mHero.model().weapon().anim().clear();
        }
    }
}

}}}}  // namespace scn::step::hero::superbeam
