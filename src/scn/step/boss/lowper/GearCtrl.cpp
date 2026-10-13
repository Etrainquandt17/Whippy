#include "scn/step/boss/lowper/GearCtrl.h"

#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "gobj/ModelDesc.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/chara/ModelDesc.h"
#include "scn/step/item/IndiviUtil.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

GearCtrl::GearCtrl(Boss& boss) : mBoss(boss), mIsSetup(false), mModelDesc() {}

GearCtrl::~GearCtrl() {}

// TODO: the casts stand for members of chara::ModelDesc and gobj::ModelDesc that have no type yet: the fallback
// name at 0x0, the node description at 0x50 of the model and the animation table at 0x70.
void GearCtrl::setup(map::BinItemKind kind, u32 variation) {
    if (!mIsSetup) {
        mBoss.gearManager().setup(1);
        const chara::ModelDesc& desc = item::IndiviUtil::ModelDesc(mBoss.comp(), kind, variation);
        mModelDesc.mName = desc.mModel._18;
        mModelDesc._40[0] = 2;
        mModelDesc.mNodes = *reinterpret_cast<const gobj::NodeReposDesc*>(&desc.mModel._44[3]);
        const char* name = desc._4;
        if (name == 0) {
            name = reinterpret_cast<const char*>(desc._0);
        }
        mBoss.gearManager().gear(0).set(name, mModelDesc);
        if (desc._70[0] != 0) {
            mAnimDesc._C = 0;
            const u32* anim = reinterpret_cast<const u32*>(desc._70[0]);
            mAnimDesc._0 = anim[0];
            mAnimDesc._4 = anim[1];
            mAnimDesc._8 = reinterpret_cast<const void*>(anim[2]);
            const char* animName = desc._8;
            if (animName == 0) {
                animName = reinterpret_cast<const char*>(desc._0);
            }
            mBoss.gearManager().gear(0).setAnim(animName, mAnimDesc);
            if (mAnimDesc._4 >= 2) {
                mBoss.gearManager().gear(0).anim().start(1, true);
            }
        }
        mBoss.gearManager().gear(0).setVisibility(true);
        mIsSetup = true;
    }
}

}
}
}
}
